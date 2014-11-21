#pragma once
#include "stdafx.h"
#include "context.hpp"
#include "action.hpp"

namespace Zen
{
    namespace AI
    {

        /**
         * @brief Результат исполнения действия
         */
        struct ActionResult
        {

            /**
             * @brief ИД Умения
             */
            IdType ActionId;

            /**
             * @brief ИД Умения
             */
            IdType WishId;

            /**
             * @brief Результат действия
             */
            int Result;

            ActionResult(IdType actionId, IdType wishId, int result)
                : ActionId(actionId)
                , WishId(wishId)
                , Result(result)
            {};
        };

        /**
         * @brief Действие существа
         * @details Действие стоит определенное кол-во энергии
         * Влияет на одно или несколько желаний существа
         * Имеет требования к контексту выполнения
         */
        class Action : public HasId, public HasName
        {
        private:
            int _actionCost;
            std::map<IdType, int> _affectedWishes;

        public:
            Action(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes)
                : HasId(id)
                , HasName(name)
                , _actionCost(cost)
                , _affectedWishes(affectedWishes)
            {};

            /**
             * @brief Стоимость действия
             */
            inline const int cost()
            {
                return _actionCost;
            }

            /**
             * Когда перегруженно в дочерних класах дает возможность повлиять на контекст событий
             *
             * @param ctx Контекст действий
             */
            virtual void applyToContext(Context *ctx) = 0;

            /**
             * @brief Применить результаты действия
             *
             * @param ctx Контекст ситуации
             * @param skillLvl Уровень умения с которым выполняется дейтвие
             */
            std::vector<ActionResult> applyResults(Context &ctx, int skillLvl)
            {
                //Применить действие к контексту
                applyToContext(ctx);

                std::vector<ActionResult> res;
                for (auto && wish : _affectedWishes)
                {
                    //Изменени уровня желания = Базовый уровень + Базовый уровень % Уровень умения
                    int modifyLvl = wish.second + wish.second / 100 * skillLvl;

                    //Прменить изменения уровня желания
                    ctx.actorInfo().modifyWish(wish.first, modifyLvl);

                    //Формируем запись в историю
                    res.push_back(ActionResult(id(), wish.first, modifyLvl));
                }

                return res;
            }

            /**
             * @brief Когда перегруженно в дочерних классах определяет возможность исполнения действия
             *
             * @param ctx Контекст действий
             * @return true если применимо к текущему контексту
             */
            virtual bool isApplyable(Context *ctx) = 0;
        };
    }



    namespace Actions
    {
        namespace Steps
        {
        	/**
        	 * @brief Контекст выполнения шага
        	 * 
        	 */
        	struct StepContext {
        		IdType itemType;
        		uint ammount;
        		std::string stat;
        		std::string resourceType;
        		Resource* resource;

        		StepContext()
        			:itemType()
        			,ammount()
        			,stat()
        			,resourceType()
        			,resource()
        		{}
        	};

        	/**
        	 * @brief Шаг составного действия
        	 */
            class ActionStep
            {
            private:

            protected:
                ActionStep() = default;
            public:
                virtual ~ActionStep() {};

                /**
                 * @brief Применить шаг к контексту события
                 * @details [long description]
                 * 
                 * @param ctx Контекст действяи
                 * @param stepCtx Контекст шага
                 * 
                 * @return true если шаг исполнен
                 */
                virtual bool applyToContext(Context *ctx, StepContext* stepCtx) = 0;

                /**
                 * @brief Когда прергруженно в доченрних классах определяет возможность исполнения шага
                 * 
                 * @param ctx Контекст действяи
                 * @param stepCtx Контекст шага
                 * 
                 * @return true если шаг возможно исполнить
                 */
                virtual bool isApplyable(Context *ctx, StepContext* stepCtx) const = 0;
            };

            namespace ActionSteps
            {
            	/**
            	 * @brief Базовый класс шагов использующих ресурсы и контекст
            	 * 
            	 */
            	class ResourceStep : public ActionStep {
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

            		virtual ~ResourceStep() {}
            	};

            	/**
            	 * @brief Потребить ресурс (из инвентаря или мира)	
            	 */
                class ConsumeStep : ResourceStep
                {
                public:
                    ConsumeStep(IdType itemType, unsigned int ammount)
                        : ResourceStep(itemType, ammount)
                    {};

                    ConsumeStep(unsigned int ammount)
                        : ResourceStep(itemType, ammount)
                    {
                    };

                    virtual ~ConsumeStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext* stepCtx)
                    {
                        //Взять ресурс из природы
                        Inventroy &inv = ctx->actorInfo().character().inventory();

                        if(_useContext)
                        {
                        	_type=stepCtx->itemType;
                        }

                        if (!inv.hasItemTypeId(_type, _ammount))
                            inv = ctx.location().inventory();

                        if (invinv.hasItemTypeId(_type, _ammount))
                        {
                            ctx->location().inventory().take(_type, _ammount);
                            return true;
                        }

                        return false;
                    }

                    virtual bool isApplyable(Context *ctx, StepContext* stepCtx) const
                    {
                        return ctx->actorinfo().character().inventory().hasItemTypeId(_type, _ammount)
                               || ctx->location().inventory().hasItemTypeId(_type, _ammount);
                    }
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
                        ,_ammountFromContext(false)
                    {};

                    LootStep(unsigned int ammount)
                        : ResourceStep(ammount)
                        ,_ammountFromContext(false)
                    {};


                    LootStep()
                        : ResourceStep(0)
                        ,_ammountFromContext(true)
                    {};

                    virtual ~LootStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext* stepCtx) const
                    {
                    	//Взять ресурс из природы
                        Inventroy &inv = ctx->actorInfo().character().inventory();

                        if(_useContext)
                        {
                        	_type=stepCtx->itemType;
                        }

                        if(_ammountFromContext){
                        	_ammount = ctx->location().inventory().getResourceCount(_type);                        	
                        }

                        if (inv.hasItemTypeId(_type, _ammount))
                        {
                            ctx->location().inventory().take(_type, _ammount);
                            ctx->actorinfo().character().inventory().add(_type, _ammount);
                            return true;
                        }

                        return false;
                    }
                };

                /**
                 * @brief Найти лучший ресурс заданного типа
                 */
                class FindBestResourceOfTypeStep : ActionStep {
                private:
                	std::string _resType;
                public:
                	FindBestResourceOfTypeStep(std::string resType)
                        : _resType(resType)
                    {};

                    virtual ~FindBestResourceOfTypeStep() {}
                    virtual bool applyToContext(Context *ctx, StepContext* stepCtx)
                    {
                    	InventoryItem items;
                        //Найти все ресурсы нужного типа
                        std::vector<InventoryItem> resources = ctx.location().inventory().getResourceOfType(_resType);
                        for(auto&& res : ctx->actorinfo().character().inventory().getResourceOfType(_resType)) {
                        	resources.push_back(res);
                        }

                        //Выбрать лучший
                        InventoryItem bestItem = *(resources.begin());
                        Resource* resInfo = items.get(bestItem.type());

                        for(auto&& res : resources) {
                        	Resource* nextInfo = items.get(res->type());
                        	if(nextInfo->value() > resInfo->value()){
                        		resInfo = nex;
                        	}
                        }

                        //Применить изменения контекста шага после поиска
                        stepCtx->itemType = bestItem.type();
                        stepCtx->resource = resInfo;
                        stepCtx->ammount = bestItem.count();

                        return true;
                    }
                    virtual bool isApplyable(Context *ctx, StepContext* stepCtx) const
                    {
                        return 	ctx->actorinfo().character().inventory().hasResourceOfType(_resType)
                        		|| ctx->location.inventory().hasResourceOfType(_resType);
                    }
                };

                class ChangeStatStep : ActionStep
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
                    virtual bool applyToContext(Context *ctx, StepContext* stepCtx)
                    {
                    	std::string stat = _stat;
                    	int change = _change
                    	if(_useContext) stat = stepCtx->change;

                        uint old = ctx->actorinfo().character().stat(stat);
                        #warning продумать контекст изменения статов
                        ctx->actorinfo.character().stat(stat, old + resource->value());
                        return true;
                    }
                    virtual bool isApplyable(Context *ctx, StepContext* stepCtx) const
                    {
                        return true;
                    }
                };


                class StepsAction : Action
                {
                protected:
                    std::vector<ActionStep> _steps;
                public:
                    StepsAction(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes, std::vector<ActionStep> steps)
                        : Action(id, name, affectedWishes)
                        , _steps(steps)
                    {};

                    StepsAction(IdType id, std::string name, int cost, std::map<IdType, int> affectedWishes)
                        : Action(id, name, affectedWishes)
                        , _steps()
                    {};

                    virtual ~StepsAction() {}
                    virtual bool applyToContext(Context *ctx)
                    {
                    	StepContext* sctx=new StepContext();
                        for (auto && step : _steps)
                        {
                            if (!step.applyToContext(ctx,sctx))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    virtual bool isApplyable(Context *ctx) const
                    {
                    	StepContext* sctx=new StepContext();
                        for (auto && step : _steps)
                        {
                            if (!step.isApplyable(ctx,sctx))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                };
            }

            class EatRawAction : public StepsAction {
            public:
            	EatAction() : StepsAction(0, "Eat raw", {0, 10}) 
                {
                	_steps.push_back(ActionSteps::FindBestResourceOfTypeStep(ResourceTypes::FOOD))
                	_steps.push_back(ActionSteps::ConsumeStep(1));
                    _steps.push_back(ActionSteps::ChangeStatStep(Character::Stats::Common::Energy));
                    _steps.push_back(ActionSteps::ChangeStatStep(Character::Stats::Common::Food));
                    _steps.push_back(ActionSteps::ChangeStatStep(Character::Stats::Common::Water)); 
                }
            };

            class CollectFoodAction : public StepsAction {
            public:
            	CollectFoodAction() : StepsAction(0, "Collect food", {0, 10}) 
                {
                	_steps.push_back(ActionSteps::FindBestResourceOfTypeStep(ResourceTypes::FOOD))
                	_steps.push_back(ActionSteps::LootStep()); 
                }
            };
        }
    }