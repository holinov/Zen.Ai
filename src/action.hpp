#pragma once
#include "stdafx.h"
#include "context.hpp"

namespace Zen{
	namespace AI{

		/**
		 * @brief Результат исполнения действия
		 */
		struct ActionResult {
			
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
				:ActionId(actionId)
				,WishId(wishId)
				,Result(result)
			{};
		};

		/**
		 * @brief Действие существа
		 * @details Действие стоит определенное кол-во энергии
		 * Влияет на одно или несколько желаний существа
		 * Имеет требования к контексту выполнения
		 */
		class Action : public HasId, public HasName{
		private:
			int _actionCost;
			std::map<IdType,int> _affectedWishes;

		public:
			Action(IdType id, std::string name, int cost, std::map<IdType,int> affectedWishes) 
				: HasId(id)
				, HasName(name)
				, _actionCost(cost)
				, _affectedWishes(affectedWishes)
			{};

			/**
			 * @brief Стоимость действия
			 */
			inline const int cost(){ return _actionCost; }

			/**
			 * @brief Применить результаты действия
			 * 
			 * @param ctx Контекст ситуации
			 * @param skillLvl Уровень умения с которым выполняется дейтвие
			 */
			std::vector<ActionResult> applyResults(Context& ctx, int skillLvl){
				std::vector<ActionResult> res;
				for(auto&& wish : _affectedWishes) {
					//Изменени уровня желания = Базовый уровень + Базовый уровень % Уровень умения
					int modifyLvl = wish.second + wish.second / 100 * skillLvl;

					//Прменить изменения уровня желания
					ctx.actorInfo().modifyWish(wish.first,modifyLvl);

					//Формируем запись в историю
					res.push_back(ActionResult(id(),wish.first,modifyLvl));
				}

				return res;
			}
			
			/**
			 * @brief Когда перегруженно в дочерних классах определяет возможность исполнения действия
			 * 
			 * @param ctx Контекст действий
			 * @return true если применимо к текущему контексту
			 */
			virtual bool isApplyable(Context ctx) = 0;
		};
	}
}