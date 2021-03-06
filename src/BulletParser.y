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

static ParseTree* AST = ParseTree::instancePtr();

static const String gs_tokens[] = {
	"KEYWORD_CONTROLLER",				"controller",
	"KEYWORD_EMITTER",					"emitter",
	"KEYWORD_AFFECTOR",					"affector",
	"KEYWORD_FUNCTION",					"function",
	"KEYWORD_STATE",					"state",
	"KEYWORD_EVENT",					"event",
	"KEYWORD_RAISE",					"raise",
	"KEYWORD_WHILE",					"while",
	"KEYWORD_FOR",						"for",
	"KEYWORD_BREAK",					"break",
	"KEYWORD_CONTINUE",					"continue",
	"KEYWORD_IF",						"if",
	"KEYWORD_GOTO",						"goto",
	"KEYWORD_WAIT",						"wait",	
	"KEYWORD_ELSE",						"else",
	"KEYWORD_SUSPEND",					"suspend",
	"KEYWORD_SIGNAL",					"signal",
	"KEYWORD_DIE",						"die",
	"INTEGER",							"integral value",
	"REAL",								"value",
	"IDENTIFIER",						"identifier",
	"SYMBOL_LTE",						"<=",
	"SYMBOL_GTE",						">=",
	"SYMBOL_EQ",						"==",
	"SYMBOL_NEQ",						"!=",
	"SYMBOL_LOG_AND",					"&&",
	"SYMBOL_LOG_OR",					"||",
	"SYMBOL_INC",						"++",
	"SYMBOL_DEC",						"--",
	"SYMBOL_ADD_A",						"+=",
	"SYMBOL_SUB_A",						"-=",
	"SYMBOL_MUL_A",						"*=",
	"SYMBOL_DIV_A",						"/=",
};

void replaceVerboseTokens(String& a_string)
{
	for (int i = 0; i < 66; i += 2)
	{
		int startPos = (int) a_string.find(gs_tokens[i]);
		if (startPos < 0)
			continue;

		size_t count = gs_tokens[i].length();

		a_string.replace(startPos, count, gs_tokens[i + 1]);
	}
}

void yyerror(char* a_msg)
{
	String msgString = a_msg;
	replaceVerboseTokens(msgString);

	AST->addError(yylineno, msgString);
}

void rearrange_emitter_objects(YYSTYPE rootNode, YYSTYPE objNode)
{
	if (!objNode)
		return;
		
	// Go through objNode, and add any members, affectors, functions and states
	// to the list on the correct child node of rootNode
	int nodeType = objNode->getType();
	
	int rootChildren[] = {PT_EmitterAffectorNode, PT_EmitterFunctionNode, 
		PT_EmitterStateNode, PT_EmitterMemberNode};
		
	if (nodeType == PT_MemberDecl || nodeType == PT_AffectorDecl ||
		nodeType == PT_FunctionDecl || nodeType == PT_StateDecl)
	{
		int rootNodeType = rootChildren[(nodeType - PT_AffectorDecl) / 2];
		int declNodeType = nodeType - 1;
		
		YYSTYPE subNode = rootNode->getChild(rootNodeType);
		
		if (!subNode)
		{
			rootNode->setChild(rootNodeType, objNode);
		}
		else
		{
			YYSTYPE curNode = subNode;
			subNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(0, curNode);
			
			YYSTYPE newNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(1, newNode);
			newNode->setChild(0, objNode);
			
			rootNode->setChild(rootNodeType, subNode);
		}
		
		return;
	}
	
	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		rearrange_emitter_objects(rootNode, objNode->getChild(i));
}

void rearrange_controller_objects(YYSTYPE rootNode, YYSTYPE objNode)
{
	if (!objNode)
		return;

	// Go through objNode, and add any members, emitter members, events and states
	// to the list on the correct child node of rootNode
	int nodeType = objNode->getType();
	
	int rootChildren[] = {PT_ControllerStateNode, PT_ControllerMemberNode, 
		PT_ControllerEmitterNode, PT_ControllerEventNode};
		
	if (nodeType == PT_MemberDecl || nodeType == PT_StateDecl ||
		nodeType == PT_EventDecl || nodeType == PT_EmitterMemberDecl)
	{
		int rootNodeType = rootChildren[(nodeType - PT_StateDecl) / 2];
		int declNodeType = nodeType - 1;
		
		YYSTYPE subNode = rootNode->getChild(rootNodeType);
		
		if (!subNode)
		{
			rootNode->setChild(rootNodeType, objNode);
		}
		else
		{
			YYSTYPE curNode = subNode;
			subNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(0, curNode);
			
			YYSTYPE newNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(1, newNode);
			newNode->setChild(0, objNode);
			
			rootNode->setChild(rootNodeType, subNode);
		}
		
		return;
	}
	
	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		rearrange_controller_objects(rootNode, objNode->getChild(i));
}

void generate_assignment_expr(int nodeType, int idType, YYSTYPE parentNode, YYSTYPE idNode, YYSTYPE exprNode)
{
	parentNode->setChild(0, idNode);
	YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
	YYSTYPE expr_node = AST->createNode(nodeType, yylineno);
				
	YYSTYPE id_node = AST->createNode(idType, yylineno);
	if (idType == PT_EmitterMember)
	{
		id_node->setString(idNode->getStringData().c_str());
		
		YYSTYPE id_name_node = AST->createNode(PT_Identifier, yylineno);
		id_name_node->setString(idNode->getChild(0)->getStringData().c_str());

		id_node->setChild(0, id_name_node);
	}
	else
	{
		id_node->setString(idNode->getStringData().c_str());
	}
				
	expr_node->setChild(0, id_node);
	expr_node->setChild(1, exprNode);
	ce_node->setChild(0, expr_node);
	parentNode->setChild(1, ce_node);
}

void generate_inc_expr(int value, int nodeType, YYSTYPE parentNode, YYSTYPE idNode)
{
	parentNode->setChild(0, idNode);
	YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
	
	YYSTYPE inc_node = 0;
	if (value == 1)
		inc_node = AST->createNode(PT_AddStatement, yylineno);
	else if (value == -1)
		inc_node = AST->createNode(PT_SubtractStatement, yylineno);
	
	YYSTYPE id_node = AST->createNode(nodeType, yylineno);
	if (nodeType == PT_EmitterMember)
	{
		id_node->setString(idNode->getStringData().c_str());
		id_node->setChild(0, idNode->getChild(0));
	}
	else
	{
		id_node->setString(idNode->getStringData().c_str());
	}	
	
	YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
	v_node->setValue(1);

	inc_node->setChild(0, id_node);
	inc_node->setChild(1, v_node);
	ce_node->setChild(0, inc_node);
	parentNode->setChild(1, ce_node);
}

%}

%token KEYWORD_CONTROLLER
%token KEYWORD_EMITTER
%token KEYWORD_AFFECTOR
%token KEYWORD_FUNCTION
%token KEYWORD_STATE
%token KEYWORD_EVENT
%token KEYWORD_RAISE
%token KEYWORD_WHILE
%token KEYWORD_FOR
%token KEYWORD_BREAK
%token KEYWORD_CONTINUE
%token KEYWORD_IF
%token KEYWORD_ELSE
%token KEYWORD_GOTO
%token KEYWORD_WAIT
%token KEYWORD_SUSPEND
%token KEYWORD_SIGNAL
%token KEYWORD_DIE
%token INTEGER
%token REAL
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
	: definition_list
		{
			AST->getRootNode()->setChild(0, $1);
		}
	;
	
definition_list
	: definition
		{
			$$ = $1;
		}
	| definition_list definition
		{
			$$ = AST->createNode(PT_DefinitionList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;
	
definition
	: emitter_definition
		{
			$$ = $1;
		}
	| controller_definition
		{
			$$ = $1;
		}
	;

emitter_definition
	: KEYWORD_EMITTER identifier '{' emitter_object_declaration_list '}'
		{
			$$ = AST->createNode(PT_EmitterDefinition, yylineno);
			$$->setString($2->getStringData().c_str());			
			delete $2;

			// Now rearrange members, affectors, functions and states into correct nodes.
			rearrange_emitter_objects($$, $4);
		}
	;
	
emitter_object_declaration 
	: member_declaration
		{
			$$ = $1;
		}
	| affector_declaration
		{
			$$ = $1;
		}
	| function
		{
			$$ = $1;
		}
	| emitter_state
		{
			$$ = $1;
		}
	;
	
emitter_object_declaration_list
	: emitter_object_declaration
		{
			$$ = $1;
		}
	| emitter_object_declaration_list emitter_object_declaration
		{
			$$ = AST->createNode(PT_EmitterObjectList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;	
	
controller_definition
	: KEYWORD_CONTROLLER identifier '{' controller_object_declaration_list '}'
		{
			$$ = AST->createNode(PT_ControllerDefinition, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;

			// Now rearrange members, affectors, functions and states into correct nodes.
			rearrange_controller_objects($$, $4);
		}		
	;
	
controller_object_declaration 
	: member_declaration
		{
			$$ = $1;
		}
	| emitter_member_declaration
		{
			$$ = $1;
		}
	| event
		{
			$$ = $1;
		}
	| controller_state
		{
			$$ = $1;
		}
	;
	
controller_object_declaration_list
	: controller_object_declaration
		{
			$$ = $1;
		}
	| controller_object_declaration_list controller_object_declaration
		{
			$$ = AST->createNode(PT_ControllerObjectList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}
	;	
		
member_declaration
	: simple_assignment_statement
		{
			$$ = $1;
			$$->_setType(PT_MemberDecl);
		}
	;

affector_declaration
	: identifier '=' KEYWORD_AFFECTOR function_call ';'
		{
			$$ = AST->createNode(PT_AffectorDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
		}
	;
			
emitter_member_declaration
	: identifier '=' KEYWORD_EMITTER identifier ';'
		{
			$$ = AST->createNode(PT_EmitterMemberDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
		}
	| identifier '=' KEYWORD_EMITTER identifier '(' signed_constant_arg_list ')' ';'
		{
			$$ = AST->createNode(PT_EmitterMemberDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
			$$->setChild(2, $6);
		}
	;
	
signed_constant_arg_list
	: signed_constant
		{
			$$ = $1;
		}
	| signed_constant_arg_list ',' signed_constant
		{
			$$ = AST->createNode(PT_ConstantList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
unsigned_constant_arg_list
	: unsigned_constant
		{
			$$ = $1;
		}
	| unsigned_constant_arg_list ',' unsigned_constant
		{
			$$ = AST->createNode(PT_ConstantList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
function
	: identifier '=' KEYWORD_FUNCTION function_arguments function_compound_statement
		{
			$$ = AST->createNode(PT_FunctionDecl, yylineno);
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
	
event
	: identifier '=' KEYWORD_EVENT function_arguments event_compound_statement
		{
			$$ = AST->createNode(PT_EventDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
			$$->setChild(2, $5);
		}
	;
	
emitter_state
	: identifier '=' KEYWORD_STATE emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_StateDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
		}
	| identifier '=' KEYWORD_STATE '/' constant_integer emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_StateDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $6);
			$$->setChild(2, $5);
		}
	;

controller_state
	: identifier '=' KEYWORD_STATE controller_state_compound_statement
		{
			$$ = AST->createNode(PT_StateDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
		}
	| identifier '=' KEYWORD_STATE '/' constant_integer controller_state_compound_statement
		{
			$$ = AST->createNode(PT_StateDecl, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $6);
			$$->setChild(2, $5);
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

event_compound_statement
	: '{' '}'
		{
			$$ = 0;
		}
	| '{' event_statement_list '}'
		{
			$$ = $2;
		}
	;
	
emitter_state_compound_statement
	: '{' '}'
		{
			$$ = 0;
		}
	| '{' emitter_state_statement_list '}'
		{
			$$ = $2;
		}
	;

controller_state_compound_statement
	: '{' '}'
		{
			$$ = 0;
		}
	| '{' controller_state_statement_list '}'
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
	
event_statement_list
	: event_statement
		{
			$$ = $1;
		}
	| event_statement_list event_statement
		{
			$$ = AST->createNode(PT_StatementList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;

emitter_state_statement_list
	: emitter_state_statement
		{
			$$ = $1;
		}
	| emitter_state_statement_list emitter_state_statement
		{
			$$ = AST->createNode(PT_StatementList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $2);
		}			
	;
	
controller_state_statement_list
	: controller_state_statement
		{
			$$ = $1;
		}
	| controller_state_statement_list controller_state_statement
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
	| function_selection_statement
		{
			$$ = $1;
		}
	| simple_assignment_statement
		{
			$$ = $1;
		}
	| extended_assignment_statement ';'
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
	| jump_statement
		{
			$$ = $1;
		}
	| wait_statement
		{
			$$ = $1;
		}
	| emit_statement
		{
			$$ = $1;
		}
	| die_statement
		{
			$$ = $1;
		}
	;
	
event_statement
	: expression_statement
		{
			$$ = $1;
		}
	| event_selection_statement
		{
			$$ = $1;
		}
	| simple_assignment_statement
		{
			$$ = $1;
		}
	| extended_assignment_statement ';'
		{
			$$ = $1;
		}
	| emitter_member_statement
		{
			$$ = $1;
		}
	| event_iteration_statement
		{
			$$ = $1;
		}
	| jump_statement
		{
			$$ = $1;
		}
	| goto_statement
		{
			$$ = $1;
		}
	| member_goto_statement
		{
			$$ = $1;
		}
	| raise_statement
		{
			$$ = $1;
		}
	| suspend_statement
		{
			$$ = $1;
		}
	| member_suspend_statement
		{
			$$ = $1;
		}
	| signal_statement
		{
			$$ = $1;
		}
	| member_signal_statement
		{
			$$ = $1;
		}
	;

emitter_state_statement
	: expression_statement
		{
			$$ = $1;
		}
	| emitter_state_selection_statement
		{
			$$ = $1;
		}
	| simple_assignment_statement
		{
			$$ = $1;
		}
	| extended_assignment_statement ';'
		{
			$$ = $1;
		}
	| emitter_state_iteration_statement
		{
			$$ = $1;
		}
	| jump_statement
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
	| emit_statement
		{
			$$ = $1;
		}
	;

controller_state_statement
	: expression_statement
		{
			$$ = $1;
		}
	| controller_state_selection_statement
		{
			$$ = $1;
		}
	| simple_assignment_statement
		{
			$$ = $1;
		}
	| extended_assignment_statement ';'
		{
			$$ = $1;
		}
	| emitter_member_statement
		{
			$$ = $1;
		}
	| controller_state_iteration_statement
		{
			$$ = $1;
		}
	| jump_statement
		{
			$$ = $1;
		}
	| goto_statement
		{
			$$ = $1;
		}
	| member_goto_statement
		{
			$$ = $1;
		}
	| wait_statement
		{
			$$ = $1;
		}
	| suspend_statement
		{
			$$ = $1;
		}
	| member_suspend_statement
		{
			$$ = $1;
		}
	| member_signal_statement
		{
			$$ = $1;
		}
	| raise_statement
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
	
function_selection_statement
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
	| KEYWORD_IF '(' constant_expression ')' function_compound_statement KEYWORD_ELSE function_selection_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	;	

event_selection_statement
	: KEYWORD_IF '(' constant_expression ')' event_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_IF '(' constant_expression ')' event_compound_statement KEYWORD_ELSE event_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	| KEYWORD_IF '(' constant_expression ')' event_compound_statement KEYWORD_ELSE event_selection_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	;	

emitter_state_selection_statement
	: KEYWORD_IF '(' constant_expression ')' emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_IF '(' constant_expression ')' emitter_state_compound_statement KEYWORD_ELSE emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	| KEYWORD_IF '(' constant_expression ')' emitter_state_compound_statement KEYWORD_ELSE emitter_state_selection_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	;	

controller_state_selection_statement
	: KEYWORD_IF '(' constant_expression ')' controller_state_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_IF '(' constant_expression ')' controller_state_compound_statement KEYWORD_ELSE controller_state_compound_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	| KEYWORD_IF '(' constant_expression ')' controller_state_compound_statement KEYWORD_ELSE controller_state_selection_statement
		{
			$$ = AST->createNode(PT_IfStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
			$$->setChild(2, $7);
		}
	;	

simple_assignment_statement
	: identifier '=' constant_expression ';'
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
		
extended_assignment_statement		
	: identifier SYMBOL_INC
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, $$, $1);
		}
	| identifier SYMBOL_DEC
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, $$, $1);
		}
	| identifier SYMBOL_ADD_A constant_expression
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, $$, $1, $3);
		}
	| identifier SYMBOL_SUB_A constant_expression
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, $$, $1, $3);
		}
	| identifier SYMBOL_MUL_A constant_expression
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, $$, $1, $3);
		}
	| identifier SYMBOL_DIV_A constant_expression
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, $$, $1, $3);
		}
	;

emitter_member_statement
	: emitter_member '=' constant_expression ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| emitter_member '=' '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $4);
			$$->setChild(2, $6);
		}
	| emitter_member SYMBOL_INC ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, $$, $1);
		}
	| emitter_member SYMBOL_DEC ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, $$, $1);
		}
	| emitter_member SYMBOL_ADD_A constant_expression ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, $$, $1, $3);
		}
	| emitter_member SYMBOL_SUB_A constant_expression ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, $$, $1, $3);
		}
	| emitter_member SYMBOL_MUL_A constant_expression ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, $$, $1, $3);
		}
	| emitter_member SYMBOL_DIV_A constant_expression ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, $$, $1, $3);
		}
	| emitter_member SYMBOL_ADD_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, $$, $1, $4);
			$$->setChild(2, $6);
		}
	| emitter_member SYMBOL_SUB_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, $$, $1, $4);
			$$->setChild(2, $6);
		}
	| emitter_member SYMBOL_MUL_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, $$, $1, $4);
			$$->setChild(2, $6);
		}
	| emitter_member SYMBOL_DIV_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, $$, $1, $4);
			$$->setChild(2, $6);
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
	| property SYMBOL_INC ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, $$, $1);
		}
	| property SYMBOL_DEC ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, $$, $1);
		}
	| property SYMBOL_ADD_A constant_expression ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, $$, $1, $3);
		}
	| property SYMBOL_SUB_A constant_expression ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, $$, $1, $3);
		}
	| property SYMBOL_MUL_A constant_expression ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, $$, $1, $3);
		}
	| property SYMBOL_DIV_A constant_expression ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, $$, $1, $3);
		}
	| property SYMBOL_ADD_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, $$, $1, $4);
			$$->setChild(2, $6);
		}
	| property SYMBOL_SUB_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, $$, $1, $4);
			$$->setChild(2, $6);
		}
	| property SYMBOL_MUL_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, $$, $1, $4);
			$$->setChild(2, $6);
		}
	| property SYMBOL_DIV_A '{' constant_expression ',' constant_expression '}' ';'
		{
			$$ = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, $$, $1, $4);
			$$->setChild(2, $6);
		}
	;
	
for_update_statement
	: constant_expression
		{
			$$ = $1;
		}
	| identifier '=' constant_expression
		{
			$$ = AST->createNode(PT_AssignStatement, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	| extended_assignment_statement
		{
			$$ = $1;
		}
	;
		
function_iteration_statement
	: KEYWORD_WHILE '(' constant_expression ')' function_compound_statement
		{
			$$ = AST->createNode(PT_WhileStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_FOR '(' ';' constant_expression ';' for_update_statement ')' function_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			$$->setChild(1, $4);
			$$->setChild(2, $6);
			$$->setChild(3, $8);			
		}
	| KEYWORD_FOR '(' identifier '=' constant_expression ';' constant_expression ';' for_update_statement ')' function_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, $3);
			initExpr->setChild(1, $5);
			
			$$->setChild(0, initExpr);
			$$->setChild(1, $7);
			$$->setChild(2, $9);
			$$->setChild(3, $11);			
		}
	;

event_iteration_statement
	: KEYWORD_WHILE '(' constant_expression ')' event_compound_statement
		{
			$$ = AST->createNode(PT_WhileStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_FOR '(' ';' constant_expression ';' for_update_statement ')' event_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			$$->setChild(1, $4);
			$$->setChild(2, $6);
			$$->setChild(3, $8);			
		}
	| KEYWORD_FOR '(' identifier '=' constant_expression ';' constant_expression ';' for_update_statement ')' event_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, $3);
			initExpr->setChild(1, $5);
			
			$$->setChild(0, initExpr);
			$$->setChild(1, $7);
			$$->setChild(2, $9);
			$$->setChild(3, $11);			
		}
	;

emitter_state_iteration_statement
	: KEYWORD_WHILE '(' constant_expression ')' emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_WhileStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_FOR '(' ';' constant_expression ';' for_update_statement ')' emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			$$->setChild(1, $4);
			$$->setChild(2, $6);
			$$->setChild(3, $8);			
		}
	| KEYWORD_FOR '(' identifier '=' constant_expression ';' constant_expression ';' for_update_statement ')' emitter_state_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, $3);
			initExpr->setChild(1, $5);
			
			$$->setChild(0, initExpr);
			$$->setChild(1, $7);
			$$->setChild(2, $9);
			$$->setChild(3, $11);			
		}
	;

controller_state_iteration_statement
	: KEYWORD_WHILE '(' constant_expression ')' controller_state_compound_statement
		{
			$$ = AST->createNode(PT_WhileStatement, yylineno);
			$$->setChild(0, $3);
			$$->setChild(1, $5);
		}
	| KEYWORD_FOR '(' ';' constant_expression ';' for_update_statement ')' controller_state_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			$$->setChild(1, $4);
			$$->setChild(2, $6);
			$$->setChild(3, $8);			
		}
	| KEYWORD_FOR '(' identifier '=' constant_expression ';' constant_expression ';' for_update_statement ')' controller_state_compound_statement
		{
			$$ = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, $3);
			initExpr->setChild(1, $5);
			
			$$->setChild(0, initExpr);
			$$->setChild(1, $7);
			$$->setChild(2, $9);
			$$->setChild(3, $11);			
		}
	;

jump_statement
	: KEYWORD_BREAK ';'
		{
			$$ = AST->createNode(PT_BreakStatement, yylineno);
		}
	| KEYWORD_CONTINUE ';'
		{
			$$ = AST->createNode(PT_ContinueStatement, yylineno);
		}
	;

goto_statement
	: KEYWORD_GOTO identifier ';'
		{
			$$ = AST->createNode(PT_GotoStatement, yylineno);
			$$->setChild(0, $2);
		}		
	;
	
member_goto_statement
	: KEYWORD_GOTO emitter_member ';'
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
	
suspend_statement
	: KEYWORD_SUSPEND ';'
		{
			$$ = AST->createNode(PT_SuspendStatement, yylineno);
		}
	| KEYWORD_SUSPEND '(' unsigned_constant_arg_list ')' ';'
		{
			$$ = AST->createNode(PT_SuspendStatement, yylineno);
			$$->setChild(0, $3);
		}
	;

member_suspend_statement
	: KEYWORD_SUSPEND '$' identifier ';'
		{
			$$ = AST->createNode(PT_SuspendStatement, yylineno);
			$$->setChild(1, $3);
		}
	| KEYWORD_SUSPEND '$' identifier '(' unsigned_constant_arg_list ')' ';'
		{
			$$ = AST->createNode(PT_SuspendStatement, yylineno);
			$$->setChild(0, $5);
			$$->setChild(1, $3);
		}
	;
			
signal_statement
	: KEYWORD_SIGNAL ';'
		{
			$$ = AST->createNode(PT_SignalStatement, yylineno);
		}
	| KEYWORD_SIGNAL '(' unsigned_constant_arg_list ')' ';'
		{
			$$ = AST->createNode(PT_SignalStatement, yylineno);
			$$->setChild(0, $3);
		}
	;

member_signal_statement
	: KEYWORD_SIGNAL '$' identifier ';'
		{
			$$ = AST->createNode(PT_SignalStatement, yylineno);
			$$->setChild(1, $3);
		}
	| KEYWORD_SIGNAL '$' identifier '(' unsigned_constant_arg_list ')' ';'
		{
			$$ = AST->createNode(PT_SignalStatement, yylineno);
			$$->setChild(0, $5);
			$$->setChild(1, $3);
		}
	;
	
emit_statement
	: identifier identifier function_call_arguments ':' controller_list ';'
		{
			$$ = AST->createNode(PT_EmitStatement, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;
			
			$$->setChild(0, $1);
			$$->setChild(1, $3);
			$$->setChild(3, $5);
		}
	| identifier identifier function_call_arguments ';'
		{
			$$ = AST->createNode(PT_EmitStatement, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;
			
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
controller_list
	: controller_entry
		{
			$$ = $1;
		}
	| controller_list ',' controller_entry
		{
			$$ = AST->createNode(PT_ControllerList, yylineno);
			$$->setChild(0, $1);
			$$->setChild(1, $3);
		}
	;
	
controller_entry
	: function_call
		{
			$$ = $1;
		}
	| identifier
		{
			$$ = $1;
			$$->_setType(PT_AffectorCall);
		}
	| anchor
		{
			$$ = $1;
		}
	;
	
anchor
	: '&' identifier
		{
			$$ = AST->createNode(PT_Anchor, yylineno);
			$$->setChild(0, $2);
		}
	;
			
	
die_statement
	: KEYWORD_DIE ';'
		{	
			$$ = AST->createNode(PT_DieStatement, yylineno);
		}
	;
	
raise_statement
	: KEYWORD_RAISE function_call ';'
		{
			$$ = AST->createNode(PT_RaiseStatement, yylineno);
			$$->setChild(0, $2);
		}
	| KEYWORD_RAISE identifier ';'
		{
			$$ = AST->createNode(PT_RaiseStatement, yylineno);
			$$->setChild(0, $2);
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
	| emitter_member
		{
			$$ = $1;
		}
	| function_call
		{
			$$ = $1;
		}
	| unsigned_constant
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
	
emitter_member
	: '$' identifier '.' identifier
		{
			$$ = AST->createNode(PT_EmitterMember, yylineno);
			$$->setString($2->getStringData().c_str());
			delete $2;
			
			$$->setChild(0, $4);
		}
	;

signed_constant
	: unsigned_constant
		{
			$$ = $1;
		}
	| '+' unsigned_constant
		{
			$$ = $1;
		}
	| '-' unsigned_constant
		{
			$2->setValue(-($2->getValueData()));
			$$ = $2;
		}
	;

unsigned_constant
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

	
	
