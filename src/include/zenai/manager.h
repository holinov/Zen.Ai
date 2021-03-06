#pragma once
#include "stdafx.h"
#include "log.h"

namespace Zen
{
    namespace AI
    {
        /**
         * @brief ЗАгрузчик менеджера
         * @details Описывает первичную загрузку менеджера
         *
         * @tparam ItemType Тип элемента
         */
        template<class ItemType>
        struct ManagerLoader
        {
            /**
             * @brief Читает данные менеджера с диска
             *
             * @return Вектор прочитанных данных
             */
            std::vector<ItemType *> load()
            {
                return std::vector<ItemType *>();
            }
        };

        /**
         * @brief Базовая реализация менеджера ресурсов мира
         *
         * @tparam KeyType Тип ключа
         * @tparam ItemType Тип элемента
         */
        template<class KeyType, class ItemType>
        class ManagerImpl
        {
        private:
            std::map<KeyType, ItemType *> _cache;
            std::map<KeyType, unsigned long> _counts;
            unsigned int _maxCount;
            bool _firstTime = true;
        protected:
            /**
             * @brief Читистить оставив только заданное кол-во эелементов в памяти
             */
            void cleanup()
            {
                if (_cache.size() > _maxCount)
                {
                    bool firstRun = true;
                    unsigned long minCnt;
                    KeyType idx;

                    for (auto && cnt : _counts)
                    {
                        if (firstRun || minCnt > cnt.second)
                        {
                            idx = cnt.first;
                            minCnt = cnt.second;
                            firstRun = false;
                        }
                    }

                    //Удалить из записей подсчета
                    for (auto it = _counts.begin(); it != _counts.end(); )
                    {
                        if (it->first == idx)
                            it = _counts.erase(it);
                        else
                            ++it;
                    }

                    //Удалить из записей кеша
                    for (auto it = _cache.begin(); it != _cache.end(); )
                    {
                        if (it->first == idx)
                            it = _cache.erase(it);
                        else
                            ++it;
                    }


                }
            }
        public:

            /**
             * @brief Содержит ли элемент м заданным ключом
             *
             * @param key Ключ элемента
             */
            inline bool contains(KeyType key) const
            {
                auto it = _cache.find(key);
                return it != _cache.end();
            }

            /**
             * @brief Получить элемент с заданным ключом
             *
             * @param key Ключ элемента
             */
            ItemType *get(KeyType key)
            {
                if (contains(key))
                {
                    return _cache[key];
                }
                Log::MTLog::Instance().Debug() << "Have no data for key: " << key << ". Have :" << _cache.size();
                return nullptr;
            }

            /**
             * @brief Установить элемент в заданный ключ
             *
             * @param key Ключ
             * @param val Элемент
             */
            void set(KeyType key, ItemType *val)
            {
                _cache[key] = val;
                if (!contains(key))
                    _counts[key] = 1;

                for (auto && _cnt : _counts)
                {
                    --_cnt.second;
                }
                _counts[key] += 2;
                cleanup();
            }

            /**
             * @brief Получить все ИД элементов
             */
            std::vector<KeyType> getAllIds()
            {
                std::vector<KeyType> res;
                for (auto && cnt : _counts)
                {
                    res.push_back(cnt.first);
                }
                return res;
            }

            /**
             * @brief Получить все эелементы
             */
            std::vector<ItemType *> getAll()
            {
                std::vector<ItemType *> res;
                for (auto && it : _cache)
                {
                    res.push_back(it.second);
                }
                return res;
            }

            uint count() const{
                return _cache.size();
            }

            virtual ~ManagerImpl()
            {
                for (auto && i : _cache)
                {
                    delete i.second;
                }
            }
        protected:
            std::vector<ItemType *> loadItems()
            {
                ManagerLoader<ItemType> loader;
                return loader.load();
            }

            ManagerImpl(int max)
                : _cache()
                , _counts()
                , _maxCount(max)
            {
                load();
            };

            ManagerImpl() : ManagerImpl(10) {};
        private:
            void load()
            {
                if (_firstTime)
                {
                    for (auto && i : loadItems())
                    {
                        set(i->id(), i);
                    }
                    _firstTime = false;
                }
            }
        };

        /**
         * @brief Сокращение шаблона для ManagerImpl (как ключ использует IdType)
         * 
         * @tparam ItemType Тип элемента
         */
        template<class ItemType>
        class Manager : public ManagerImpl<IdType, ItemType>
        {
        protected:
            Manager(int max) : ManagerImpl<IdType, ItemType>(10) {};
            Manager() : Manager(100) {};

        public:
            static Manager<ItemType> *instance()
            {
                static Manager<ItemType> *inst = new Manager<ItemType>();
                return inst;
            }
        };
    }
}