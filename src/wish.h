#pragma once
#include "stdafx.h"
#include "skill.h"

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
				, _histroy()
			{};

			Wish()
				: Wish(0,"")
			{};

			Wish(Wish& o)
				: _histroy(o._histroy)
			{	
				id(o.id());
				name(o.name());
			};
		};

		/**
		 * @brief Информация о желании существа
		 */
		struct WishInfo {
		private:
			IdType _wishId;
			int _wishLevel;
		public:
			WishInfo(IdType wishId, int wishLevel) 
				:_wishId(wishId)
				,_wishLevel(wishLevel)
			{};
			WishInfo(): WishInfo(0,0) {}

			inline const IdType wishId(){ return _wishId; }
			inline void wishId(IdType id) { _wishId=id; }

			inline const int wishLvl() { return _wishLevel; }
			inline void wishLvl(int lvl){ _wishLevel = lvl; }
			inline void addWishLvl(int lvl){ 
				int lnvl = _wishLevel += lvl; 
				if(lnvl < 0) lnvl=0;
				wishLvl(lnvl);
			}
		};
	}
}