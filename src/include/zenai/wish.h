#pragma once
#include "stdafx.h"
#include "skill.h"

namespace Zen
{
    namespace AI
    {
        class SkillResult ;

        /**
         * @brief Желание существа
         */
        class Wish : public HasId, public HasName
        {
        private:
            std::vector<SkillResult> _histroy;
        public:
            Wish(IdType id, std::string name)
                : HasId(id)
                , HasName(name)
                , _histroy()
            {};

            Wish()
                : Wish(0, "")
            {};

            Wish(Wish &o)
                : _histroy(o._histroy)
            {
                id(o.id());
                name(o.name());
            };
        };

        /**
         * @brief Информация о желании существа
         */
        struct WishInfo
        {
        private:
            IdType _wishId;
            int _wishLevel;
            std::vector<SkillResult> _histroy;

        public:
            WishInfo(IdType wishId, int wishLevel, std::vector<SkillResult> histroy)
                : _wishId(wishId)
                , _wishLevel(wishLevel)
                , _histroy(histroy)
            {};


            WishInfo(IdType wishId, int wishLevel)
                : _wishId(wishId)
                , _wishLevel(wishLevel)
                , _histroy()
            {};
            WishInfo(Wish *w, int lvl) : WishInfo(w->id(), lvl) {}
            WishInfo(): WishInfo((IdType)0, 0) {}

            WishInfo(const WishInfo &o)
                : _wishId(o._wishId)
                , _wishLevel(o._wishLevel)
                , _histroy(o._histroy)
            {}

            /**
             * @brief ИД типа желания
             */
            inline const IdType wishId()
            {
                return _wishId;
            }

            /**
             * @brief ИД типа желания
             */
            inline void wishId(IdType id)
            {
                _wishId = id;
            }

            /**
             * @brief Уровень желания
             */
            inline const int wishLvl()
            {
                return _wishLevel;
            }

            /**
             * @brief Уровень желания
             */
            inline void wishLvl(int lvl)
            {
                _wishLevel = lvl;
            }

            /**
             * @brief Увеличить уровень желания
             */
            inline void addWishLvl(int lvl)
            {
                int lnvl = _wishLevel += lvl;
                if (lnvl < 0) lnvl = 0;
                wishLvl(lnvl);
            }

            /**
             * @brief Получить историю удовлетворения желания
             */
            inline std::vector<SkillResult> history()
            {
                return _histroy;
            }

            /**
             * @brief Добавить новую запись в историю удовлетворения желания
             *
             * @param sr Пункт истории
             */
            inline void addHistroy(std::vector<SkillResult> sr)
            {
                for (auto && h : sr)
                {
                    _histroy.push_back(h);
                }
            }

            /**
             * @brief Добавить новую запись в историю удовлетворения желания
             *
             * @param sr Пункт истории
             */
            inline void addHistroy(const SkillResult& sr)
            {
                _histroy.push_back(sr);
            }
        };
    }
}