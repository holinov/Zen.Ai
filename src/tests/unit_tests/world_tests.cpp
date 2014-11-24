#include <zenai/stdafx.h>
#include <zenai/action.h>
#include <zenai/world.h>
#include <zenai/character.h>
#include <zenai/context.h>

using namespace Zen::AI;

/********************************
 *  Тестирование мира
 ********************************/
class WorldTest : public ::testing::Test
{
protected:
    const uint MAX_X = 3;
    const uint MAX_Y = 5;
    const uint MAX_CHARS = 20;

    World *makeWorld()
    {
        World *w = new World();
        w->generateWorld(MAX_X, MAX_Y, MAX_CHARS);
        return w;
    }

    WorldTest()
    {

    }

    ~WorldTest() {}
};

/********************************
 *  Проверка свойств мира
 ********************************/
TEST_F(WorldTest, Generate)
{
    World *w = makeWorld();

    //Проверить что сгенерировалось должное кол-во локаций
    auto locs = w->locations();
    ASSERT_EQ(MAX_X * MAX_Y, locs.size());

    //Проверить что все локации правильно привязаны
    for (auto && loc : locs)
    {
        ASSERT_EQ(w,loc->world());
    }

    //Проверить что сгенерировалось должное кол-во персонажей
    auto chars = w->characters();
    ASSERT_EQ(MAX_CHARS, chars.size());

    delete w;
}

/********************************
 *  Проверка свойств мира
 ********************************/
TEST_F(WorldTest, Locations)
{
    World *w = makeWorld();

    //Проверить насыщенность ресурсами
    auto locs = w->locations();
    for (auto && loc : locs)
    {
        auto locInventory = loc->inventory();
        EXPECT_GT(locInventory->count(), 0) << "Not every location has resource";
    }

    delete w;
}