#ifndef __SH_BULLETAFFECTOR_H__
#define __SH_BULLETAFFECTOR_H__

#include "shPrerequisites.h"
#include "shCodeRecord.h"
#include "shScriptDefinition.h"
#include "shScriptVariables.h"

namespace Shmuppet
{

	class ScriptMachine;

	template <class BulletType>
	class _ShmuppetAPI BulletAffector
	{
	public:

		typedef void (*Function)(BulletType&, float*, float);

		class Argument : public VariableListener
		{
		public:

			enum Type
			{
				AT_Constant =		0,
				AT_Globals =		1,
				AT_Instances =		2,
				AT_Functions =		4,
			};

			ScriptMachine* scriptMachine;
			CodeRecord* record;
			int exprTypes;
			float value;

			void onChanged()
			{
				// Update value
				GunScriptRecord gsr;
				scriptMachine->processConstantExpression(record->byteCode, record->byteCodeSize, gsr);
				value = UINT32_TO_FLOAT(gsr.curStack[gsr.stackHead - 1]);
			}
		};

		BulletAffector(Function func) :
			mFunction(func)
		{
		}

		~BulletAffector()
		{
			ArgumentList::iterator it = mArguments.begin();
			while (it != mArguments.end())
			{
				delete (*it).record;
				++it;
			}
		}

		void addArgument(ScriptMachine* machine)
		{
			Argument arg;
			arg.scriptMachine = machine;
			arg.record = 0;
			arg.exprTypes = Argument::AT_Constant;
			arg.value = 0.0f;
			mArguments.push_back(arg);
		}

		Argument &getArgument(int index)
		{
			assert(index >= 0 && index < (int) mArguments.size() &&
				"BulletAffector::getArgument: out of bounds.");
			return mArguments[index];
		}

		void updateFunctionArguments()
		{
			ArgumentList::iterator it = mArguments.begin();
			while (it != mArguments.end())
			{
				Argument& arg = *it;
				if (arg.exprTypes & Argument::AT_Functions)
				{
					GunScriptRecord gsr;
					arg.scriptMachine->processConstantExpression(arg.record->byteCode, 
																 arg.record->byteCodeSize, gsr);
					arg.value = UINT32_TO_FLOAT(gsr.curStack[gsr.stackHead - 1]);
				}
				++it;
			}
		}

		void updateInstanceArguments(float* arguments, const GunScriptRecord& gunRecord)
		{
			int index = 0;
			ArgumentList::iterator it = mArguments.begin();
			while (it != mArguments.end())
			{
				Argument& arg = *it;
				if (arg.exprTypes & Argument::AT_Instances)
				{
					GunScriptRecord gsr;
					for (int i = 0; i < NUM_INSTANCE_VARS; ++i)
						gsr.instanceVars[i] = gunRecord.instanceVars[i];

					arg.scriptMachine->processConstantExpression(arg.record->byteCode, 
																 arg.record->byteCodeSize, gsr);
					arguments[index] = UINT32_TO_FLOAT(gsr.curStack[gsr.stackHead - 1]);
				}
				else
				{
					// If not an instance argument, we need to just copy the already calculated
					// value into the argument list.
					arguments[index] = arg.value;
				}

				++it;
				++index;
			}
		}

		void runFunction(BulletType& b, float* arguments, float frameTime)
		{
			mFunction(b, arguments, frameTime);
		}

	private:

		typedef std::vector<Argument> ArgumentList;
		ArgumentList mArguments;

		Function mFunction;
	};

}

#endif