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

			inline IdType type() const{
				return _typeId;
			}

			inline unsigned int count() const{
				return _count;
			}

			inline void count(unsigned int cnt){
				_count=cnt;
			}
		};

		

		struct ResourceTypes {
			static const std::string FOOD;
			static const std::string MINERAL;
			static const std::string WOOD;
		};
		
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
			inline unsigned long value() const{
				return _resouceValue;
			}

			inline std::string type() const{
				return _type;
			}
		};

		class Food : public Resource {
		public:
			Food()
				:Resource(0,"Raw food (berries)",ResourceTypes::FOOD,1)
			{}

			virtual ~Food(){}
		};
	}
}