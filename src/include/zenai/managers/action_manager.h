#pragma once
#include <zenai/stdafx.h>
#include <zenai/action.h>
#include <zenai/skill.h>
#include <zenai/manager.h>
#include <zenai/actions_lib.h>


namespace Zen
{
    namespace AI
    {
        template<>
        struct ManagerLoader<Action>
        {
            std::vector<Action *> load()
            {
                return std::vector<Action *>
                {
                    //new Steps::EatRawAction(),
                    //new Steps::CollectFoodAction(),
                    //new Steps::RestAction()
                };
            }
        };
    }
}