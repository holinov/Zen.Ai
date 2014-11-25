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

        protected:
            Skill(IdType id, std::string name)
                : HasId(id)
                , HasName(name)
            {};
            virtual std::vector<ActionResult> applyToContext(Context *ctx, int lvl) = 0;
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
            CompositeSkill(IdType id, std::string name)
                : Skill(id, name)
                , _skills()
            {}
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