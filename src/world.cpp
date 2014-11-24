#include "world.h"
#include "log.h"
#include "item.h"
#include "managers.h"
#include "character.h"
#include "context.h"

static const std::string LINE = "=========================\r\n";

namespace Zen
{
    namespace AI
    {
        static void debugCharacter(Character *ch)
        {
            WishManager mgr;
            mgr.LoadActions();

            auto clog = Log::MTLog::Instance().Log("CharInfo") << "";
            clog << std::endl << LINE << "Character stats:" << std::endl << LINE << std::endl;
            std::vector<std::string> stats =
            {
                Character::Stats::Social::Attractivnes,
                Character::Stats::Social::Influence,
                Character::Stats::Survival::Energy,
                Character::Stats::Survival::Food,
                Character::Stats::Survival::Water,
                Character::Stats::Common::TotalExp,
                Character::Stats::Common::Happines,
                Character::Stats::Common::Wealth
            };

            for (auto && statName : stats)
            {
                clog << " " << statName << " = " << ch->stat(statName) << std::endl;
            }

            clog << LINE << "Character wishes:" << std::endl << LINE;

            auto wlist = ch->wishes();
            for (auto && wish : wlist)
            {
                Wish *wInfo = mgr.get(wish.wishId());

                clog << " " << wish.wishId() << ") " << wInfo->name() << " = " <<  wish.wishLvl() << std::endl;
            }

            clog << LINE << "Character addictions:" << std::endl << LINE;
            auto alist = ch->addictions();
            for (auto && wish : alist)
            {
                Wish *wInfo = mgr.get(wish.wishId());

                clog << " " << wish.wishId() << ") " << wInfo->name() << " = " <<  wish.wishLvl() << std::endl;
            }
            clog << LINE ;//<< "Character wishes:"<< std::endl;

        }

        Character *newCharacter()
        {
            Character *ch = new Character();

            WishManager mgr;
            mgr.LoadActions();
            ch->addictions(mgr.makeAddictions());

            for (auto && w : mgr.getAll())
            {
                ch->modifyWish(w->id(), 15);
            }

            debugCharacter(ch);
            return ch;
        }

        void World::generateCharacters(unsigned chars)
        {
            for (unsigned i = 0; i < chars; ++i)
            {
                _characters.push_back(newCharacter());
            }
        }

        struct genstat
        {
            uint locs;
            uint resources;
        };

        void World::makeWorldStep()
        {
            Location *l = _locations[0];

            Log::MTLog::Instance().Info() << "Making world step. " << l;
            for (auto && ch : _characters)
            {
                Context *ctx = new Context(ch, l);
                ch->makeAction(ctx);
                delete ctx;

                debugCharacter(ch);
            }
        }

        void World::generateWorld(unsigned maxX, unsigned maxY, unsigned chars)
        {
            ItemManager mgr;
            mgr.LoadActions();

            genstat stat {0, 0};

            Log::MTLog::Instance().Debug() << "World::generateWorld start X:" << maxX << " Y:" << maxY << " CH:" << chars;
            //std::vector<std::vector<Location*>> locs(maxX);
            //Сгенерировать локации
            //int count = 0;
            for (unsigned x = 0; x < maxX; ++x)
            {
                //std::vector<Location *> row(maxY);
                for (unsigned y = 0; y < maxY; ++y)
                {
                    Location *l = new Location(x, y, this);


                    //Сгенерировать стартовые ресурсы локации
#warning TODO: generate resources
                    for (auto && itype : mgr.getAll())
                    {
                        l->inventory()->add(itype, 3);
                    }
                    //l->generateResources();

                    ++stat.locs;
                    stat.resources += l->inventory()->count();

                    _locations.push_back(l);
                }
                //_locations.push_back(row);
            }

            ItemManager imgr;
            imgr.LoadActions();

            Log::MTLog::Instance().Debug() << "Locations" << LINE;
            for (auto && l : _locations)
            {
                Log::MTLog::Instance().Debug() << "Location x:" << l->x() << " y:" << l->y();
                for (auto && i : l->inventory()->getAll())
                {
                    Log::MTLog::Instance().Debug() << "Item: " << imgr.get(i.type())->name() << " " << i.count();
                }
            }

            Log::MTLog::Instance().Info() << "World::generateWorld done. " << stat.locs << " locations " << stat.resources << " resources";

            //Сгенерировать персонажей
            generateCharacters(chars);
        }
    }
}