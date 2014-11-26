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
    Manager<Skill> *smgr;
    Manager<Action> *amgr;

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
    Location *loc = new Location(0, 0, w);
    Context *ctx = new Context(ch, loc);

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
    ADD_FAILURE() << "Написать тесты для умений";
}

/********************************
 *  Проверка создания и исполнения составных умений
 ********************************/
TEST_F(SkillTest, CompositeSkill)
{
    CompositeSkillManager mgr;
    CharGenerator gen;
    World *w = new World();
    Character *ch = gen.generate();
    Location *loc = new Location(0, 0, w);
    Context *ctx = new Context(ch, loc);

    //Добавить ресурс на локацию
    loc->inventory()->add(new Food(), 10);

    // Наполнить историю событий
    Skill *s = smgr->getAll()[2];   // Rest x2
    s->applySkill(ctx);
    s->applySkill(ctx);

    s = smgr->getAll()[0];          // Eat Raw
    s->applySkill(ctx);

    // Попробовать создать композитный скилл для желания 0 (покушать)
    CompositeSkill *cskill = mgr.findCompositeInHistory(0, ch->history());

    //Проверить что такой скилл найден
    ASSERT_NE(nullptr, cskill);

    // Попробовать создать композитный скилл для не существующего желания
    CompositeSkill *cskill1 = mgr.findCompositeInHistory(100500, ch->history());

    //Проверить что такой скилл НЕ найден
    ASSERT_EQ(nullptr, cskill1);

    ADD_FAILURE() << "Сделать тестирование исполнения";
}