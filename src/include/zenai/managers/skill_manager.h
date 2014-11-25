#pragma once
#include "../stdafx.h"
#include "../action.h"
#include "../skill.h"
#include "../manager.h"


namespace Zen
{
    namespace AI
    {
        template<>
        struct ManagerLoader<Skill>
        {
        private:
            std::vector<Skill *> getBasicSkills()
            {
                std::vector<Skill *> skills;
                Manager<Action>* actMgr = Manager<Action>::instance();
 
                for (auto && act : actMgr->getAll())
                {
                    BasicSkill *s = new BasicSkill(act);
                    skills.push_back(s);
                }

                return skills;
            }

        public:
            std::vector<Skill *> load()
            {
                return getBasicSkills();
            }
        };

    }
}