#pragma once
#include "stdafx.h"

namespace Zen{
	namespace AI{
		class Context;

        /**
         * @brief Результат исполнения действия
         */
        struct ActionResult
        {

            /**
             * @brief ИД Умения
             */
            IdType ActionId;

            /**
             * @brief ИД Умения
             */
            IdType WishId;

            /**
             * @brief Результат действия
             */
            int Result;

            ActionResult(IdType actionId, IdType wishId, int result)
                : ActionId(actionId)
                , WishId(wishId)
                , Result(result)
            {};
        };

        /**
         * @brief Действие существа
         * @details Действие стоит определенное кол-во энергии
         * Влияет на одно или несколько желаний существа
         * Имеет требования к контексту выполнения
         */
        class Action : public HasId, public HasName
        {
        private:
            int _actionCost;
            std::map<IdType, int> _affectedWishes;

        public:
            Action(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes)
                : HasId(id)
                , HasName(name)
                , _actionCost(cost)
                , _affectedWishes(affectedWishes)
            {};
            virtual ~Action() {}

            /**
             * @brief Стоимость действия
             */
            inline const int cost() const
            {
                return _actionCost;
            }

            inline const std::map<IdType, int> affectedWishes() const{
                return _affectedWishes;
            }

            /**
             * @brief Применить результаты действия
             *
             * @param ctx Контекст ситуации
             * @param skillLvl Уровень умения с которым выполняется дейтвие
             */
            std::vector<ActionResult> applyResults(Context *ctx, int skillLvl);

            /**
             * Когда перегруженно в дочерних класах дает возможность повлиять на контекст событий
             *
             * @param ctx Контекст действий
             */
            virtual bool applyToContext(Context *ctx) = 0;

            /**
             * @brief Когда перегруженно в дочерних классах определяет возможность исполнения действия
             *
             * @param ctx Контекст действий
             * @return true если применимо к текущему контексту
             */
            virtual bool isApplyable(Context *ctx) = 0;
        };
    }
}