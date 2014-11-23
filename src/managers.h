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
        	virtual void LoadActions(){
            	Item *i=new Food();
                set(i->id(),i);
            }
        };

        class WishManager: public Manager<IdType, Wish>
        {
        private:
            /* data */
        public:
            WishManager(/* args */) = default;
            virtual ~WishManager() {}
        protected:
            virtual void LoadActions()
            {
                IdType i = 0;

                Wish *w1 = new Wish(i, "To eat");
                set(i, w1);

                Wish *w2 = new Wish(++i, "To sleep");
                set(i, w2);
            }
        };

        /*class ActionManager: public Manager<IdType, Action>
        {
        private:
        public:
            ActionManager() = default;
            virtual ~ActionManager()
            {};
        protected:
            virtual void LoadActions()
            {
                IdType i = 0;

                Action *a1 = new Action(i, "Eat raw", {0, 10});
                set(i, a1);

                Action *a2 = new Action(++i, "Sit", {1, 15});
                set(i, a2);
            }
        };*/
    }
}