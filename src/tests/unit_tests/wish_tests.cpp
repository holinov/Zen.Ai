#include <zenai/stdafx.h>
#include <zenai/action.h>
#include <zenai/world.h>
#include <zenai/character.h>
#include <zenai/context.h>

using namespace Zen::AI;

/********************************
 *  Тестирование желаний
 ********************************/
class WishTest : public ::testing::Test
{
protected:
    IdType _id = 14;
    int _lvl = 30;
    std::string _name = "Wish name";
    Wish* _wish;

    WishTest() {
        _wish = new Wish(_id,_name);
    }

    ~WishTest(){
        delete _wish;
    }
};

/********************************
 *  Проверка свойств желания
 ********************************/
TEST_F(WishTest, Wish_Property)
{
    auto wish = new Wish(_id, _name);
    ASSERT_EQ(_id, wish->id());
    ASSERT_EQ(_name, wish->name());
}

/********************************
 *  Проверка конструкторов WishInfo
 ********************************/
TEST_F(WishTest, WishInfo_Constructor)
{
    WishInfo wi1 = WishInfo(_id,_lvl);
    ASSERT_EQ(_id, wi1.wishId());
    ASSERT_EQ(_lvl, wi1.wishLvl());
    ASSERT_EQ(0, wi1.history().size());

    WishInfo wi2 = WishInfo(_wish,_lvl);
    ASSERT_EQ(_wish->id(), wi1.wishId());
    ASSERT_EQ(_lvl, wi1.wishLvl());
    ASSERT_EQ(0, wi1.history().size());

}

/********************************
 *  Проверка свойств WishInfo
 ********************************/
TEST_F(WishTest, WishInfo_Property)
{
    IdType id=14;
    int lvl = 134;
    WishInfo wi = WishInfo();
    wi.wishId(id);
    wi.wishLvl(lvl);

    ASSERT_EQ(id,   wi.wishId());
    ASSERT_EQ(lvl,  wi.wishLvl());
}