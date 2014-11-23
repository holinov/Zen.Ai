#pragma once
#include "stdafx.h"
#include "inventory.h"
#include "skill.h"
#include "addiction.h"

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
					static const std::string TotalExp;

					/**
					 * @brief Уровень счастья
					 */
					static const std::string Happines;

					/**
					 * @brief Богатство
					 */
					static const std::string Wealth;
				};

				/**
				 * @brief Характеристики выживания
				 */
				struct Survival {
					/**
					 * @brief Энергия (расходуется на выполнение действий)
					 * @details При достижении 0 существо засыпает (выбирается умение восстанавливающее наибольшее кол-во энергии)
					 */
					static const std::string Energy;

					/**
					 * @brief Голод (при достижении 0 существо умирает)
					 */
					static const std::string Food;

					/**
					 * @brief Жажда (при достижении 0 существо умирает)
					 */
					static const std::string Water;
				};

				/**
				 * @brief Социальные характеристики
				 */
				struct Social{
					
					/**
					 * @brief Влиятельность]
					 */
					static const std::string Influence;

					/**
					 * @brief Привлекательность
					 * @details Используется для выбора партнера для размножения
					 */
					static const std::string Attractivnes;
				};
			};
			static IdType curId;

		private:
			std::vector<WishInfo> _wishes;
			std::vector<AddictionInfo> _addictions;
			std::map<IdType,Skill> _skills;
			std::map<std::string,int> _stats;
			Inventroy* _inventroy;

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
				, _stats({ 	{Stats::Social::Attractivnes, 100} 
							,{Stats::Social::Influence, 100}
							,{Stats::Survival::Energy, 100}
							,{Stats::Survival::Food, 100}
							,{Stats::Survival::Water, 100}
							,{Stats::Common::TotalExp, 0}
							,{Stats::Common::Happines, 100}
							,{Stats::Common::Wealth, 0}
							})				
			{
				id(++curId);
				_inventroy=new Inventroy();
			};

			~Character(){
				delete _inventroy;
			}

			/**
			 * @brief Изменить уровень желания
			 * 
			 * @param wishId ИД изменяемого желания
			 * @param modifyLvl Уровень изменения желания
			 */
			inline void modifyWish(IdType wishId, int modifyLvl){
				_wishes[wishId].addWishLvl(modifyLvl);
			}

			inline Inventroy* inventory(){
				return _inventroy;
			}

			int stat(std::string stat){
				return _stats[stat];
			}

			void stat(std::string stat, uint val){
				_stats[stat] = val;
			}
		};
	}
}