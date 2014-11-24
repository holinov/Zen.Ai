#include <zenai/action_steps.h>
#include <zenai/context.h>

namespace Zen
{
    namespace AI
    {
        namespace Steps
        {

            bool StepsAction::applyToContext(Context *ctx)
            {
                StepContext *sctx = new StepContext();
                Log::MTLog::Instance().Debug() << "StepsAction " << _steps.size();
                bool res=true;
                int idx=0;
                for (auto && step : _steps)
                {
                    Log::MTLog::Instance().Debug() << "StepsAction step: " << idx++;
                    if(!step->applyToContext(ctx, sctx))
                    {
                        res = false;
                        break;
                    }
                }
                return res;
            }

            bool StepsAction::isApplyable(Context *ctx)
            {
                StepContext *sctx = new StepContext();
                for (auto && step : _steps)
                {
                    if (!step->isApplyable(ctx, sctx))
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
}