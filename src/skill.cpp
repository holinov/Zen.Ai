#include <zenai/skill.h>
#include <zenai/context.h>
#include <zenai/character.h>

#include <functional>
#include <random>

namespace Zen
{
    namespace AI
    {
        static std::default_random_engine generator;
        static std::uniform_int_distribution<int> distribution(1, 100);
        static auto d100 = std::bind ( distribution, generator );

        bool Skill::applySkill(Context *ctx)
        {
            SkillResult sr;

            auto actor = ctx->actorInfo().actor();

            //Получаем текущий уровень умения
            SkillInfo* skillInfo = actor->skill(id());
            std::vector<ActionResult> results = applyToContext(ctx, skillInfo->skillLvl());

            //Записываем историю
            sr.SkillId = id();
            sr.Results = results;
            actor->addWishHistory(sr);

            //поднимаем уровень скила
            int roll = d100();
            if(roll <= skillInfo->skillExp()){
                skillInfo->skillExpInc();
            }
        }

    }
}