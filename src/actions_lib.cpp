#include <zenai/actions_lib.h>
#include <zenai/item.h>
#include <zenai/character.h>

using namespace Zen::AI::Steps;

namespace Zen
{
    namespace AI
    {
        namespace Steps
        {

            EatRawAction::EatRawAction(): StepsAction(0, "Eat raw", 1 , {{0, 12}})
            {
                _steps.push_back(new FindBestResourceOfTypeStep(ResourceTypes::FOOD));
                _steps.push_back(new ConsumeStep(1));
                _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Energy));
                _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Food));
                _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Water));
            }

            CollectFoodAction::CollectFoodAction() : StepsAction(1, "Collect food", 2, {{0, 1}})
            {
                _steps.push_back(new FindBestResourceOfTypeStep(ResourceTypes::FOOD));
                _steps.push_back(new LootStep());
            }

            RestAction::RestAction() : StepsAction(2, "Rest", 1 , {{1, 10}})
            {
                _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Energy, 5));
            }
        }
    }
}