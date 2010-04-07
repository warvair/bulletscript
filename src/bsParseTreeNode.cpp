#include "bsParseTreeNode.h"
#include "bsParseTree.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
ParseTreeNode::ParseTreeNode(int type, int line, ScriptMachine* scriptMachine,
							 ParseTree* tree) :
	mTree(tree),
	mParent(0),
	mScriptMachine(scriptMachine),
	mType(type),
	mLine(line)
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
		mChildren[i] = 0;
}
// --------------------------------------------------------------------------------
ParseTreeNode::~ParseTreeNode()
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
		delete mChildren[i];
}
// --------------------------------------------------------------------------------
void ParseTreeNode::_setType(int type)
{
	mType = type;
}
// --------------------------------------------------------------------------------
void ParseTreeNode::setChild(int index, ParseTreeNode *node)
{
	mChildren[index] = node;
	if (mChildren[index])
		mChildren[index]->mParent = this;
}
// --------------------------------------------------------------------------------
ParseTreeNode* ParseTreeNode::getChild(int index) const
{
	return mChildren[index];
}
// --------------------------------------------------------------------------------
ParseTreeNode* ParseTreeNode::getParent() const
{
	return mParent;
}
// --------------------------------------------------------------------------------
ParseTree* ParseTreeNode::getTree() const
{
	return mTree;
}
// --------------------------------------------------------------------------------
int ParseTreeNode::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
int ParseTreeNode::getLine() const
{
	return mLine;
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldBinaryNode()
{
	if (mChildren[0]->getType() != PT_Constant || mChildren[1]->getType() != PT_Constant)
		return;

	bstype val1 = mChildren[0]->getValueData();
	bstype val2 = mChildren[1]->getValueData();

	switch (mType)
	{
	case PT_AddStatement:
		setValue(val1 + val2);
		break;

	case PT_SubtractStatement:
		setValue(val1 - val2);
		break;

	case PT_MultiplyStatement:
		setValue(val1 * val2);
		break;

	case PT_DivideStatement:
		setValue(val1 / val2);
		break;

	case PT_RemainderStatement:
		setValue((bstype) ((int) val1 % (int) val2));
		break;

	case PT_EqualsStatement:
		setValue(val1 == val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_NotEqualsStatement:
		setValue(val1 != val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_LessThanStatement:
		setValue(val1 < val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_GreaterThanStatement:
		setValue(val1 > val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_LessThanEqStatement:
		setValue(val1 <= val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_GreaterThanEqStatement:
		setValue(val1 >= val2 ? bsvalue1 : bsvalue0);
		break;
	}

	mType = PT_Constant;
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
			mChildren[i] = 0;
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldUnaryNode()
{
	if (mChildren[0]->getType() != PT_Constant)
		return;

	bstype val = mChildren[0]->getValueData();

	switch (mType)
	{
	case PT_UnaryPosStatement:
		setValue(val);
		break;

	case PT_UnaryNegStatement:
		setValue(-val);
		break;

	case PT_ConstantExpression:
		setValue(val);
		break;
	}

	mType = PT_Constant;
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
			mChildren[i] = 0;
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldLogicalNode()
{
	if (mChildren[0]->getType () != PT_Constant || mChildren[1]->getType () != PT_Constant)
		return;

	bstype val1 = mChildren[0]->getValueData();
	bstype val2 = mChildren[1]->getValueData();

	switch (mType)
	{
	case PT_LogicalOr:
		setValue(val1 || val2 ? bsvalue1 : bsvalue0);
		break;

	case PT_LogicalAnd:
		setValue(val1 && val2 ? bsvalue1 : bsvalue0);
		break;
	}

	mType = PT_Constant;
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			delete mChildren[i];
			mChildren[i] = 0;
		}
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::foldConstants()
{
	for (int i = 0; i < MAX_CHILDREN; ++i)
	{
		if (mChildren[i])
		{
			mChildren[i]->foldConstants();
		}
	}

	switch (mType)
	{
	case PT_AddStatement:
	case PT_SubtractStatement:
	case PT_MultiplyStatement:
	case PT_DivideStatement:
	case PT_RemainderStatement:
	case PT_EqualsStatement:
	case PT_NotEqualsStatement:
	case PT_LessThanStatement:
	case PT_GreaterThanStatement:
	case PT_LessThanEqStatement:
	case PT_GreaterThanEqStatement:
		foldBinaryNode();
		break;

	case PT_UnaryPosStatement:
	case PT_UnaryNegStatement:
	case PT_ConstantExpression:
		foldUnaryNode();
		break;

	case PT_LogicalOr:
	case PT_LogicalAnd:
		foldLogicalNode();
		break;

	default:
		break;
	}
}
// --------------------------------------------------------------------------------
void ParseTreeNode::setValue(bstype data)
{
	mDataType = DT_Value;
	mValueData = data;
}
// --------------------------------------------------------------------------------
void ParseTreeNode::setString(const char* data)
{
	mDataType = DT_String;
	mStringData = data;
}
// --------------------------------------------------------------------------------
int ParseTreeNode::getDataType() const
{
	return mDataType;
}
// --------------------------------------------------------------------------------
bstype ParseTreeNode::getValueData() const
{
	return mValueData;
}
// --------------------------------------------------------------------------------
const String& ParseTreeNode::getStringData() const
{
	return mStringData;
}
// --------------------------------------------------------------------------------

}