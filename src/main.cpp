#include "stdafx.h"
#include "log.h"
#include "world.h"
//#include "ai_common.h"
//#include "steps.h"

using namespace std;
using namespace Zen::Log;
using namespace Zen::AI;

int main(int argc, char const *argv[])
{
    MTLog::Instance().Info() << "Zen Ai Startup";
    World world;
    world.generateWorld(3,2,1);

    world.makeWorldStep();
    char i;
    std::cin >> i;
    world.makeWorldStep();
    
    std::cin >> i;
    world.makeWorldStep();
    //ActionManager itemManager;
    //itemManager.LoadActions();

    //for(auto&& item : itemManager.getAll()) {
    //	std::cout << item->id() << "\t: " << item->name() << std::endl;
    //}
    //auto person = Person("Test person");
    //person.LogPerson();

    return 0;
}