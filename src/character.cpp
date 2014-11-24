#include <algorithm>
#include <zenai/character.h>
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

    	static bool compare_wishes(WishInfo w1, WishInfo w2){
    		return w1.wishLvl() > w2.wishLvl();
    	}

        void Character::makeAction(Context *ctx)
        {
        	//Повысить уровни желаний
        	for(auto&& add : _addictions) {
        		auto lvl = _wishes[add.second.wishId()].wishLvl();
        		_wishes[add.second.wishId()].wishLvl(lvl + add.second.wishLvl());
        	}

        	//Выбрать желание которое будем удовлетворять
        	std::vector<WishInfo> wishes;
        	for(auto&& s : _wishes) {
        		wishes.push_back(s.second);
        	}
        	std::sort(wishes.begin(),wishes.end(),compare_wishes);

        	//Выбрать умение для удовлетворения
        	WishInfo wishInfo = wishes[0];
        	Log::MTLog::Instance().Debug() << "Selected wish " << wishInfo.wishId();

        	ActionManager mgr;
        	mgr.LoadActions();
        	auto action = mgr.getAll()[0];

        	Log::MTLog::Instance().Debug() << "Selected action \"" << action->name() << "\"";
        	action->applyResults(ctx,1);
        	Log::MTLog::Instance().Debug() << "Selected action " << action->name() << " DONE";


        	/*auto l1 = _wishes[wishInfo.wishId()].wishLvl();
        	if(l1 < 30)
        		_wishes[wishInfo.wishId()].wishLvl(0);        	
        	else
        		_wishes[wishInfo.wishId()].wishLvl(l1 - 30);*/

        	//Если умения нету или выпал шанс попробовать новое умение - выбрать их истории
        }
    } // AI
} // Zen