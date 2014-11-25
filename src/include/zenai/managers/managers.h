#pragma once
#include "../stdafx.h"
#include "../manager.h"
#include "../addiction.h"
#include "../wish.h"
#include "../item.h"

namespace Zen
{
    namespace AI
    {
        template<>
        struct ManagerLoader<Item>
        {
            std::vector<Item *> load()
            {
                return std::vector<Item *>
                {
                    new Food(),
                };
            }
        };

        class ItemManager: public Manager<IdType, Item>
        {
        private:

        public:
            ItemManager() = default;
            virtual ~ItemManager() {};
        };

        template<>
        struct ManagerLoader<Wish>
        {
            std::vector<Wish *> load(){ return std::vector<Wish*>{
                new Wish(0, "To eat"),
                new Wish(1, "To sleep")
            }; };
        };

        class WishManager: public Manager<IdType, Wish>
        {
        public:
            WishManager(/* args */) = default;
            virtual ~WishManager() {}
            
            std::vector<AddictionInfo> makeAddictions()
            {
                std::vector<AddictionInfo> r;
                for (auto && w : this->getAll())
                {
                    r.push_back(AddictionInfo(w->id(), 10));
                }

                return r;
            }
        };
    }
}