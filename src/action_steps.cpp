#include "action_steps.h"
#include "context.h"

namespace Zen
{
    namespace AI
    {
        namespace Steps
        {

            bool StepsAction::applyToContext(Context *ctx)
            {
                StepContext *sctx = new StepContext();
                for (auto && step : _steps)
                {
                    step->applyToContext(ctx, sctx);
                    {
                        return false;
                    }
                }
                return true;
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