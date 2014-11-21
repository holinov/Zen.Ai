#pragma once
#include "stdafx.h"
#include "manager.hpp"

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
				, count(count)
			{};

			InventoryItem(const InventoryItem& o) 
				: InventoryItem(o._typeId,o._count)
			{}

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
			unsigned long value() const{
				return _resouceValue;
			}
		};

		/**
		 * @brief Инвентрарь (класс для работы с коллекциями предметов)
		 */
		class Inventroy {
		private:
			std::map<ItemType, InventoryItem> _items;
		public:
			Inventroy()
				: _items
			{};

			/**
			 * @brief Наличие предмета заданного типа
			 * 
			 * @param id ИД типа
			 * @return true если есть
			 */
			bool hasItemTypeId(IdType id) const{
				auto it = _items.find(id);
				return it != _items.end();
			}

			uint resAmmount(IdType id) const{
				if(hasItemTypeId(id)){
					return _items[id].count();
				}else{
					return 0;
				}
			}

			/**
			 * @brief Наличие предмета заданного типа в нужном количестве
			 * 
			 * @param id ИД типа
			 * @param count Необходимое количество
			 * @return true если есть
			 */
			bool hasItemTypeId(IdType id, uint count) const{
				auto it = _items.find(id);
				return it != _items.end() && _items[id].count() >= count;
			}

			/**
			 * @brief Добавить предметы в инвентарь
			 * 
			 * @param item Тип предмета
			 * @param int колическтво предметов
			 */
			inline void add(Item* item,unsigned int count){
				add(item->id(), count);
			}

			/**
			 * @brief Добавить предметы в инвентарь
			 * 
			 * @param itemType ИД типа предмета
			 * @param int количество предметов
			 */
			inline void add(IdType itemType, unsigned int count){
				add(InventoryItem(itemType,count));
			}

			/**
			 * @brief Добавить предметы в инвентарь
			 * 
			 * @param item Предметы
			 */
			void add(InventoryItem& item){
				IdType id=item.type();
				if(hasItemTypeId(id)){
					_items[id].count(_items[id].count() + item.count());
				}else{
					_items[id] = item;
				}
			}

			/**
			 * @brief Забрать предметы из инвентаря
			 * @details Просто вычитает кол-во предметов
			 * 
			 * @param item Предмет
			 */
			void take(InventoryItem& item){
				IdType id=item.type();
				if(hasItemTypeId(id)){
					_items[id].count(_items[id].count() - item.count());
				}
			}

			/**
			 * @brief Переместить предметы из этого инвентаря в другой
			 * @details Убирает предметы из этого и добавляет их в другой инвентарь
			 * 
			 * @param target В какой инвентарь переложить
			 * @param item Предметы
			 */
			void moveToInventory(Inventroy* target,InventoryItem& item){
				if(hasItemTypeId(item.id() && _items[item.id()] >= item.count()){
					take(item);
					target->add(item);
				}
			}

			/**
			 * @brief Есть ресурсы заданного типа
			 * 
			 * @param type Тип ресурса
			 * @return true если есть хотя-бы один ресурс заданного типа
			 */
			bool hasResourceOfType(std::string type) const{
				ItemManager itemManager;
				bool has = false;
				for(auto&& invItem : _items) {
					Item* item = itemManager.get(invItem.type());
					Resource* res = dynamic_cast<Resource*>(item);
					if(res != nullptr && res.type() == type){
						has = true;
						break;
					}
				}

				return res;
			}

			/**
			 * @brief Получить ресурсы нужного типа
			 * 
			 * @param type Тип ресурса
			 * @return Список ресурсов заданного типа
			 */	
			std::vector<InventoryItem> getResourcesOfType(std::string type){
				return getResourcesOfType(type,1);
			}

			/** 
			 * @brief Получить ресурсы нужного типа в нужном количестве
			 * 
			 * @param type Тип ресурса
			 * @param count количество ресурса
			 * @return Список ресурсов заданного типа
			 */	
			std::vector<InventoryItem> getResourcesOfType(std::string type, unsigned int count){
				ItemManager itemManager;
				std::vector<InventoryItem> resources;
				for(auto&& invItem : _items) {
					Item* item = itemManager.get(invItem->type());
					Resource* res = dynamic_cast<Resource*>(item);
					if(res != nullptr && res.type() == type && res.count() => count){
						resources.push_back(*item);
					}
				}

				return resources;
			}
		};

		class Food : Resource {
		public:
			Food()
				:Resource(0,"Raw food (berries)",ResourceTypes::FOOD,1)
			{}

			virtual ~Food(){}
		};
	}
}