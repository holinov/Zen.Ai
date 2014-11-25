#pragma once
#include "stdafx.h"
//#include "character.h"
//#include "world.h"

namespace Zen{
	namespace AI{

		class Character;
		class Location;
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