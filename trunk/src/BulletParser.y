%{

#include <iostream>
#include <stdlib.h> // for Linux
#include "bsParseTree.h"

using namespace BS_NMSP;

#define YYERROR_VERBOSE
#define YYSTYPE ParseTreeNode*

int yylex (void);

extern char *yytext;
extern int yylineno;

static ParseTree* AST = ParseTree::instancePtr ();

void yyerror (char *a_msg)
{
	AST->addError (yylineno, a_msg);
}

%}

%token KEYWORD_GUN
%token KEYWORD_FUNCTION
%token KEYWORD_STATE
%token KEYWORD_LOOP
%token KEYWORD_WHILE
%token KEYWORD_IF
%token KEYWORD_ELSE
%token KEYWORD_GOTO
%token KEYWORD_WAIT
%token KEYWORD_DIE
%token INTEGER
%token REAL
%token FUNC_ARGS
%token IDENTIFIER
%token SYMBOL_LTE
%token SYMBOL_GTE
%token SYMBOL_EQ
%token SYMBOL_NEQ
%token SYMBOL_LOG_AND
%token SYMBOL_LOG_OR
%token SYMBOL_INC
%token SYMBOL_DEC
%token SYMBOL_ADD_A
%token SYMBOL_SUB_A
%token SYMBOL_MUL_A
%token SYMBOL_DIV_A
%token TOKEN_ERROR

%%

script_file
	: gun_definition_list
		{
			AST->getRootNode()->setChild(0, $1);
		}
	;

gun_definition_list
	: gun_definition
		{
			$$ = $1;
		}
	| gun_definition_list gun_definition
		{
			$$ = AST->createNode(PT_GunDefinitionList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;

gun_definition
	: KEYWORD_GUN identifier '{' state_list '}'
		{
			// Guns have the following nodes:
			// 0: name
			// 1: member variables
			// 2: functions
			// 3: states
			// members must be declared first, then functions, then events
			$$ = AST->createNode(PT_GunDefinition, yylineno);
			$$->setChild(NameNode, $2);
			$$->setChild(MemberNode, 0);
			$$->setChild(FunctionNode, 0);
			$$->setChild(StateNode, $4);
		}		
	| KEYWORD_GUN identifier '{' member_list state_list '}'
		{
			$$ = AST->createNode(PT_GunDefinition, yylineno);
			$$->setChild(NameNode, $2);
			
			// member list
			if ($4->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, $4->getLine());
				newChild->setChild(0, $4);
				$$->setChild(MemberNode, newChild);
			}
			else
			{
				$$->setChild(MemberNode, $4);
			}
			
			$$->setChild(FunctionNode, 0);
			$$->setChild(StateNode, $5);
		}		
	| KEYWORD_GUN identifier '{' function_list state_list '}'
		{
			$$ = AST->createNode(PT_GunDefinition, yylineno);
			$$->setChild(NameNode, $2);
			$$->setChild(MemberNode, 0);
			$$->setChild(FunctionNode, $4);
			$$->setChild(StateNode, $5);
		}		
	| KEYWORD_GUN identifier '{' member_list function_list state_list '}'
		{
			$$ = AST->createNode(PT_GunDefinition, yylineno);
			$$->setChild(NameNode, $2);

			// member list
			if ($4->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, $4->getLine());
				newChild->setChild(0, $4);
				$$->setChild(MemberNode, newChild);
			}
			else
			{
				$$->setChild(MemberNode, $4);
			}

			$$->setChild(FunctionNode, $5);
			$$->setChild(StateNode, $6);
		}		
	;
	
member_list
	: assignment_statement
		{
			$$ = $1;
		}
	| member_list assignment_statement
		{
			$$ = AST->createNode(PT_MemberList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;
	
function_list
	: function
		{
			$$ = $1;
		}
	| function_list function
		{
			$$ = AST->createNode(PT_FunctionList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;
	
function
	: identifier '=' KEYWORD_FUNCTION function_arguments function_compound_statement
		{
			$$ = AST->createNode(PT_Function, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
			$$->setChild(2, $5);
		}
	;

function_arguments
	: '(' ')'
		{
			$$ = 0;
		}
	| '(' argument_list ')'
		{
			$$ = $2;
		}
	;

argument_list
	: identifier
		{
			$$ = AST->createNode(PT_FunctionArg, yylineno);
			$$->setChild(0, $1);
		}
	| argument_list ',' identifier
		{
			$$ = AST->createNode(PT_FunctionArgList, yylineno);
			$$->setChild(0, $1);
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, $3);
			$$->setChild(1, argNode);
		}
	;
			
state_list
	: state
		{
			$$ = $1;
		}
	| state_list state
		{
			$$ = AST->createNode(PT_StateList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;
	
state
	: identifier '=' KEYWORD_STATE state_compound_statement
		{
			$$ = AST->createNode(PT_State, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
		}
	;
	
function_compound_statement
	: '{' '}'
		{
			$$ = 0;
		}
	| '{' function_statement_list '}'
		{
			$$ = $2;
		}
	;
	
state_compound_statement
	: '{' '}'
		{
			$$ = 0;
		}
	| '{' state_statement_list '}'
		{
			$$ = $2;
		}
	;

function_statement_list
	: function_statement
		{
			$$ = $1;
		}
	| function_statement_list function_statement
		{
			$$ = AST->createNode(PT_StatementList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;
	
state_statement_list
	: state_statement
		{
			$$ = $1;
		}
	| state_statement_list state_statement
		{
			$$ = AST->createNode(PT_StatementList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;

function_statement
	: expression_statement
		{
			$$ = $1;
		}
	| function_conditional_statement
		{
			$$ = $1;
		}
	| assignment_statement
		{
			$$ = $1;
		}
	| property_statement
		{
			$$ = $1;
		}
	| function_iteration_statement
		{
			$$ = $1;
		}
	| wait_statement
		{
			$$ = $1;
		}
	| fire_statement
		{
			$$ = $1;
		}
	| die_statement
		{
			$$ = $1;
		}
	;
	
state_statement
	: expression_statement
		{
			$$ = $1;
		}
	| state_conditional_statement
		{
			$$ = $1;
		}
	| assignment_statement
		{
			$$ = $1;
		}
	| state_iteration_statement
		{
			$$ = $1;
		}
	| goto_statement
		{
			$$ = $1;
		}
	| wait_statement
		{
			$$ = $1;
		}
	| fire_statement
		{
			$$ = $1;
		}
	;

expression_statement
	: ';'
		{
			$$ = 0;
		}
	| constant_expression ';'
		{
			$$ = $1;
		}
	;
	
state_conditional_statement
	: KEYWORD_IF '(' constant_expression ')' state_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_IF '(' constant_expression ')' state_compound_statement KEYWORD_ELSE state_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	| KEYWORD_IF '(' constant_expression ')' state_compound_statement KEYWORD_ELSE state_conditional_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	;	

function_conditional_statement
	: KEYWORD_IF '(' constant_expression ')' function_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_IF '(' constant_expression ')'function_compound_statement KEYWORD_ELSE function_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	| KEYWORD_IF '(' constant_expression ')' function_compound_statement KEYWORD_ELSE function_conditional_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	;	
	
assignment_statement
	: identifier '=' constant_expression ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| identifier SYMBOL_INC ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			
			// create 'identifier + 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString($1->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			$$->setChild(1, ce_node);
		}
	| identifier SYMBOL_DEC ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			
			// create 'identifier - 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString($1->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			$$->setChild(1, ce_node);
		}
	| identifier SYMBOL_ADD_A constant_expression ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			
			// create 'identifier + ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString($1->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, $3);
			ce_node->setChild(0, add_node);
			$$->setChild(1, ce_node);
		}
	| identifier SYMBOL_SUB_A constant_expression ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			
			// create 'identifier - ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString($1->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, $3);
			ce_node->setChild(0, add_node);
			$$->setChild(1, ce_node);
		}
	| identifier SYMBOL_MUL_A constant_expression ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			
			// create 'identifier * ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_MultiplyStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString($1->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, $3);
			ce_node->setChild(0, add_node);
			$$->setChild(1, ce_node);
		}
	| identifier SYMBOL_DIV_A constant_expression ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			
			// create 'identifier / ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_DivideStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString($1->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, $3);
			ce_node->setChild(0, add_node);
			$$->setChild(1, ce_node);
		}
	;
	
property_statement
	: property '=' constant_expression ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| property '=' '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
			$$->setChild(2, $6);
		}
	;
		
state_iteration_statement
	: KEYWORD_LOOP '(' constant_expression ')' state_compound_statement
		{
			$$ = AST->createNode(PT_LoopStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_WHILE '(' constant_expression ')' state_compound_statement
		{
			$$ = AST->createNode(PT_WhileStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	;

function_iteration_statement
	: KEYWORD_LOOP '(' constant_expression ')' function_compound_statement
		{
			$$ = AST->createNode(PT_LoopStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}		
	| KEYWORD_WHILE '(' constant_expression ')' function_compound_statement
		{
			$$ = AST->createNode(PT_WhileStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	;
	
goto_statement
	: KEYWORD_GOTO identifier ';'
		{
			$$ = AST->createNode(PT_GotoStatement, yylineno);
			$$->setChild(0, $2);
		}		
	;
	
wait_statement
	: KEYWORD_WAIT '(' constant_expression ')' ';'
		{
			$$ = AST->createNode(PT_WaitStatement, yylineno);
			$$->setChild(0, $3);
		}
	;
	
fire_statement
	: identifier identifier function_call_arguments fire_tail ';'
		{
			$$ = AST->createNode(PT_FireStatement, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;
			
			$$->setChild(0, $1);
			$$->setChild(1, $3);
			$$->setChild(3, $4);
		}
	| identifier identifier function_call_arguments ';'
		{
			$$ = AST->createNode(PT_FireStatement, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;
			
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
fire_tail
	: ':' function_call
		{
			$$ = AST->createNode(PT_FunctionTail, yylineno);
			$$->setChild(0, $2);
		}
	| '[' func_args ']'
		{
			$$ = AST->createNode(PT_FunctionTail, yylineno);
			$$->setChild(1, $2);
		}
	| '[' func_args ']' ':' function_call
		{
			$$ = AST->createNode(PT_FunctionTail, yylineno);
			$$->setChild(0, $5);
			$$->setChild(1, $2);
		}
	;
	
die_statement
	: KEYWORD_DIE '(' ')' ';'
		{	
			$$ = AST->createNode(PT_DieStatement, yylineno);
		}
	;
		
constant_expression
	: logical_or_expression
		{
			$$ = AST->createNode(PT_ConstantExpression, yylineno);
			$$->setChild(0, $1);
		}
	;

logical_or_expression
	: logical_and_expression
		{
			$$ = $1;
		}
	| logical_or_expression SYMBOL_LOG_OR logical_and_expression
		{
			$$ = AST->createNode(PT_LogicalOr, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;	
	
logical_and_expression
	: equality_expression
		{
			$$ = $1;
		}
	| logical_and_expression SYMBOL_LOG_AND equality_expression
		{
			$$ = AST->createNode(PT_LogicalAnd, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;		
	
equality_expression
	: relational_expression
		{
			$$ = $1;
		}
	| equality_expression SYMBOL_EQ relational_expression
		{
			$$ = AST->createNode(PT_EqualsStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| equality_expression SYMBOL_NEQ relational_expression
		{
			$$ = AST->createNode(PT_NotEqualsStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
relational_expression 
	: additive_expression
		{
			$$ = $1;
		}
	| relational_expression '<' additive_expression
		{
			$$ = AST->createNode(PT_LessThanStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| relational_expression '>' additive_expression
		{
			$$ = AST->createNode(PT_GreaterThanStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| relational_expression SYMBOL_LTE additive_expression
		{
			$$ = AST->createNode(PT_LessThanEqStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| relational_expression SYMBOL_GTE additive_expression
		{
			$$ = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;

additive_expression
	: multiplicative_expression
		{
			$$ = $1;
		}
	| additive_expression '+' multiplicative_expression
		{
			$$ = AST->createNode(PT_AddStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| additive_expression '-' multiplicative_expression
		{
			$$ = AST->createNode(PT_SubtractStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;

multiplicative_expression
	: unary_expression
		{
			$$ = $1;
		}
	| multiplicative_expression '*' unary_expression
		{
			$$ = AST->createNode(PT_MultiplyStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| multiplicative_expression '/' unary_expression
		{
			$$ = AST->createNode(PT_DivideStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| multiplicative_expression '%' unary_expression
		{
			$$ = AST->createNode(PT_RemainderStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;

unary_expression
	: primary_expression
		{
			$$ = $1;
		}
	| '+' unary_expression
		{
			$$ = AST->createNode(PT_UnaryPosStatement, yylineno);
			$$->setChild(0, $2);
		}
	| '-' unary_expression
		{
			$$ = AST->createNode(PT_UnaryNegStatement, yylineno);
			$$->setChild(0, $2);
		}
	;
	
primary_expression
	: identifier
		{
			$$ = $1;
		}
	| property
		{
			$$ = $1;
		}
	| function_call
		{
			$$ = $1;
		}
	| constant
		{
			$$ = $1;
		}
	| '(' constant_expression ')'
		{
			$$ = $2;
		}
	;
	
function_call
	: identifier function_call_arguments
		{
			$$ = AST->createNode(PT_FunctionCall, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;
	
function_call_arguments
	: '(' ')'
		{
			$$ = 0;
		}
	| '(' argument_expression_list ')'
		{
			$$ = $2;
		}
	;

argument_expression_list
	: constant_expression
		{
			$$ = AST->createNode(PT_FunctionCallArg, yylineno);
			$$->setChild(0, $1);
		}
	| argument_expression_list ',' constant_expression
		{
			$$ = AST->createNode(PT_FunctionCallArgList, yylineno);
			$$->setChild(0, $1);
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, $3);
			$$->setChild(1, argNode);
		}
	;

identifier
	: IDENTIFIER
		{
			$$ = AST->createNode(PT_Identifier, yylineno);
			$$->setString(yytext);
		}
	;
	
property
	: '$' identifier
		{
			$$ = AST->createNode(PT_Property, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;
		}
	;
			
	
func_args
	: FUNC_ARGS
		{
			$$ = AST->createNode(PT_Identifier, yylineno);
			$$->setString(yytext);
		}
	;

constant
	: constant_integer
		{
			$$ = $1;
		}
	| constant_real
		{
			$$ = $1;
		}
	;
	
constant_integer
	: INTEGER
		{
			// This only accepts non-negative integers
			$$ = AST->createNode(PT_Constant, yylineno);
			$$->setValue(atof(yytext));
		}
	;

constant_real
	: REAL
		{
			$$ = AST->createNode(PT_Constant, yylineno);
			$$->setValue(atof(yytext));
		}
	;

%%

	
	
