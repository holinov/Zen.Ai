#include <algorithm>
#include <zenai/character.h>
#include <zenai/inventory.h>
#include <zenai/wish.h>
#include <zenai/managers.h>

IdType Zen::AI::Character::curId = 0;

const std::string Zen::AI::Character::Stats::Social::Attractivnes = "Social.Attractivnes";
const std::string Zen::AI::Character::Stats::Social::Influence = "Social.Influence";

const std::string Zen::AI::Character::Stats::Survival::Energy = "Survival.Energy";
const std::string Zen::AI::Character::Stats::Survival::Food = "Survival.Food";
const std::string Zen::AI::Character::Stats::Survival::Water = "Survival.Water";;

const std::string Zen::AI::Character::Stats::Common::TotalExp = "Common.TotalExp";
const std::string Zen::AI::Character::Stats::Common::Happines = "Common.Happines";
const std::string Zen::AI::Character::Stats::Common::Wealth = "Common.Wealth";

namespace Zen
{
    namespace AI
    {

        static bool compare_wishes(WishInfo w1, WishInfo w2)
        {
            return w1.wishLvl() > w2.wishLvl();
        }

        Character::Character()
            : _wishes()
            , _addictions()
            , _skills()
            , _stats({  {Stats::Social::Attractivnes, 100}
            , {Stats::Social::Influence, 100}
            , {Stats::Survival::Energy, 100}
            , {Stats::Survival::Food, 100}
            , {Stats::Survival::Water, 100}
            , {Stats::Common::TotalExp, 0}
            , {Stats::Common::Happines, 100}
            , {Stats::Common::Wealth, 0}
        })
        {
            id(++curId);
            _Inventory = new Inventory();
            _history = new SkillHistoryManager();
        };

        Character::~Character()
        {
            delete _Inventory;
            delete _history;
        }


        void Character::makeAction(Context *ctx)
        {
            //Повысить уровни желаний
            for (auto && add : _addictions)
            {
                auto lvl = _wishes[add.second.wishId()].wishLvl();
                _wishes[add.second.wishId()].wishLvl(lvl + add.second.wishLvl());
            }

            //Выбрать желание которое будем удовлетворять
            std::vector<WishInfo> wishes;
            for (auto && s : _wishes)
            {
                wishes.push_back(s.second);
            }
            std::sort(wishes.begin(), wishes.end(), compare_wishes);
            WishInfo wishInfo = wishes[0];
            //          Log::MTLog::Instance().Debug() << "Selected wish " << wishInfo.wishId();

            //Выбрать умение для удовлетворения
            auto history = wishInfo.history();

            Manager<Action>* mgr = Manager<Action>::instance();
            auto action = mgr->getAll()[0];

            action->applyResults(ctx, 1);
            Log::MTLog::Instance().Debug() << "Selected action " << action->name() << " DONE";


            /*auto l1 = _wishes[wishInfo.wishId()].wishLvl();
            if(l1 < 30)
                _wishes[wishInfo.wishId()].wishLvl(0);
            else
                _wishes[wishInfo.wishId()].wishLvl(l1 - 30);*/

            //Если умения нету или выпал шанс попробовать новое умение - выбрать их истории
        }

        void Character::modifyWish(IdType wishId, int modifyLvl)
        {
            auto it = _wishes.find(wishId);
            if (it == _wishes.end())
                _wishes[wishId] = WishInfo(wishId, 0);

            _wishes[wishId].addWishLvl(modifyLvl);
        }


        SkillInfo *Character::skill(IdType skillId)
        {
            auto it = _skills.find(skillId);
            if (it == _skills.end())
            {
                _skills[skillId] = SkillInfo(skillId, 0);
            }
            return &_skills[skillId];
        }

        std::vector<WishInfo> Character::wishes()
        {
            std::vector<WishInfo> res;
            for (auto && i : _wishes)
            {
                res.push_back(i.second);
            }
            return res;
        }

        std::vector<AddictionInfo> Character::addictions()
        {
            std::vector<AddictionInfo> res;
            for (auto && i : _addictions)
            {
                res.push_back(i.second);
            }
            return res;
        }

        void Character::addictions(std::vector<AddictionInfo> adds)
        {
            for (auto && a : adds)
            {
                _addictions[a.wishId()] = a;
                modifyWish(a.wishId(), 0);
            }
        }

        void Character::addWishHistory(const SkillResult &sr)
        {
            _history->add(sr);
            for (auto && wish : sr.affectedWishes())
            {
                _wishes[wish.first].addHistroy(sr);
            }
        }

        void Character::addSkill(Skill *skill)
        {
            IdType skillId = skill->id();
            auto it = _skills.find(skillId);
            if (it == _skills.end())
            {
                _skills[skillId] = SkillInfo(skillId, 10);
            }
        }

    } // AI
} // Zen