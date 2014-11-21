#pragma once
#include "stdafx.h"
#include "context.hpp"
#include "action.hpp"

namespace Zen{
	namespace AI{
		template<class KeyType, class ItemType>
		class Manager {
		private:
			std::map<KeyType,ItemType*> _cache;
			std::map<KeyType,unsigned long> _counts;
			unsigned int _maxCount;
		protected:
			void cleanup(){
				if(_cache.size() > _maxCount){
					bool firstRun = true;
					unsigned long minCnt;
					KeyType idx;

					for(auto&& cnt : _counts) {
						if(firstRun || minCnt > cnt->second{
							idx = cnt->first;
							minCnt = cnt->second;
							firstRun = false;
						}
					}

					//Удалить из записей подсчета
					for (auto it = _counts.begin(); it != _counts.end(); ) {
				        if (it->first == idx)
				            // new erase() that returns iter..
				            it = _counts.erase(it);
				        else
				            ++it;
				    }

				    //Удалить из запимиь кеша
				    for (auto it = _cache.begin(); it != _cache.end(); ) {
				        if (it->first == idx)
				            // new erase() that returns iter..
				            it = _cache.erase(it);
				        else
				            ++it;
				    }


				}
			}
		public:
			Manager(int max)
				: _cache() 
				, _counts();
			{
				_maxCount=max;
			};
			
			inline bool contains(KeyType key) const{
				auto it = _cache.find(key);
				return it != _cache.end();
			}

			ItemType* get(KeyType key) const{
				if(contains(key))
					return _cache[key];
				return nullptr;
			}

			void set(ItemType key, ItemType* val){
				_cache[key] = val;
				cleanup();
			}

			virtual ~Manager(){
				for(auto&& i : _cache) {
					delete i->second;
				}
			}

		protected:
			virtual void LoadActions(){

			}
		};

		class WishManager: public Manager<IdType,Wish> {
		private:
			/* data */
		public:
			WishManager(/* args */) = default;
			virtual ~WishManager() {}
			protected:
			virtual void LoadActions(){
				IdType i = 0;
				
				Wish* w1=new Wish(i,"To eat");
				set(i,w1);
				
				Wish* w2=new Wish(++i,"To sleep");
				set(i,w2);
			}
		};

		class ActionManager: public Manager<IdType,Action> {
		private:
			/* data */
		public:
			ActionManager(/* args */) = default;
			virtual ~ActionManager()
			{};
		protected:
			virtual void LoadActions(){
				IdType i=0;

				Action* a1 = new Action(i,"Eat raw",{0,10});
				set(i,a1);

				Action* a2 = new Action(++i,"Sit",{1,15});
				set(i,a2);
			}
		};
}
}