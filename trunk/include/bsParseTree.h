#ifndef __BS_PARSETREE_H__
#define __BS_PARSETREE_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsGunDefinition.h"

namespace BS_NMSP
{
	enum
	{
		NameNode,
		MemberNode,
		FunctionNode,
		StateNode
	};

	// Node types
	enum PTodeType
	{
		PT_Null,
		PT_GunDefinitionList,
		PT_GunDefinition,
		PT_MemberList,
		PT_FunctionList,
		PT_Function,
		PT_FunctionArg,
		PT_FunctionArgList,
		PT_ControllerList,
		PT_StateList,
		PT_State,
		PT_StatementList,
		PT_Statement,
		PT_IfStatement,
		PT_AssignStatement,
		PT_LoopStatement,
		PT_WhileStatement,
		PT_GotoStatement,
		PT_WaitStatement,
		PT_SetStatement,
		PT_FireStatement,
		PT_DieStatement,
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
		PT_FunctionCallArg,
		PT_FunctionCallArgList,
		PT_Identifier,
		PT_Property,
		PT_Constant
	};

	class ScriptMachine;
	class ParseTree;

	class _BSAPI ParseTreeNode
	{
	public:

		static const int MAX_CHILDREN = 4;

	private:

		ParseTree* mTree;

		ParseTreeNode* mChildren[MAX_CHILDREN];

		ParseTreeNode* mParent;

		// Weak pointer to script machine
		ScriptMachine* mScriptMachine;

		// See: PTodeType enum
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

	class FireType;

	class _BSAPI ParseTree
	{
		static ScriptMachine* mScriptMachine;

		ParseTreeNode* mRoot;

		int mNumErrors;

		static ParseTree* msInstance;

		void create();
		
		void destroy();

		// Parsing
		bool checkConstantExpression(GunDefinition* def, ParseTreeNode* node);

		void checkLoopDepth(ParseTreeNode *node, int& depth);

		void createMemberVariables(GunDefinition* def, ParseTreeNode* node);

		void addMemberVariables(GunDefinition* def, const MemberVariableDeclarationMap& memberDecls);

		void countFunctionCallArguments(ParseTreeNode* node, int& numArguments);

		void addFunctionArguments(GunDefinition* def, ParseTreeNode* node, 
			GunDefinition::Function& func);	

		void addFunctions(GunDefinition* def, ParseTreeNode* node);

		void buildFunctions(GunDefinition* def, ParseTreeNode* node);

		void createStates(GunDefinition* def, ParseTreeNode* node);

		void checkFireStatements(GunDefinition* def, ParseTreeNode* node);

		void checkFireControllers(GunDefinition* def, ParseTreeNode* node, int& ctrls, int& affectors);

		void checkFunctionProperties(ParseTreeNode* node, FireType* type);

		// Code generation
		void createMemberVariableBytecode(GunDefinition* def, ParseTreeNode* node, bool first);

		void generateBytecode(GunDefinition* def, ParseTreeNode* node, BytecodeBlock* bytecode,
			bool reset = false);

		// Utility
		GunDefinition* createGunDefinition(ParseTreeNode* node,
			const MemberVariableDeclarationMap& memberDecls);

	protected:

		// Protected for singleton implementation.
		ParseTree();

	public:

		~ParseTree();

		void reset();

		static ParseTree* instancePtr();

		static void setMachines(ScriptMachine* scriptMachine);

		void addError(int line, const String& msg);

		ParseTreeNode* getRootNode();

		ParseTreeNode* createNode(int type, int line);

		void foldConstants();

		int getNumErrors() const;

		void createGunDefinitions(ParseTreeNode* node, 
			const MemberVariableDeclarationMap& memberDecls);

		int createCodeRecord(const String& type, const String& typeName,
			const String& blockType, const String& blockName);

		CodeRecord* getCodeRecord(const String& type, const String& typeName,
			const String& blockType, const String& blockName);

		int getCodeRecordIndex(const String& type, const String& typeName,
			const String& blockType, const String& blockName);

		void print(ParseTreeNode* node, int indent);

	private:

		// Helpers for building
		std::vector<String> mCodeblockNames;

		std::list<int> mStateIndices;

		std::list<int> mFunctionIndices;

		String getCodeRecordName(const String& type, const String& typeName,
			const String& blockType, const String& blockName);
	};

}

#endif
