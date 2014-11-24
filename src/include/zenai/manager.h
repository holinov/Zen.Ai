#pragma once
#include "stdafx.h"
#include "log.h"

namespace Zen
{
    namespace AI
    {
        template<class ItemType>
        struct ManagerLoader {
            //std::vector<ItemType*> load();//{ return std::vector<ItemType*>();}
        };

        template<class KeyType, class ItemType>
        class Manager
        {
        private:
            std::map<KeyType, ItemType *> _cache;
            std::map<KeyType, unsigned long> _counts;
            unsigned int _maxCount;
        protected:
            void cleanup()
            {
                if(_cache.size() > _maxCount)
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
            Manager(int max)
                : _cache()
                , _counts()
                , _maxCount(max)
        	{};

        	Manager() : Manager(10) {};

            inline bool contains(KeyType key) const
            {
                auto it = _cache.find(key);
                return it != _cache.end();
            }

            ItemType *get(KeyType key)
            {
                if (contains(key))
                {          
                    return _cache[key];
                }
                Log::MTLog::Instance().Debug() << "Have no data for key: " << key << ". Have :" << _cache.size();
                return nullptr;
            }

            void set(KeyType key, ItemType * val)
            {
                _cache[key] = val;
                if(!contains(key))
                	_counts[key] = 1;

                for (auto && _cnt : _counts)
                {
                    --_cnt.second;
                }
                _counts[key] += 2;
                cleanup();
            }

            std::vector<KeyType> getAllIds(){
            	std::vector<KeyType> res;
                for(auto&& cnt : _counts) {
                    res.push_back(cnt.first);
            	}
            	return res;
            }

            virtual ~Manager()
            {
                for (auto && i : _cache)
                {
                    delete i.second;
                }
            }

            std::vector<ItemType*> getAll(){
                std::vector<ItemType*> res;
                for(auto&& it : _cache) {
                    res.push_back(it.second);
                }
                return res;
            }
        
            virtual void LoadActions()
            {
            	for(auto&& i : loadItems()) {
            		set(i->id(),i);
            	}
            }
protected:
            std::vector<ItemType*> loadItems(){
            	ManagerLoader<ItemType> loader;
                return loader.load();
            }
        };
    }
}