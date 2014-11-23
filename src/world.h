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
			Inventory* _inventory;

		public:
			Location(int x, int y, World* w)
				: _x(x)
				, _y(y)
				, _characters()
				, _world(w)
			{
				_inventory = new Inventory();
			};

			~Location(){
				delete _inventory;
			}

			
			inline Inventory* inventory(){
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

			void generateCharacters(unsigned chars);

		public:
			World() 
				: _locations()
				, _characters()
			{};
			void generateWorld(unsigned maxX, unsigned maxY, unsigned chars);

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