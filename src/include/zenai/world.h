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

			/**
			 * @brief Предметы и ресурсы локации
			 */
			inline Inventory* inventory(){
				return _inventory;
			}

			/**
			 * @brief Ссылка на мир к которому принадлежит локация
			 */
			inline World* world(){
				return _world;
			}

			/**
			 * @brief X координата локации
			 */
			inline int x(){return _x;}

			/**
			 * @brief Y координата локации
			 */
			inline int y(){return _y;}
		};

		/**
		 * @brief Игровой мир
		 */
		class World {
		private:
			std::vector<Location*> _locations;
			std::vector<Character*> _characters;
			void generateCharacters(unsigned chars);

		public:
			World() 
				: _locations()
				, _characters()
			{};

			/**
			 * @brief Сгенерировать мир
			 * 
			 * @param maxX максимальная координата X
			 * @param maxY максимальная координаты Y
			 * @param chars стартовое кол-во персонажей
			 */
			void generateWorld(unsigned maxX, unsigned maxY, unsigned chars);

			/**
			 * @brief Обсчитать слудующий тик мира
			 */
			void makeWorldStep();

			/**
			 * @brief Список локаций мира
			 */
			inline std::vector<Location*> locations() {return _locations;}

			/**
			 * @brief Список персонажей мира
			 */
			inline std::vector<Character*> characters() {return _characters;};

			~World(){
				for(auto&& loc : _locations) {
					//for(auto&& loc : row) {
						delete loc;
					//}
				}

				for(auto&& ch : _characters) {
					delete ch;
				}
			}
		};
	}
}