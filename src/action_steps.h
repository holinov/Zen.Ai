#pragma once
#include "stdafx.h"
#include "context.h"
#include "action.h"

namespace Zen
{
    namespace AI
    {
        namespace Steps
        {

            /**
             * @brief Контекст выполнения шага
             *
             */
            struct StepContext
            {
                IdType itemType;
                uint ammount;
                std::string stat;
                std::string resourceType;
                Resource *resource;

                StepContext()
                    : itemType()
                    , ammount()
                    , stat()
                    , resourceType()
                    , resource()
                {}
            };

            /**
             * @brief Шаг составного действия
             */
            class ActionStep
            {
            public:
                /**
                 * @brief Применить шаг к контексту события
                 * @details [long description]
                 *
                 * @param ctx Контекст действяи
                 * @param stepCtx Контекст шага
                 *
                 * @return true если шаг исполнен
                 */
                virtual bool applyToContext(Context *ctx, StepContext *stepCtx) = 0;

                /**
                 * @brief Когда прергруженно в доченрних классах определяет возможность исполнения шага
                 *
                 * @param ctx Контекст действяи
                 * @param stepCtx Контекст шага
                 *
                 * @return true если шаг возможно исполнить
                 */
                virtual bool isApplyable(Context *ctx, StepContext *stepCtx) = 0;

                virtual ~ActionStep() {}
            };


            /**
             * @brief Действие остоящие из нескольких шагов
             */
            class StepsAction : public Action
            {
            protected:
                std::vector<ActionStep *> _steps;
            public:
                StepsAction(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes, std::vector<ActionStep *> steps)
                    : Action(id, name, cost, affectedWishes)
                    , _steps(steps)
                {};

                StepsAction(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes)
                    : Action(id, name, cost, affectedWishes)
                    , _steps()
                {};

                virtual ~StepsAction()
                {
                    for (auto && s : _steps)
                    {
                        delete s;
                    }
                }
                virtual bool applyToContext(Context *ctx);
                virtual bool isApplyable(Context *ctx);
            };

            
        }
    }
}