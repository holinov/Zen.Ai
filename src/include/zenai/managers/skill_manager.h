#pragma once
#include <zenai/stdafx.h>
#include <zenai/action.h>
#include <zenai/skill.h>
#include <zenai/manager.h>
#include <zenai/character.h>

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
                Manager<Action> *actMgr = Manager<Action>::instance();

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

        class CompositeSkillManager
        {
        private:
            Manager<Skill> *_skillManager;
            static const IdType MIN_COMPOSITE_IDX = 10000;
        public:
            CompositeSkillManager()
            {
                _skillManager = Manager<Skill>::instance();
            };

            CompositeSkill *makeCompositeSkill(std::vector<Skill *> components)
            {
                static IdType curIdx = MIN_COMPOSITE_IDX;
                CompositeSkill *cSkill = new CompositeSkill(curIdx++, "Composite skill", components);
                return cSkill;
            }

            CompositeSkill *addCompositeSkill(CompositeSkill *cSkill)
            {
                _skillManager->set(cSkill->id(), cSkill);
                return cSkill;
            }

            CompositeSkill *addCompositeSkill(const std::vector<Skill *> components)
            {
                return addCompositeSkill(makeCompositeSkill(components));
            }

            CompositeSkill *addCompositeSkill(const std::vector<IdType> componentIds)
            {
                std::vector<Skill *> skills;
                for (auto && id : componentIds)
                {
                    skills.push_back(_skillManager->get(id));
                }
                return addCompositeSkill(skills);
            }

            CompositeSkill *findCompositeInHistory(IdType wishId, SkillHistoryManager *skillHistoryManager)
            {
                auto history = skillHistoryManager->get();
                std::vector<IdType> skillIds;
                bool found = false;
                //сканируем историю до первого попадания умения с нужным желанием
                for (auto i = history.begin(); i != history.end(); ++i)
                {
                    SkillResult sr = *i;
                    skillIds.push_back(sr.SkillId);
                    auto wishMap = sr.affectedWishes();

                    //если нашли нужное желание - завершить поиск
                    if (wishMap.find(wishId) != wishMap.end())
                    {
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    CompositeSkill *cSkill = addCompositeSkill(skillIds);
                    return cSkill;
                }
                else
                {
                    return nullptr;
                }
            }
        };
    }
}