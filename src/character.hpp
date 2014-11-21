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
					static const std::string TotalExp = "Common.TotalExp";

					/**
					 * @brief Уровень счастья
					 */
					static const std::string Happines = "Common.Happines";

					/**
					 * @brief Богатство
					 */
					static const std::string Wealth = "Common.Wealth";
				};

				/**
				 * @brief Характеристики выживания
				 */
				struct Survival {
					/**
					 * @brief Энергия (расходуется на выполнение действий)
					 * @details При достижении 0 существо засыпает (выбирается умение восстанавливающее наибольшее кол-во энергии)
					 */
					static const std::string Energy ="Survival.Energy";

					/**
					 * @brief Голод (при достижении 0 существо умирает)
					 */
					static const std::string Food = "Survival.Food";

					/**
					 * @brief Жажда (при достижении 0 существо умирает)
					 */
					static const std::string Water = "Survival.Water";
				};

				/**
				 * @brief Социальные характеристики
				 */
				struct Social{
					
					/**
					 * @brief Влиятельность]
					 */
					static const std::string Influence = "Social.Influence";

					/**
					 * @brief Привлекательность
					 * @details Используется для выбора партнера для размножения
					 */
					static const std::string Attractivnes = "Social.Attractivnes";
				};
			};
			static IdType curId;

		private:
			std::vector<WishInfo> _wishes;
			std::vector<AddictionInfo> _addictions;
			std::map<IdType,Skill> _skills;
			std::map<std::string,int> _stats;
			Inventroy _inventroy;

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

			Character()
				: Stats() 
				, _wishes()
				, _addictions()
				, _skills()
				, _stats({ 	{Stats::Common::Attractivnes, 100} 
							,{Stats::Common::Influence, 100}
							,{Stats::Survival::Energy, 100}
							,{Stats::Survival::Food, 100}
							,{Stats::Survival::Water, 100}
							,{Stats::Common::TotalExp, 0}
							,{Stats::Common::Happines, 100}
							,{Stats::Common::Wealth, 0}
							});
				, _inventroy()
			{
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

			Inventroy& inventory() const{
				return &inventory;
			}
		};
	}
}