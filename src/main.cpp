#include "stdafx.h"
#include "log.h"
#include "ai_common.h"

using namespace std;
using namespace Zen::Log;
using namespace Zen::AI;

int main(int argc, char const *argv[])
{
    MTLog::Instance().Info() << "Zen Ai Startup";
    Manager<IdType,Item> itemManager;
    //auto person = Person("Test person");
    //person.LogPerson();

    return 0;
}