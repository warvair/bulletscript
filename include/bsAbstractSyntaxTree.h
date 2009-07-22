#ifndef __BS_ABSTRACTSYNTAXTREE_H__
#define __BS_ABSTRACTSYNTAXTREE_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsGunDefinitions.h"

namespace BS_NMSP
{

	// Node types
	enum ASTNodeType
	{
		ASTN_Root,
		ASTN_GunDefinitionList,
		ASTN_BulletGunDefinition,
		ASTN_AreaGunDefinition,
		ASTN_SplineGunDefinition,
		ASTN_StateList,
		ASTN_State,
		ASTN_StatementList,
		ASTN_Statement,
		ASTN_IfStatement,
		ASTN_AssignStatement,
		ASTN_RepeatStatement,
		ASTN_GotoStatement,
		ASTN_WaitStatement,
		ASTN_SetStatement,
		ASTN_AffectorStatement,
		ASTN_AffectorCall,
		ASTN_ConstantExpression,
		ASTN_LogicalOr,
		ASTN_LogicalAnd,
		ASTN_EqualsStatement,
		ASTN_NotEqualsStatement,
		ASTN_LessThanStatement,
		ASTN_GreaterThanStatement,
		ASTN_LessThanEqStatement,
		ASTN_GreaterThanEqStatement,
		ASTN_AddStatement,
		ASTN_SubtractStatement,
		ASTN_MultiplyStatement,
		ASTN_DivideStatement,
		ASTN_RemainderStatement,
		ASTN_UnaryPosStatement,
		ASTN_UnaryNegStatement,
		ASTN_FunctionCall,
		ASTN_FunctionCallArg,
		ASTN_FunctionCallArgList,
		ASTN_Identifier,
		ASTN_Constant
	};

	class ScriptMachine;
	class BulletMachineBase;

	typedef std::vector<uint32> BytecodeBlock;

	class _BSAPI AbstractSyntaxTreeNode
	{
	public:

		static const int MAX_CHILDREN = 5;

	private:

		AbstractSyntaxTreeNode* mChildren[MAX_CHILDREN];

		// Weak pointer to script machine
		ScriptMachine* mScriptMachine;

		// Weak pointer to bullet machine
		BulletMachineBase* mBulletMachine;

		// See: ASTNodeType enum
		int mType;

		// Script line
		int mLine;

		// See: DataType enum
		int mDataType;

		float mFloatData;
		String mStringData;

		void checkRepeatDepth(int& depth);

		void countAffectorArguments(int& numArgs);

		void createAffectorArgumentsBytecode(int index,	bool newAffector);

		void foldBinaryNode();

		void foldUnaryNode();

		void foldLogicalNode();

	public:

		enum DataType
		{
			DT_Float,
			DT_String
		};

		AbstractSyntaxTreeNode(int type, int line, ScriptMachine* scriptMachine,
			BulletMachineBase* bulletMachine);

		~AbstractSyntaxTreeNode();

		void setChild(int index, AbstractSyntaxTreeNode* node);

		AbstractSyntaxTreeNode* getChild(int index) const;

		int getType() const;

		int getLine() const;

		void foldConstants();

		void setFloat(float data);

		void setString(const char* data);

		int getDataType() const;

		float getFloatData() const;

		const String& getStringData() const;

		void createGunMembers(GunDefinition* def);

		void createGunBytecode(GunDefinition* def, bool newAffector, BytecodeBlock* bytecode);

	};

	class _BSAPI AbstractSyntaxTree
	{
		static ScriptMachine* mScriptMachine;

		static BulletMachineBase* mBulletMachine;

		AbstractSyntaxTreeNode* mRoot;

		int mNumErrors;

		static AbstractSyntaxTree* msInstance;

		void create();
		
		void destroy();

		BulletGunDefinition* createBulletGunDefinition(AbstractSyntaxTreeNode* node);

		AreaGunDefinition* createAreaGunDefinition(AbstractSyntaxTreeNode* node);

		SplineGunDefinition* createSplineGunDefinition(AbstractSyntaxTreeNode* node);

	protected:

		// Protected for singleton implementation.
		AbstractSyntaxTree();

	public:

		~AbstractSyntaxTree();

		void reset();

		static AbstractSyntaxTree* instancePtr();

		static void setMachines(ScriptMachine* scriptMachine, 
								BulletMachineBase* bulletMachine);

		void addError(int line, const String& msg);

		AbstractSyntaxTreeNode* getRootNode();

		AbstractSyntaxTreeNode* createNode(int type, int line);

		void foldConstants();

		int getNumErrors() const;

		void createGunDefinitions(AbstractSyntaxTreeNode* node);
	};

}

#endif
