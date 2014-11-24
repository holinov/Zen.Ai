#include <zenai/stdafx.h>
#include <zenai/action.h>
#include <zenai/world.h>
#include <zenai/character.h>
#include <zenai/context.h>

using namespace Zen::AI;

/********************************
 *  Тестирование действий
 ********************************/
class TestAction : public Action
{
private:
public:
    TestAction(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes)
        : Action(id, name, cost, affectedWishes)
    {}

    TestAction(IdType id, std::string name, int cost)
        : Action(id, name, cost, {{0,100},{1,30}})
    {}

    /**
     * Когда перегруженно в дочерних класах дает возможность повлиять на контекст событий
     *
     * @param ctx Контекст действий
     */
    virtual bool applyToContext(Context *ctx)
    {
        return true;
    };

    /**
     * @brief Когда перегруженно в дочерних классах определяет возможность исполнения действия
     *
     * @param ctx Контекст действий
     * @return true если применимо к текущему контексту
     */
    virtual bool isApplyable(Context *ctx)
    {
        return true;
    };
};

class ActionTest : public ::testing::Test
{
protected:
    IdType _id = 14;
    std::string _name = "Action Name";
    int _cost = 5;
    Character* _ch;
    Context* _ctx;
    Location* _loc;

    ActionTest() {
        _ch = new Character();
        _loc = new Location(0,0, nullptr);
        _ctx = new Context(_ch,_loc);
    }

    ~ActionTest(){
        delete _ch;
        delete _loc;
        delete _ctx;
    }
};

/********************************
 *  Проверка свойств действия
 ********************************/
TEST_F(ActionTest, Property)
{
    auto action = new TestAction(_id, _name, _cost);
    ASSERT_EQ(_id, action->id());
    ASSERT_EQ(_name, action->name());
    ASSERT_EQ(_cost, action->cost());
}

/********************************
 *  Проверка базовых методов
 ********************************/
TEST_F(ActionTest, BasicMethods)
{
    auto action = new TestAction(_id, _name, _cost);
    ASSERT_EQ(action->isApplyable(_ctx), true);
    ASSERT_EQ(action->applyToContext(_ctx), true);

    //Применить на 30ом уровне умения
    auto results = action->applyResults(_ctx,30);

    //Проверить историю действий
    auto firstResult = results[0];
    ASSERT_EQ(results.size(), 2);
    ASSERT_EQ(_id, firstResult.ActionId);
    ASSERT_EQ(0, firstResult.WishId);
    ASSERT_EQ(130, firstResult.Result);
}