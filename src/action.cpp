#include <zenai/action.h>
#include <zenai/context.h>
#include <zenai/character.h>

std::vector<Zen::AI::ActionResult> Zen::AI::Action::applyResults(Context *ctx, int skillLvl)
{
    //Применить действие к контексту
    applyToContext(ctx);

    std::vector<ActionResult> res;
    for (auto && wish : _affectedWishes)
    {
        //Изменени уровня желания = Базовый уровень + Базовый уровень % Уровень умения
        float modifyLvlF = wish.second + (float)wish.second / 100 * skillLvl;

        //Усекаем до целых
        int modifyLvl = (int)modifyLvlF;

        //Log::MTLog::Instance().Debug() << "Modify wish:" << wish.first << " level: " << modifyLvl << " addition: " << (float)wish.second / 100 * skillLvl;

        //Прменить изменения уровня желания
        ctx->actorInfo().actor()->modifyWish(wish.first, -modifyLvl);

        //Формируем запись в историю
        res.push_back(Zen::AI::ActionResult(id(), wish.first, modifyLvl));
    }

    auto stat = ctx->actorInfo().actor()->stat(Character::Stats::Survival::Energy);
    ctx->actorInfo().actor()->stat(Character::Stats::Survival::Energy, stat - cost());

    return res;
}