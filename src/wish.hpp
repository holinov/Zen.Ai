#pragma once
#include "stdafx.h"

namespace Zen{
	namespace AI{
		class SkillResult ;

		/**
		 * @brief Желание существа
		 */
		class Wish : public HasId, public HasName{
		private:
			std::vector<SkillResult> _histroy;
		public:
			Wish(IdType id, std::string name) 
				: HasId(id)
				, HasName(name)
			{};
		};

		/**
		 * @brief Информация о желании существа
		 */
		class WishInfo {
		private:
			IdType _wishId;
			int _wishLevel;
		public:
			WishInfo(IdType wishId, int wishLevel) 
				:_wishId(wishId)
				,_wishLevel(wishLevel)
			{};

			inline const IdType wishId(){ return _wishId; }
			inline void wishId(IdType id) { _wishId=id; }

			inline const int wishLvl() { return _wishId; }
			inline void wishLvl(int lvl){ _wishLevel = lvl; }
			inline void addWishLvl(int lvl){ _wishLevel += lvl; }
		};
	}
}