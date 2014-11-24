#pragma once
#include "stdafx.h"
#include "manager.h"

namespace Zen{
	namespace AI{

		/**
		 * @brief Предмет
		 */
		class Item : public HasId, public HasName{
		protected:
			Item(IdType id, std::string name) 
				: HasId(id)
				, HasName(name)
			{};
		public:
			virtual ~Item(){}
		};

		/**
		 * @brief Предмет в инвентаре
		 */
		class InventoryItem {
		private:
			IdType _typeId;
			unsigned int _count;
		public:
			InventoryItem(IdType type, unsigned int count)
				: _typeId(type)
				, _count(count)
			{};

			InventoryItem(const InventoryItem& o) 
				: InventoryItem(o.type(),o.count())
			{}

			InventoryItem() : _typeId(), _count() {}

			/**
			 * @brief ИД типа предмета
			 */
			inline IdType type() const{
				return _typeId;
			}

			/**
			 * @brief Кол-во предметов
			 */
			inline unsigned int count() const{
				return _count;
			}

			/**
			 * @brief Кол-во предметов
			 */
			inline void count(unsigned int cnt){
				_count=cnt;
			}
		};

		
		/**
		 * @brief Типы ресурсов 
		 */
		struct ResourceTypes {

			/**
			 * Еда
			 */
			static const std::string FOOD;

			/**
			 * Минералы
			 */
			static const std::string MINERAL;

			/**
			 * Древесина
			 */
			static const std::string WOOD;
		};
		
		/**
		 * @brief Предмет ресурс
		 */
		class Resource : public Item {
		private:
			std::string _type;
			unsigned int _resouceValue;
		protected:
			Resource(IdType id, std::string name,std::string type,unsigned int resouceValue)
				: Item(id,name)
				, _type(type)
				, _resouceValue(resouceValue)
			{}
		public:
			virtual ~Resource(){}

			/**
			 * @brief Значение ресурса
			 */
			inline unsigned long value() const{
				return _resouceValue;
			}

			/**
			 * @brief Тип ресурса
			 */
			inline std::string type() const{
				return _type;
			}
		};

		class Food : public Resource {
		public:
			Food()
				:Resource(13,"Raw food (berries)",ResourceTypes::FOOD,1)
			{}

			virtual ~Food(){}
		};
	}
}