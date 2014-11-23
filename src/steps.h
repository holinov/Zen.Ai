#pragma once
#include "action_steps.h"

namespace Zen
{
    namespace AI
    {
        namespace Steps
        {
            //namespace ActionSteps
            //{
            	/**
                 * @brief Базовый класс шагов использующих ресурсы и контекст
                 *
                 */
                class ResourceStep : public ActionStep
                {
                protected:
                    IdType _type;
                    unsigned int _ammount;
                    bool _useContext;

                    /**
                      * @param itemType тип ресурса
                      * @param int кол-во ресурса
                    */
                    ResourceStep(IdType itemType, unsigned int ammount)
                        : ActionStep()
                        , _type(itemType)
                        , _ammount(ammount)
                        , _useContext(false)
                    {};

                    /**
                      * @param itemType тип ресурса
                      * @param int кол-во ресурса
                    */
                    ResourceStep(unsigned int ammount)
                        : ActionStep()
                        , _type(0)
                        , _ammount(ammount)
                        , _useContext(true)
                    {};
                public:
                    virtual ~ResourceStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext *stepCtx) = 0;
                    virtual bool isApplyable(Context *ctx, StepContext *stepCtx) = 0;
                };

                /**
                 * @brief Потребить ресурс (из инвентаря или мира)
                 */
                class ConsumeStep : public ResourceStep
                {
                public:
                    ConsumeStep(IdType itemType, unsigned int ammount)
                        : ResourceStep(itemType, ammount)
                    {};

                    ConsumeStep(unsigned int ammount)
                        : ResourceStep(0, ammount)
                    {
                        _useContext = true;
                    };

                    virtual ~ConsumeStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext *stepCtx);
                    virtual bool isApplyable(Context *ctx, StepContext *stepCtx);
                };

                /**
                 * @brief Поднять в инвентарь
                 */
                class LootStep : public ResourceStep
                {
                private:
                    bool _ammountFromContext;
                public:
                    LootStep(IdType itemType, unsigned int ammount)
                        : ResourceStep(itemType, ammount)
                        , _ammountFromContext(false)
                    {};

                    LootStep(unsigned int ammount)
                        : ResourceStep(ammount)
                        , _ammountFromContext(false)
                    {};


                    LootStep()
                        : ResourceStep(0)
                        , _ammountFromContext(true)
                    {};

                    virtual ~LootStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext *stepCtx);
                    virtual bool isApplyable(Context *ctx, StepContext *stepCtx);                    
                };

                /**
                 * @brief Найти лучший ресурс заданного типа
                 */
                class FindBestResourceOfTypeStep : public ActionStep
                {
                private:
                    std::string _resType;
                public:
                    FindBestResourceOfTypeStep(std::string resType)
                        : _resType(resType)
                    {};

                    virtual ~FindBestResourceOfTypeStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext *stepCtx);
                    virtual bool isApplyable(Context *ctx, StepContext *stepCtx);
                };

                /**
                 * @brief Изменения стата персонажа
                 */
                class ChangeStatStep : public ActionStep
                {
                private:
                    std::string _stat;
                    int _change;
                    bool _useContext;
                public:
                    ChangeStatStep(std::string stat, int change)
                        : ActionStep()
                        , _stat(stat)
                        , _change(change)
                        , _useContext(false)
                    {};

                    ChangeStatStep(std::string stat)
                        : ActionStep()
                        , _stat(stat)
                        , _change()
                        , _useContext(true)
                    {};
                    virtual ~ChangeStatStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext *stepCtx);
                    virtual bool isApplyable(Context *ctx, StepContext *stepCtx);
                };


                class EatRawAction : public StepsAction
                {
                public:
                    EatRawAction() : StepsAction(0, "Eat raw", 1 , {{0, 10}})
                    {
                        _steps.push_back(new FindBestResourceOfTypeStep(ResourceTypes::FOOD));
                        _steps.push_back(new ConsumeStep(1));
                        _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Energy));
                        _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Food));
                        _steps.push_back(new ChangeStatStep(Character::Stats::Survival::Water));
                    }
                };

                class CollectFoodAction : public StepsAction
                {
                public:
                    CollectFoodAction() : StepsAction(0, "Collect food", 2, {{0, 10}})
                    {
                        _steps.push_back(new FindBestResourceOfTypeStep(ResourceTypes::FOOD));
                        _steps.push_back(new LootStep());
                    }
                };
            //}
        }
    }
}