#pragma once
#include "stdafx.h"

namespace Zen{
	namespace AI{
		/**
		 * @brief Склонность существа
		 */
		class Addiction : public HasId, public HasName{
		private:

		public:
			Addiction(IdType id, std::string name) 
				: HasId(id)
				, HasName(name)
			{};
		};

		/**
		 * @brief Информация о склонности существа
		 */
		class AddictionInfo {
		/*private:
			IdType _wishId;
			int _wishLevel;
		public:
			AddictionInfo(IdType wishId, int wishLevel) 
				:_wishId(wishId)
				,_wishLevel(wishLevel)
			{};

			inline const IdType wishId(){ return _wishId; }
			inline void wishId(IdType id) { _wishId=id; }

			inline const int wishLvl() { return _wishId; }
			inline void wishLvl(int lvl){ _wishLevel = lvl; }
			inline void addWishLvl(int lvl){ _wishLevel += lvl; }*/
		};
	}
}