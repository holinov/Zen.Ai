#pragma once
#include "stdafx.h"
#include "item.h"

namespace Zen
{
    namespace AI
    {
        /**
         * @brief Инвентрарь (класс для работы с коллекциями предметов)
         */
        class Inventory
        {
        private:
            std::map<IdType, InventoryItem> _items;
        public:
            Inventory()
                : _items()
            {}

            /**
             * @brief Наличие предмета заданного типа
             *
             * @param id ИД типа
             * @return true если есть
             */
            bool hasItemTypeId (IdType id)
            {
                auto it = this->_items.find(id);
                bool res = it != this->_items.end();
                return res;
            }

            uint resAmmount(IdType id)
            {
                if (hasItemTypeId(id))
                {
                    return _items[id].count();
                }
                else
                {
                    return 0;
                }
            }

            uint count()
            {
                uint c = 0;
                for (auto && i : _items)
                {
                    c += i.second.count();
                }
                return c;
            }

            /**
             * @brief Наличие предмета заданного типа в нужном количестве
             *
             * @param id ИД типа
             * @param count Необходимое количество
             * @return true если есть
             */
            bool hasItemTypeId(IdType id, uint count)
            {
                auto it = _items.find(id);
                return it != _items.end() && _items[id].count() >= count;
            }

            /**
             * @brief Добавить предметы в инвентарь
             *
             * @param item Тип предмета
             * @param int колическтво предметов
             */
            inline void add(Item *item, unsigned int count)
            {
                add(item->id(), count);
            }

            /**
             * @brief Добавить предметы в инвентарь
             *
             * @param itemType ИД типа предмета
             * @param int количество предметов
             */
            inline void add(IdType itemType, unsigned int count)
            {
                auto item = InventoryItem(itemType, count);
                add(item);
            }

            /**
             * @brief Добавить предметы в инвентарь
             *
             * @param item Предметы
             */
            void add(InventoryItem &item)
            {
                IdType id = item.type();
                if (hasItemTypeId(id))
                {
                    _items[id].count(_items[id].count() + item.count());
                }
                else
                {
                    _items[id] = item;
                }
            }

            /**
             * @brief Забрать предметы из инвентаря
             * @details Просто вычитает кол-во предметов
             *
             * @param item Предмет
             */
            void take(InventoryItem &item)
            {
                IdType id = item.type();
                if (hasItemTypeId(id))
                {
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
            void moveToInventory(Inventory *target, InventoryItem &item)
            {
                if (
                    hasItemTypeId(item.type())
                    && _items[item.type()].count() >= item.count()
                )
                {
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
            bool hasResourceOfType(std::string type) const
            {
                Manager<IdType, Item> itemManager;
                bool has = false;
                for (auto && invItem : _items)
                {
                    Item *item = itemManager.get(invItem.second.type());
                    Resource *res = dynamic_cast<Resource *>(item);
                    if (res != nullptr && res->type() == type)
                    {
                        has = true;
                        break;
                    }
                }

                return has;
            }

            /**
             * @brief Получить ресурсы нужного типа
             *
             * @param type Тип ресурса
             * @return Список ресурсов заданного типа
             */
            std::vector<InventoryItem> getResourcesOfType(std::string type)
            {
                return getResourcesOfType(type, 1);
            }

            /**
             * @brief Получить ресурсы нужного типа в нужном количестве
             *
             * @param type Тип ресурса
             * @param count количество ресурса
             * @return Список ресурсов заданного типа
             */
            std::vector<InventoryItem> getResourcesOfType(std::string type, unsigned int count)
            {
                Manager<IdType, Item> itemManager;
                std::vector<InventoryItem> resources;
                for (auto && invItem : _items)
                {
                    Item *item = itemManager.get(invItem.second.type());
                    Resource *res = dynamic_cast<Resource *>(item);
                    if (res != nullptr && res->type() == type && invItem.second.count() >= count)
                    {
                        resources.push_back(invItem.second);
                    }
                }

                return resources;
            }

            inline uint getResourceCount(IdType type)
            {
                return resAmmount(type);
            }
        };
    }
}