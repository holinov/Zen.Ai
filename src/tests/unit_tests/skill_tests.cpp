#include <zenai/stdafx.h>
#include <zenai/skill.h>
//#include <zenai/managers.h>
#include <zenai/managers.h>
#include <zenai/char_generator.h>

using namespace Zen;
using namespace Zen::AI;

/********************************
 *  Тестирование умений
 ********************************/
class SkillTest : public ::testing::Test
{
protected:
    Manager<Skill>* smgr;
    Manager<Action>* amgr;

    SkillTest()
    {
        amgr = Manager<Action>::instance();
        smgr = Manager<Skill>::instance();
    }

    ~SkillTest() {}
};

/********************************
 *  Проверка конструкторов умений
 ********************************/
TEST_F(SkillTest, ManagerLoad)
{
    auto actions = amgr->getAll();
    auto skills  = smgr->getAll();

    ASSERT_EQ(actions.size(), skills.size());
    for (auto && act : actions)
    {
        ASSERT_TRUE(smgr->contains(act->id()));
        auto s = smgr->get(act->id());

        ASSERT_NE(nullptr, s);
    }
}

/********************************
 *  Проверка исполнения базовых умений
 ********************************/
TEST_F(SkillTest, SkillApply)
{
    //Создать мир, персонажа, локацию и контекст
    CharGenerator gen;
    World *w = new World();
    Character *ch = gen.generate();
    Location *loc = new Location(0,0,w);
    Context *ctx = new Context(ch,loc);

    //Добавить ресурс на локацию
    loc->inventory()->add(new Food(), 10);

    //Взть скилл для проверки
    Skill *s = smgr->getAll()[0];

    //Применить скилл к контексту
    s->applySkill(ctx);

    //проверить историю персонажа
    ASSERT_EQ(1, ch->history()->count());

    //проверить изменения параметров
    ASSERT_EQ(109, ch->stat(Character::Stats::Survival::Energy)); //109 тк одно очно энергии ушло на исполнение умения
    ASSERT_EQ(110, ch->stat(Character::Stats::Survival::Water));
    ASSERT_EQ(110, ch->stat(Character::Stats::Survival::Food));

    delete ctx;
    delete loc;
    delete ch;
    delete w;
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