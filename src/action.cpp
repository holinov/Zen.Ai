#include "action.h"
#include "context.h"

std::vector<Zen::AI::ActionResult> Zen::AI::Action::applyResults(Context *ctx, int skillLvl)
{
    //Применить действие к контексту
    applyToContext(ctx);

    std::vector<ActionResult> res;
    for (auto && wish : _affectedWishes)
    {
        //Изменени уровня желания = Базовый уровень + Базовый уровень % Уровень умения
        int modifyLvl = wish.second + wish.second / 100 * skillLvl;

        //Прменить изменения уровня желания
        ctx->actorInfo().actor()->modifyWish(wish.first, modifyLvl);

        //Формируем запись в историю
        res.push_back(Zen::AI::ActionResult(id(), wish.first, modifyLvl));
    }

    return res;
}