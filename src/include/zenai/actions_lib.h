#pragma once
#include "steps.h"

using namespace Zen::AI::Steps;

namespace Zen
{
    namespace AI
    {
        namespace Steps
        {
            class EatRawAction : public StepsAction
            {
            public:
                EatRawAction();/* : StepsAction(0, "Eat raw", 1 , {{0, 12}})
                {
                    _steps.push_back(new FindBestResourceOfTypeStep(ResourceTypes::FOOD));
                    _steps.push_back(new ConsumeStep(1));
                    _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Energy));
                    _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Food));
                    _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Water));
                }*/
            };

            class CollectFoodAction : public StepsAction
            {
            public:
                CollectFoodAction();/* : StepsAction(1, "Collect food", 2, {{0, 10}})
                {
                    _steps.push_back(new FindBestResourceOfTypeStep(ResourceTypes::FOOD));
                    _steps.push_back(new LootStep());
                }*/
            };

            class RestAction : public StepsAction
            {
            public:
                RestAction();/* : StepsAction(2, "Rest", 1 , {{1, 10}})
                {
                    _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Energy, 5));
                }*/
            };
        }
    }
}