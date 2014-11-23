#pragma once
#include "stdafx.h"
#include "manager.h"
#include "action.h"
#include "wish.h"
#include "item.h"

namespace Zen
{
    namespace AI
    {  
        class ItemManager: public Manager<IdType, Item> {
        private:
        	
        public:
        	ItemManager() = default;
            virtual ~ItemManager(){};
        	virtual void LoadActions();
        };

        class WishManager: public Manager<IdType, Wish>
        {
        private:
            /* data */
        public:
            WishManager(/* args */) = default;
            virtual ~WishManager() {}
            virtual void LoadActions();
        };

        class ActionManager: public Manager<IdType, Action>
        {
        private:
        public:
            ActionManager() = default;
            virtual ~ActionManager(){};
            virtual void LoadActions();
        };
    }
}