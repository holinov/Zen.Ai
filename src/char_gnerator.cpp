#include <zenai/character.h>
#include <zenai/char_generator.h>
#include <zenai/managers.h>

namespace Zen
{
    namespace AI
    {

        Character* CharGenerator::generate()
        {
            Character *ch = new Character();

            WishManager wishManager;
            ch->addictions(wishManager.makeAddictions());
            for (auto && w : wishManager.getAll())
            {
                ch->modifyWish(w->id(), 15);
            }

            Manager<Skill>* skillManager = Manager<Skill>::instance();
            for(auto&& s : skillManager->getAll()) {
            	ch->addSkill(s);
            }

            return ch;
        }

    }
}