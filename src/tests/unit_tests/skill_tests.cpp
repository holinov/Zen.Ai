#include <zenai/stdafx.h>
#include <zenai/skill.h>
//#include <zenai/managers.h>
#include <zenai/managers.h>

using namespace Zen::AI;

/********************************
 *  Тестирование умений
 ********************************/
class SkillTest : public ::testing::Test
{
protected:
    Manager<IdType, Skill> smgr;
    Manager<IdType, Action> amgr;

    SkillTest()
    {
        smgr.LoadActions();
        amgr.LoadActions();
    }

    ~SkillTest() {}
};

/********************************
 *  Проверка конструкторов умений
 ********************************/
TEST_F(SkillTest, ManagerLoad)
{
    auto actions = amgr.getAll();
    auto skills  = smgr.getAll();

    ASSERT_EQ(actions.size(), skills.size());
    for (auto && act : actions)
    {
        ASSERT_TRUE(smgr.contains(act->id()));
        auto s = smgr.get(act->id());

        ASSERT_NE(nullptr, s);
    }
}

/********************************
 *  Проверка исполнения базовых умений
 ********************************/
TEST_F(SkillTest, SkillApply)
{
    Character *ch = new Character();
    EXPECT_TRUE(false) << "Написать тесты для умений";
}

/********************************
 *  Проверка роста уровней умений
 ********************************/
TEST_F(SkillTest, SkillLvlUp)
{
    EXPECT_TRUE(false) << "Написать тесты для умений";
}

/********************************
 *  Проверка исполнения составных умений
 ********************************/
TEST_F(SkillTest, CompositeSkillApply)
{
    EXPECT_TRUE(false) << "Написать тесты для умений";
}