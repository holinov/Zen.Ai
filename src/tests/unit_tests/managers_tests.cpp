#include <zenai/stdafx.h>
#include <zenai/managers.h>



using namespace Zen::AI;

/********************************
 *  Тестирование мира
 ********************************/
class ManagersTest : public ::testing::Test
{
protected:

    ManagersTest()
    {

    }

    ~ManagersTest() {}
};

/********************************
 *  Проверка Singletone менеджеров ресурсов
 ********************************/
TEST_F(ManagersTest, Instantate)
{
    //Инстанцировать шаблоны
    auto iManager = Manager<Item>::instance();
    auto aManager = Manager<Action>::instance();
    auto wManager = Manager<Wish>::instance();
    auto sManager = Manager<Skill>::instance();

    //Проверить что возвращается такой-же указатель как и в прошлый раз
    ASSERT_EQ(iManager, Manager<Item>::instance());
    
    //Проверить что для всех инстанцированных шаблонов указатель не null
    ASSERT_NE(nullptr, iManager);
    ASSERT_NE(nullptr, aManager);
    ASSERT_NE(nullptr, wManager);
    ASSERT_NE(nullptr, sManager);

    //Проверить что в менеджерах есть элементы
    EXPECT_GT(iManager->getAll().size(), 0);
    EXPECT_GT(aManager->getAll().size(), 0);
    EXPECT_GT(wManager->getAll().size(), 0);
    EXPECT_GT(sManager->getAll().size(), 0);

    //Заведомо пустой менеджер
    auto inManager = Manager<HasId>::instance();
    EXPECT_EQ(inManager->getAll().size(), 0);
}