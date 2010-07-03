/*
	BulletScript: a script for firing bullets.
	See /doc/license.txt for license details.
*/

#ifndef __BS_PARSETREENODE_H__
#define __BS_PARSETREENODE_H__

#include "bsPrerequisites.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{
	// Node types: insert any new types at the end!
	// These values are carefully chosen to make parsing more efficient.
	enum PT_NodeType
	{
		PT_Null,
		PT_DefinitionList,
		PT_ControllerDefinition,
		PT_ControllerObjectList,
		PT_EmitterDefinition,
		PT_EmitterObjectList,
		// Emitter objects
		PT_AffectorDeclList,
		PT_AffectorDecl,
		PT_FunctionDeclList,
		PT_FunctionDecl,
		PT_StateDeclList,
		PT_StateDecl,
		PT_MemberDeclList,
		PT_MemberDecl,
		// Controller objects - including the previous state & member declaration
		PT_EmitterMemberDeclList,
		PT_EmitterMemberDecl,
		PT_EventDeclList,
		PT_EventDecl,
		// Statements
		PT_StatementList,
		PT_IfStatement,
		PT_AssignStatement,
		PT_MemberAssignStatement,
		PT_WhileStatement,
		PT_ForStatement,
		PT_BreakStatement,
		PT_ContinueStatement,
		PT_GotoStatement,
		PT_WaitStatement,
		PT_SuspendStatement,
		PT_SignalStatement,
		PT_SetStatement,
		PT_EmitStatement,
		PT_DieStatement,
		PT_RaiseStatement,
		// Constant expression nodes
		PT_ConstantExpression,
		PT_LogicalOr,
		PT_LogicalAnd,
		PT_EqualsStatement,
		PT_NotEqualsStatement,
		PT_LessThanStatement,
		PT_GreaterThanStatement,
		PT_LessThanEqStatement,
		PT_GreaterThanEqStatement,
		PT_AddStatement,
		PT_SubtractStatement,
		PT_MultiplyStatement,
		PT_DivideStatement,
		PT_RemainderStatement,
		PT_UnaryPosStatement,
		PT_UnaryNegStatement,
		PT_FunctionCall,
		// Values/text
		PT_Identifier,
		PT_Property,
		PT_Anchor,
		PT_EmitterMember,
		PT_Constant,
		// Misc
		PT_FunctionCallArg,
		PT_FunctionCallArgList,
		PT_AffectorCall,
		PT_ConstantList,
		PT_FunctionArg,
		PT_FunctionArgList,
		PT_ControllerList
	};

	class ParseTree;

	class ParseTreeNode
	{
	public:

		static const int MAX_CHILDREN = 4;

	private:

		ParseTree* mTree;

		ParseTreeNode* mChildren[MAX_CHILDREN];

		ParseTreeNode* mParent;

		// Weak pointer to script machine
		ScriptMachine* mScriptMachine;

		// See: PT_NodeType enum
		int mType;

		// Script line
		int mLine;

		// See: DataType enum
		int mDataType;

		bstype mValueData;

		String mStringData;

		void foldBinaryNode();

		void foldUnaryNode();

		void foldLogicalNode();

	public:

		enum DataType
		{
			DT_Value,
			DT_String
		};

		ParseTreeNode(int type, int line, ScriptMachine* scriptMachine,
			ParseTree* tree);

		~ParseTreeNode();

		void _setType(int type);

		void setChild(int index, ParseTreeNode* node);

		ParseTreeNode* getChild(int index) const;

		ParseTreeNode* getParent() const;

		ParseTree* getTree() const;

		int getType() const;

		int getLine() const;

		void foldConstants();

		void setValue(bstype data);

		void setString(const char* data);

		int getDataType() const;

		bstype getValueData() const;

		const String& getStringData() const;
	};

}

#endif
