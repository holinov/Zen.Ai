#pragma once
#include "stdafx.h"
#include "action.h"


#include <typeinfo>

namespace Zen
{
    namespace AI
    {

        class Context;

        /**
         * @brief Результат исполнения умения
         */
        struct SkillResult
        {
            SkillResult()
                : SkillId()
                , Results()
            {}

            SkillResult(const SkillResult &o)
            : SkillId(o.SkillId)
            , Results(o.Results)
            {}


            /**
             * ИД Умения
             */
            IdType SkillId;

            /**
             * Результаты действий
             */
            std::vector<ActionResult> Results;

            /**
             * @brief Получить суммарные воздействия на желания
             */
            std::map<IdType, int> affectedWishes() const
            {
                std::map<IdType, int> res;
                for (auto && histroyPoint : Results)
                {
                    auto it = res.find(histroyPoint.WishId);
                    if ( it == res.end())
                    {
                        res[histroyPoint.WishId] =  0;
                    }

                    res[histroyPoint.WishId] += histroyPoint.Result;
                }

                return res;
            }
        };

        /**
         * @brief Умение персонажа
         */
        class Skill : public HasId, public HasName
        {
        public:
            bool applySkill(Context *ctx);
            virtual std::map<IdType, int> getAffectedWishes() = 0;
            virtual ~Skill() {}
            virtual std::vector<ActionResult> applyToContext(Context *ctx, int lvl) = 0;

        protected:
            Skill(IdType id, std::string name)
                : HasId(id)
                , HasName(name)
            {};
        };

        /**
         * @brief  Базовое умение (исполнет только одно действие
         */
        class BasicSkill : public Skill
        {
        private:
            Action *_action;
        public:
            BasicSkill(Action *action)
                : Skill(action->id(), action->name())
                , _action(action)
            {};

            virtual std::map<IdType, int> getAffectedWishes()
            {
                return _action->affectedWishes();
            }

        protected:
            virtual std::vector<ActionResult> applyToContext(Context *ctx, int lvl)
            {
                //Просто исполняем действие
                return _action->applyResults(ctx, lvl);
            };
        };

        class CompositeSkill : public Skill
        {
        private:
            std::vector<Skill *> _skills;
        public:
            CompositeSkill(IdType id, std::string name, std::vector<Skill *> skills)
                : Skill(id, name)
                , _skills(skills)
            {}

            virtual std::map<IdType, int> getAffectedWishes()
            {
                std::map<IdType, int> summary;
                for (auto && skill : _skills)
                {
                    std::map<IdType, int> inner = skill->getAffectedWishes();
                    for (auto && wish : inner)
                    {
                        if (summary.find(wish.first) == summary.end())
                        {
                            summary[wish.first] = 0;
                        }
                        summary[wish.first] += wish.second;
                    }
                }
                return summary;
            }

        protected:
            virtual std::vector<ActionResult> applyToContext(Context *ctx, int lvl)
            {
                std::vector<ActionResult> results;
                for (auto && skill : _skills)
                {
                    for (auto && res : skill->applyToContext(ctx, lvl))
                    {
                        results.push_back(res);
                    }
                }
                return results;
            };
        };

        /**
         * @brief Информация о умении существа
         */
        struct SkillInfo
        {
        private:
            IdType _skillId;
            int _skillLevel;
            int _skillExp;

        public:
            SkillInfo(IdType wishId, int wishLevel, std::vector<SkillResult> histroy)
                : _skillId(wishId)
                , _skillLevel(wishLevel)
                , _skillExp(0)
                //, _histroy(histroy)
            {};


            SkillInfo(IdType wishId, int wishLevel)
                : _skillId(wishId)
                , _skillLevel(wishLevel)
                , _skillExp(0)
                //, _histroy()
            {};
            SkillInfo(Skill *s, int lvl) : SkillInfo(s->id(), lvl) {}
            SkillInfo(): SkillInfo((IdType)0, 0) {}

            SkillInfo(const SkillInfo &o)
                : _skillId(o._skillId)
                , _skillLevel(o._skillLevel)
                , _skillExp(0)
                //, _histroy(o._histroy)
            {}

            /**
             * @brief ИД типа умения
             */
            inline const IdType skillId()
            {
                return _skillId;
            }

            /**
             * @brief ИД типа умения
             */
            inline void skillId(IdType id)
            {
                _skillId = id;
            }

            /**
             * @brief Уровень умения
             */
            inline const int skillLvl()
            {
                return _skillLevel;
            }

            /**
             * @brief Уровень умения
             */
            inline void skillLvl(int lvl)
            {
                _skillLevel = lvl;
            }

            /**
             * @brief Уровень умения
             */
            inline const int skillExp()
            {
                return _skillExp;
            }

            /**
             * @brief Уровень умения
             */
            inline void skillExp(int lvl)
            {
                _skillExp = lvl;
            }

            /**
             * @brief Уровень умения
             */
            inline void skillExpInc()
            {
                ++_skillExp;
                if (_skillExp >= _skillLevel)
                {
                    ++_skillLevel;
                    _skillExp = 0;
                }
            }
        };
    }
}