%{

#include <iostream>
#include <stdlib.h> // for Linux
#include "shAbstractSyntaxTree.h"

using namespace Shmuppet;

#define YYERROR_VERBOSE
#define YYSTYPE AbstractSyntaxTreeNode*

int yylex (void);

extern char *yytext;
extern int yylineno;

static AbstractSyntaxTree* AST = AbstractSyntaxTree::instancePtr ();

void yyerror (char *a_msg)
{
	AST->addError (yylineno, a_msg);
}

%}

%token KEYWORD_BULLET
%token KEYWORD_AREA
%token KEYWORD_SPLINE
%token KEYWORD_REPEAT
%token KEYWORD_IF
%token KEYWORD_ELSE
%token KEYWORD_GOTO
%token KEYWORD_WAIT
%token KEYWORD_SET
%token KEYWORD_AFFECTORS
%token KEYWORD_BASE
%token KEYWORD_CENTRE
%token INTEGER
%token REAL
%token IDENTIFIER
%token SYMBOL_LTE
%token SYMBOL_GTE
%token SYMBOL_EQ
%token SYMBOL_NEQ
%token SYMBOL_LOG_AND
%token SYMBOL_LOG_OR
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
			$$ = AST->createNode(ASTN_GunDefinitionList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;

gun_definition
	: KEYWORD_BULLET identifier '{' KEYWORD_AFFECTORS affector_list ';' state_definition_list '}'
		{
			$$ = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $7);
			$$->setChild(2, $5);
		}		
	| KEYWORD_BULLET identifier '{' state_definition_list '}'
		{
			$$ = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $4);
		}
	| KEYWORD_AREA '[' constant_integer ',' constant ',' KEYWORD_BASE ']' identifier '{' state_definition_list '}'
		{
			$$ = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			$$->setChild(0, $9);
			$$->setChild(1, $11);
			$$->setChild(2, $3);
			$$->setChild(3, $5);
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Base);
			$$->setChild(4, originNode);
		}
	| KEYWORD_AREA '[' ',' constant ',' KEYWORD_BASE ']' identifier '{' state_definition_list '}'
		{
			$$ = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			$$->setChild(0, $8);
			$$->setChild(1, $10);
			YYSTYPE sideNode = AST->createNode(ASTN_Constant, yylineno);
			sideNode->setFloat(-1.0f); // negative number means adaptive circle
			$$->setChild(2, sideNode);
			$$->setChild(3, $4);
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Base);
			$$->setChild(4, originNode);
		}
	| KEYWORD_AREA '[' constant_integer ',' constant ',' KEYWORD_CENTRE ']' identifier '{' state_definition_list '}'
		{
			$$ = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			$$->setChild(0, $9);
			$$->setChild(1, $11);
			$$->setChild(2, $3);
			$$->setChild(3, $5);
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Centre);
			$$->setChild(4, originNode);
		}
	| KEYWORD_AREA '[' ',' constant ',' KEYWORD_CENTRE ']' identifier '{' state_definition_list '}'
		{
			$$ = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			$$->setChild(0, $8);
			$$->setChild(1, $10);
			YYSTYPE sideNode = AST->createNode(ASTN_Constant, yylineno);
			sideNode->setFloat(-1.0f); // negative number means adaptive circle
			$$->setChild(2, sideNode);
			$$->setChild(3, $4);
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Centre);
			$$->setChild(4, originNode);
		}
	;
	
affector_list
	: affector_call
		{
			$$ = $1;
		}
	| affector_list ',' affector_call
		{
			$$ = AST->createNode(ASTN_AffectorStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
affector_call
	: identifier function_call_arguments
		{
			$$ = AST->createNode(ASTN_AffectorCall, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;
	
state_definition_list
	: state_definition
		{
			$$ = $1;
		}
	| state_definition_list state_definition
		{
			$$ = AST->createNode(ASTN_StateList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;
	
state_definition
	: identifier compound_statement
		{
			$$ = AST->createNode(ASTN_State, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;
	
compound_statement
	: '{' '}'
		{
			$$ = 0;
		}
	| '{' statement_list '}'
		{
			$$ = $2;
		}
	;
	
statement_list
	: statement
		{
			$$ = $1;
		}
	| statement_list statement
		{
			$$ = AST->createNode(ASTN_StatementList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;
	
statement
	: expression_statement
		{
			$$ = $1;
		}
	| conditional_statement
		{
			$$ = $1;
		}
	| assignment_statement
		{
			$$ = $1;
		}
	| iteration_statement
		{
			$$ = $1;
		}
	| jump_statement
		{
			$$ = $1;
		}
	| wait_statement
		{
			$$ = $1;
		}
	| set_statement
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
	
conditional_statement
	: KEYWORD_IF constant_expression compound_statement
		{
			$$ = AST->createNode(ASTN_IfStatement, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $3);
		}
	| KEYWORD_IF constant_expression compound_statement KEYWORD_ELSE compound_statement
		{
			$$ = AST->createNode(ASTN_IfStatement, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $3);
			$$->setChild(2, $5);
		}
	| KEYWORD_IF constant_expression compound_statement KEYWORD_ELSE conditional_statement
		{
			$$ = AST->createNode(ASTN_IfStatement, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $3);
			$$->setChild(2, $5);
		}
	;	
	
assignment_statement
	: identifier '=' constant_expression ';'
		{
			$$ = AST->createNode(ASTN_AssignStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}		
	;
		
iteration_statement
	: KEYWORD_REPEAT constant_expression compound_statement
		{
			$$ = AST->createNode(ASTN_RepeatStatement, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $3);
		}		
	;
	
jump_statement
	: KEYWORD_GOTO identifier ';'
		{
			$$ = AST->createNode(ASTN_GotoStatement, yylineno);
			$$->setChild(0, $2);
		}		
	;
	
wait_statement
	: KEYWORD_WAIT function_call_arguments ';'
		{
			$$ = AST->createNode(ASTN_WaitStatement, yylineno);
			$$->setChild(0, $2);
		}
	;
	
set_statement
	: KEYWORD_SET identifier '(' constant_expression ',' constant_expression ')' ';'
		{
			$$ = AST->createNode(ASTN_SetStatement, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $4);
			$$->setChild(2, $6);
		}
	| KEYWORD_SET identifier '('constant_expression ')' ';'
		{
			$$ = AST->createNode(ASTN_SetStatement, yylineno);
			$$->setChild(0, $2);
			$$->setChild(1, $4);
			
			YYSTYPE timeNode = AST->createNode(ASTN_Constant, yylineno);
			timeNode->setFloat(-1.0f);
			$$->setChild(2, timeNode);
		}

	;
	
				
constant_expression
	: logical_or_expression
		{
			$$ = AST->createNode(ASTN_ConstantExpression, yylineno);
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
			$$ = AST->createNode(ASTN_LogicalOr, yylineno);
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
			$$ = AST->createNode(ASTN_LogicalAnd, yylineno);
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
			$$ = AST->createNode(ASTN_EqualsStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| equality_expression SYMBOL_NEQ relational_expression
		{
			$$ = AST->createNode(ASTN_NotEqualsStatement, yylineno);
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
			$$ = AST->createNode(ASTN_LessThanStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| relational_expression '>' additive_expression
		{
			$$ = AST->createNode(ASTN_GreaterThanStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| relational_expression SYMBOL_LTE additive_expression
		{
			$$ = AST->createNode(ASTN_LessThanEqStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| relational_expression SYMBOL_GTE additive_expression
		{
			$$ = AST->createNode(ASTN_GreaterThanEqStatement, yylineno);
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
			$$ = AST->createNode(ASTN_AddStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| additive_expression '-' multiplicative_expression
		{
			$$ = AST->createNode(ASTN_SubtractStatement, yylineno);
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
			$$ = AST->createNode(ASTN_MultiplyStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| multiplicative_expression '/' unary_expression
		{
			$$ = AST->createNode(ASTN_DivideStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| multiplicative_expression '%' unary_expression
		{
			$$ = AST->createNode(ASTN_RemainderStatement, yylineno);
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
			$$ = AST->createNode(ASTN_UnaryPosStatement, yylineno);
			$$->setChild(0, $2);
		}
	| '-' unary_expression
		{
			$$ = AST->createNode(ASTN_UnaryNegStatement, yylineno);
			$$->setChild(0, $2);
		}
	;
	
primary_expression
	: identifier
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
			$$ = AST->createNode(ASTN_FunctionCall, yylineno);
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
			$$ = AST->createNode(ASTN_FunctionCallArg, yylineno);
			$$->setChild(0, $1);
		}
	| argument_expression_list ',' constant_expression
		{
			$$ = AST->createNode(ASTN_FunctionCallArgList, yylineno);
			$$->setChild(0, $1);
			
			YYSTYPE argNode = AST->createNode(ASTN_FunctionCallArg, yylineno);
			argNode->setChild (0, $3);
			$$->setChild(1, argNode);
		}
	;

identifier
	: IDENTIFIER
		{
			$$ = AST->createNode(ASTN_Identifier, yylineno);
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
			$$ = AST->createNode(ASTN_Constant, yylineno);
			$$->setFloat(atof(yytext));
		}
	;

constant_real
	: REAL
		{
			$$ = AST->createNode(ASTN_Constant, yylineno);
			$$->setFloat(atof(yytext));
		}
	;

%%

	
	
