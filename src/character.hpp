#pragma once
#include "stdafx.h"
#include "item.hpp"

namespace Zen{
	namespace AI{
		class WishInfo;
		class AddictionInfo;
		class Skill;

		/**
		 * @brief Существо
		 */
		class Character : public HasId{
		public:
			/**
			 * @brief Характеристики существа
			 */
			struct Stats {
				/**
				 * @brief Общие характеристики
				 */
				struct Common{

					/**
					 * @brief Общий уровень опыта
					 */
					int TotalExp;

					/**
					 * @brief Уровень счастья
					 */
					int Happines;

					/**
					 * @brief Богатство
					 */
					int Wealth;

					Common():TotalExp(0),Happines(0),Wealth(0) {}
				};

				/**
				 * @brief Характеристики выживания
				 */
				struct Survival {
					/**
					 * @brief Энергия (расходуется на выполнение действий)
					 * @details При достижении 0 существо засыпает (выбирается умение восстанавливающее наибольшее кол-во энергии)
					 */
					int Energy;

					/**
					 * @brief Голод (при достижении 0 существо умирает)
					 */
					int Food;

					/**
					 * @brief Жажда (при достижении 0 существо умирает)
					 */
					int Water;

					Survival():Energy(0),Food(0),Water(0) {}
				};

				/**
				 * @brief Социальные характеристики
				 */
				struct Social{
					
					/**
					 * @brief Влиятельность]
					 */
					int Influence;

					/**
					 * @brief Привлекательность
					 * @details Используется для выбора партнера для размножения
					 */
					int Attractivnes;

					Social():Influence(0),Attractivnes(0) {}
				};

				/**
				 * @brief Общие характеристики
				 */
				Common Common;

				/**
				 * @brief Характеристики выживания
				 */
				Survival Survival;

				/**
				 * @brief Социальные характеристики
				 */
				Social Social;

				Stats(): Common(),Survival(),Social() {}
			};
			static IdType curId;

		private:
			std::vector<WishInfo> _wishes;
			std::vector<AddictionInfo> _addictions;
			std::map<IdType,Skill> _skills;
			std::map<IdType,Item> _items;

		public:

			void makeAction();

			/**
			 * @brief Получить кол-во заданного ресурса в интвентаре
			 * 
			 * @param resourceId ИД типа ресурса
			 * @return Кол-во доступных ресурсов
			 */
			int getResourceCount(IdType resourceId);

			/**
			 * @brief Характеристики персонажа
			 */
			Stats Stats;

			Character(): Stats() {
				id(++curId);
			};

			/**
			 * @brief Изменить уровень желания
			 * 
			 * @param wishId ИД изменяемого желания
			 * @param modifyLvl Уровень изменения желания
			 */
			inline void modifyWish(IdType wishId, int modifyLvl){
				_wishes[wishId].addWishLvl(wishId,modifyLvl);
			}
		};
	}
}