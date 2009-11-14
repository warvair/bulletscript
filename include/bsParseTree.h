#ifndef __BS_PARSETREE_H__
#define __BS_PARSETREE_H__

#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsEmitterDefinition.h"
#include "bsControllerDefinition.h"

namespace BS_NMSP
{
	enum ControllerNode
	{
		PT_ControllerMemberNode,
		PT_ControllerEmitterNode,
		PT_ControllerEventNode,
		PT_ControllerStateNode
	};

	enum EmitterNode
	{
		PT_EmitterMemberNode,
		PT_EmitterAffectorNode,
		PT_EmitterFunctionNode,
		PT_EmitterStateNode
	};

	enum CodeBlockType
	{
		CBT_None,
		CBT_MemberDeclaration,
		CBT_AffectorArgument,
		CBT_EmitterState,
		CBT_ControllerState,
		CBT_Function,
		CBT_Event
	};

	// Node types
	enum PT_NodeType
	{
		PT_Null,
		PT_DefinitionList,
		PT_ControllerDefinition,
		PT_EmitterDefinition,
		PT_MemberList,
		PT_AffectorDeclList,
		PT_AffectorDecl,
		PT_AffectorCall,
		PT_EmitterList,
		PT_Emitter,
		PT_EmitterArgList,
		PT_FunctionList,
		PT_Function,
		PT_FunctionArg,
		PT_FunctionArgList,
		PT_ControllerList,
		PT_EventList,
		PT_Event,
		PT_StateList,
		PT_State,
		PT_StatementList,
		PT_Statement,
		PT_IfStatement,
		PT_AssignStatement,
		PT_MemberAssignStatement,
		PT_WhileStatement,
		PT_BreakStatement,
		PT_ContinueStatement,
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
		PT_EmitterMember,
		PT_Constant
	};

	class ScriptMachine;
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

	class FireType;

	class ParseTree
	{
		ScriptMachine* mScriptMachine;

		ParseTreeNode* mRoot;

		int mNumErrors;

		static ParseTree* msInstance;

		void create();
		
		void destroy();

		// Core definition creation
		void createEmitterDefinitions(ParseTreeNode* node);

		EmitterDefinition* createEmitterDefinition(ParseTreeNode* node);

		void createControllerDefinitions(ParseTreeNode* node, const MemberVariableDeclarationMap& memberDecls);

		ControllerDefinition* createControllerDefinition(ParseTreeNode* node, const MemberVariableDeclarationMap& memberDecls);

		// Member variables
		void createMemberVariables(ObjectDefinition* def, ParseTreeNode* node);

		void addMemberVariables(ObjectDefinition* def, const MemberVariableDeclarationMap* memberDecls = 0);

		// Affectors
		void createAffectors(EmitterDefinition* def, ParseTreeNode* node);

		bool checkAffectorArguments(EmitterDefinition* def, ParseTreeNode* node);

		void setAffectorRecalculationType(EmitterDefinition* def, Affector* affector, ParseTreeNode* node);

		// Emitter variables
		void createEmitterVariables(ControllerDefinition* def, ParseTreeNode* node);

		// Functions
		void addFunctionArguments(EmitterDefinition* def, ParseTreeNode* node, 
			EmitterDefinition::Function& func);	

		void addFunctions(EmitterDefinition* def, ParseTreeNode* node);

		void buildFunctions(EmitterDefinition* def, ParseTreeNode* node);

		void checkFunctionProperties(ParseTreeNode* node, FireType* type);

		void checkFunctionDieStatements(ParseTreeNode* node, FireType* type);

		// Events
		void addEventArguments(ControllerDefinition* def, ParseTreeNode* node, 
			ControllerDefinition::Event& evt);	

		void addEvents(ControllerDefinition* def, ParseTreeNode* node);

		void buildEvents(ControllerDefinition* def, ParseTreeNode* node);

		// States
		void addStates(ObjectDefinition* def, ParseTreeNode* node);

		void buildStates(ObjectDefinition* def, ParseTreeNode* node);

		// Fire statements
		void _checkFireStatements(EmitterDefinition* def, ParseTreeNode* node, const String& type);

		void checkFireStatements(EmitterDefinition* def, ParseTreeNode* node);

		void checkFireControllers(EmitterDefinition* def, ParseTreeNode* node, int& ctrls, 
			FireType* ft, CodeBlockType type, const String& typeName);

		// Code generation
		void createMemberVariableBytecode(ObjectDefinition* def, ParseTreeNode* node, bool first);

		void generateFireTail(EmitterDefinition* def, ParseTreeNode* node, BytecodeBlock* bytecode, 
			FireType* ft, CodeBlockType codeType);

		void generateBytecode(ObjectDefinition* def, ParseTreeNode* node, BytecodeBlock* bytecode,
			CodeBlockType codeType, bool reset = false);

		// Utility functions
		bool checkConstantExpression(ObjectDefinition* def, CodeBlockType type, const String& name,
			ParseTreeNode* node);

		void countFunctionCallArguments(ParseTreeNode* node, int& numArguments);

		void getEmitterVariableArguments(ParseTreeNode* node, bstype emitArgs[NUM_SPECIAL_MEMBERS],
			int& numArguments);

	protected:

		// Protected for singleton implementation.
		ParseTree();

	public:

		~ParseTree();

		void reset();

		static ParseTree* instancePtr();

		void setMachines(ScriptMachine* scriptMachine);

		void addError(int line, const String& msg);

		ParseTreeNode* getRootNode();

		ParseTreeNode* createNode(int type, int line);

		void foldConstants();

		int getNumErrors() const;

		void createDefinitions(ParseTreeNode* node,	const MemberVariableDeclarationMap& memberDecls);

		int createCodeRecord(const String& type, const String& typeName,
			const String& blockType, const String& blockName);

		CodeRecord* getCodeRecord(const String& type, const String& typeName,
			const String& blockType, const String& blockName) const;

		int getCodeRecordIndex(const String& type, const String& typeName,
			const String& blockType, const String& blockName) const;

		void print(ParseTreeNode* node, int indent);

	private:

		// Helpers for building
		std::vector<String> mCodeblockNames;

		struct AffectorInfo
		{
			String name;
			String function;
			int numArgs;
			ParseTreeNode* node;
		};

		std::vector<AffectorInfo> mAffectors;

		std::list<int> mStateIndices;

		std::list<int> mFunctionIndices;

		std::list<int> mEventIndices;

		std::list<std::list<uint32> > mBreakLocations;

		std::list<std::list<uint32> > mContinueLocations;

		String getCodeRecordName(const String& type, const String& typeName,
			const String& blockType, const String& blockName) const;
	};

}

#endif
