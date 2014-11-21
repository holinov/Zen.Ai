#pragma once
#include "stdafx.h"
#include "character.hpp"
#include "item.hpp"

namespace Zen{
	namespace AI{
		class World;

		/**
		 * @brief Локация мира
		 * @details Содержит информацию о ресурсах и существах в данной локации
		 * 
		 */
		class Location {
		private:
			int _x;
			int _y;
			std::vector<Character*> _characters;
			std::vector<InventoryItem> _resources;
			World* _world;
			Inventroy _inventory;

		public:
			Location(int x, int y, World* w)
				: _x(x)
				, _y(y)
				, _characters()
				, _resources()
				, _world(w)
				, _inventory()
			{};

			
			Inventroy& inventory() const{
				return &_inventory;
			}
		};

		class World {
		private:
			std::vector<std::vector<Location*>> _locations;
			std::vector<Character*> _characters;

			void generateCharacters(unsigned chars){
				for(unsigned i = 0; i < chars; ++i) {
					/* code */
				}
			}

		public:
			World() 
				: _locations()
				, _characters()
			{};
			void generateWorld(unsigned maxX, unsigned maxY, unsigned chars){
				std::vector<std::vector<Location*>> locs(maxY);
				//Сгенерировать локации
				for(unsigned x = 0; x < maxX; ++x) {
					std::vector<Location*> row(maxY);
					for(unsigned y = 0; y < maxY; ++y) {
						Location* l= new Location(x,y,this);

						//Сгенерировать стартовые ресурсы локации
						#warning TODO: generate resources
						//l->generateResources();
					}
				}

				//Сгенерировать персонажей
				#warning TODO: generate characters
			}

			~World(){
				for(auto&& row : _locations) {
					for(auto&& loc : row) {
						delete loc;
					}
				}
			}
		};
	}
}