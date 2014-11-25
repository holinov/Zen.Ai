#pragma once
#include "stdafx.h"
#include "wish.h"

namespace Zen{
	namespace AI{
		/**
		 * @brief Склонность существа
		 */
		class Addiction : public HasId, public HasName{
		private:
			IdType _wishId;
		public:
			Addiction(IdType id, std::string name, IdType wishId) 
				: HasId(id)
				, HasName(name)
			{};

			inline IdType wishId() { return id(); }
		};

		/**
		 * @brief Информация о склонности существа
		 */
		class AddictionInfo {
		private:
			IdType _wishId;
			int _wishLevel;
		public:
			AddictionInfo(IdType wishId, int wishLevel) 
				:_wishId(wishId)
				,_wishLevel(wishLevel)
			{};

			AddictionInfo(Wish* w, int wishLevel)
				:AddictionInfo(w->id(),wishLevel)
			{}

			AddictionInfo():AddictionInfo((IdType)0,0) {} 

			/**
			 * @brief ИД желания склонности
			 */
			inline const IdType wishId(){ return _wishId; }
			
			/**
			 * @brief ИД желания склонности
			 */
			inline void wishId(const IdType id) { _wishId=id; }

			/**
			 * @brief Силя влияния на желание
			 */
			inline const int wishLvl() { return _wishLevel; }
			
			/**
			 * @brief Силя влияния на желание
			 */
			inline void wishLvl(const int lvl){ _wishLevel = lvl; }			
		};
	}
}