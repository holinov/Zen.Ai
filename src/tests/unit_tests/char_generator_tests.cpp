#include <zenai/stdafx.h>
#include <zenai/character.h>
#include <zenai/char_generator.h>


using namespace Zen::AI;

/********************************
 *  Тестирование мира
 ********************************/
class CharGeneratorTest : public ::testing::Test
{
protected:

    CharGeneratorTest()
    {

    }

    ~CharGeneratorTest() {}
};

/********************************
 *  Проверка генератора персонажей
 ********************************/
TEST_F(CharGeneratorTest, Generate)
{
    CharGenerator gen;
    Character *ch = gen.generate();

    //Проверяем что появились какие-то скилы
    ASSERT_NE(0, ch->skills().size());

    //Проверяем наличие склонностей
    ASSERT_NE(0, ch->addictions().size());

    //Прверим реальность генерации умения
    Manager<Skill>* m = Manager<Skill>::instance();
    for (auto && skill : ch->skills())
    {
        auto skill1 = m->get(skill.second.skillId());
        ASSERT_NE(nullptr, skill1);
    }
}