#include "context.h"
#include "steps.h"
#include "item.h"
#include "action_steps.h"


namespace Zen
{
    namespace AI
    {
        namespace Steps
        {
            //namespace ActionSteps
            //{
                bool ConsumeStep::isApplyable(Context *ctx, StepContext *stepCtx)
                {
                    return ctx->actorInfo().actor()->inventory()->hasItemTypeId(_type, _ammount)
                           || ctx->location()->inventory()->hasItemTypeId(_type, _ammount);
                }

                bool ConsumeStep::applyToContext(Context *ctx, StepContext *stepCtx)
                {
                    //Взять ресурс из природы
                    Inventroy *inv = ctx->actorInfo().actor()->inventory();

                    if (_useContext)
                    {
                        _type = stepCtx->itemType;
                    }

                    if (!inv->hasItemTypeId(_type, _ammount))
                        inv = ctx->location()->inventory();

                    if (inv->hasItemTypeId(_type, _ammount))
                    {
                        InventoryItem item = InventoryItem(_type, _ammount);
                        inv->take(item);
                        return true;
                    }

                    return false;
                }

                bool LootStep::applyToContext(Context *ctx, StepContext *stepCtx)
                {
                    //Взять ресурс из природы
                    Inventroy *inv = ctx->actorInfo().actor()->inventory();

                    if (_useContext)
                    {
                        _type = stepCtx->itemType;
                    }

                    if (_ammountFromContext)
                    {
                        _ammount = ctx->location()->inventory()->resAmmount(_type);
                    }

                    if (inv->hasItemTypeId(_type, _ammount))
                    {
                        auto item = InventoryItem(_type, _ammount);
                        ctx->location()->inventory()->take(item);
                        ctx->actorInfo().actor()->inventory()->add(item);
                        return true;
                    }

                    return false;
                }

                bool LootStep::isApplyable(Context *ctx, StepContext *stepCtx)
                {
                    return ctx->actorInfo().actor()->inventory()->hasItemTypeId(_type, _ammount)
                           || ctx->location()->inventory()->hasItemTypeId(_type, _ammount);
                }

                bool FindBestResourceOfTypeStep::applyToContext(Context *ctx, StepContext *stepCtx)
                {
                    Manager<IdType, Item> items;
                    //Найти все ресурсы нужного типа
                    std::vector<InventoryItem> resources = ctx->location()->inventory()->getResourcesOfType(_resType);
                    for (auto && res : resources)
                    {
                        resources.push_back(res);
                    }

                    //Выбрать лучший
                    InventoryItem bestItem = *(resources.begin());
                    Resource *resInfo = dynamic_cast<Resource *>(items.get(bestItem.type()));

                    for (auto && res : resources)
                    {
                        Resource *nextInfo = dynamic_cast<Resource *>(items.get(res.type()));
                        if (nextInfo->value() > resInfo->value())
                        {
                            bestItem = res;
                            resInfo = nextInfo;
                        }
                    }

                    //Применить изменения контекста шага после поиска
                    stepCtx->itemType = bestItem.type();
                    stepCtx->resource = resInfo;
                    stepCtx->ammount = bestItem.count();

                    return true;
                }

                bool FindBestResourceOfTypeStep::isApplyable(Context *ctx, StepContext *stepCtx)
                {
                    return  ctx->actorInfo().actor()->inventory()->hasResourceOfType(_resType)
                            || ctx->location()->inventory()->hasResourceOfType(_resType);
                }

                bool ChangeStatStep::applyToContext(Context *ctx, StepContext *stepCtx)
                {
                    std::string stat = _stat;
                    int change = _change;
                    if (_useContext) change = stepCtx->ammount;

                    uint old = ctx->actorInfo().actor()->stat(stat);
#warning продумать контекст изменения статов
                    ctx->actorInfo().actor()->stat(stat, old + change);
                    return true;
                }

                bool ChangeStatStep::isApplyable(Context *ctx, StepContext *stepCtx)
                {
                    return true;
                }

            //}
        }
    }
}