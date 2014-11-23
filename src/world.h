#pragma once
#include "stdafx.h"
#include "character.h"
#include "managers.h"

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
			World* _world;
			Inventroy* _inventory;

		public:
			Location(int x, int y, World* w)
				: _x(x)
				, _y(y)
				, _characters()
				, _world(w)
			{
				_inventory = new Inventroy();
			};

			~Location(){
				delete _inventory;
			}

			
			inline Inventroy* inventory(){
				return _inventory;
			}

			inline World* world(){
				return _world;
			}
		};

		class World {
		private:
			std::vector<std::vector<Location*>> _locations;
			std::vector<Character*> _characters;

			void generateCharacters(unsigned chars){
				WishManager mgr;
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
				//std::vector<std::vector<Location*>> locs(maxX);
				//Сгенерировать локации
				for(unsigned x = 0; x < maxX; ++x) {
					std::vector<Location*> row(maxY);
					for(unsigned y = 0; y < maxY; ++y) {
						Location* l= new Location(x,y,this);
						row.push_back(l);

						//Сгенерировать стартовые ресурсы локации
						#warning TODO: generate resources
						//l->generateResources();
					}
					_locations.push_back(row);
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

				for(auto&& ch : _characters) {
					delete ch;
				}
			}
		};
	}
}