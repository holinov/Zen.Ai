#include <zenai/managers.h>
#include <zenai/steps.h>

namespace Zen
{
    namespace AI
    {
        /*void ItemManager::LoadActions()
        {
            Item *i = new Food();
            set(i->id(), i);
        }*/


        /*void WishManager::LoadActions()
        {
            IdType i = 0;

            Wish *w1 = new Wish(i, "To eat");
            set(i, w1);

            ++i;
            Wish *w2 = new Wish(i, "To sleep");
            set(i, w2);
        }*/

        void ActionManager::LoadActions()
        {
            IdType i = 0;

            Action *a1 = new Steps::EatRawAction();
            set(a1->id(), a1);

            Action *a2 = new Steps::CollectFoodAction();
            set(a2->id(), a2);

            a2=new Steps::RestAction();
            set(a2->id(),a2);
        }

    }
}