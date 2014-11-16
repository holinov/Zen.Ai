#pragma once
#include "stdafx.h"
#include "character.hpp"
#include "item.hpp"
#include "world.hpp"

namespace Zen{
	namespace AI{

		/**
		 * @brief Данные о главном действущем лице
		 */
		class ActorInfo {
		private:
			std::vector<Character*> _characters;
			Character* _actor;
		public:
			ActorInfo(Character* ch): _actor(ch) {};

			/**
			 * @brief Ссылка на существо
			 */
			Character* actor(){ return _actor; }

			/**
			 * @brief Достаточно ли ресурсов
			 * 
			 * @param resourceId ИД ресурса
			 * @param count необходимое кол-во ресурса
			 * 
			 * @return true если достаточно
			 */
			inline const bool isEnougthResources(IdType resourceId, int count){
				return _actor->getResourceCount(resourceId) >= count;
			}

			/**
			 * @brief Изменить уровень желания
			 * 
			 * @param wishId ИД желания
			 * @param modifyLvl ировень изменения
			 */
			inline void modifyWish(IdType wishId, int modifyLvl){
				_actor->modifyWish(wishId, modifyLvl);
			}

		};

		/**
		 * @brief Контекст ситуации
		 * @details Сожержит текущий контекст принятия решения. Включая информацию о главном действющем лице,
		 * месте действия и других существах в месте действия
		 */
		class Context {
		private:
			Location* _location;
			ActorInfo _actorInfo;
		public:
			Context(Character* actor, Location* loc)
				:_location(loc)
				,_actorInfo(actor)
			{};

			/**
			 * @brief Информация о главном действющем лице
			 */
			inline ActorInfo& actorInfo(){
				return _actorInfo;
			}

			/**
			 * @brief Место действия
			 */
			inline Location* const location() const{
				return _location;
			}
		};
	}
}