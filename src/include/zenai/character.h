#pragma once
#include "stdafx.h"
//#include "inventory.h"
#include "skill.h"
//#include "addiction.h"

namespace Zen
{
    namespace AI
    {
        class WishInfo;
        class AddictionInfo;
        class SkillInfo;

        class SkillResult;
        class Context;
        class Inventory;

        class SkillHistoryManager
        {
        private:
            std::vector<SkillResult> _history;
        public:
            SkillHistoryManager()
                : _history()
            {};

            void add(const SkillResult &res)
            {
                _history.push_back(res);
            }

            uint const count() const{
                return _history.size();
            }

            std::vector<SkillResult> get()
            {
                return _history;
            }
        };

        /**
         * @brief Существо
         */
        class Character : public HasId
        {
        public:
            /**
             * @brief Характеристики существа
             */
            struct Stats
            {
                /**
                 * @brief Общие характеристики
                 */
                struct Common
                {

                    /**
                     * @brief Общий уровень опыта
                     */
                    static const std::string TotalExp;

                    /**
                     * @brief Уровень счастья
                     */
                    static const std::string Happines;

                    /**
                     * @brief Богатство
                     */
                    static const std::string Wealth;
                };

                /**
                 * @brief Характеристики выживания
                 */
                struct Survival
                {
                    /**
                     * @brief Энергия (расходуется на выполнение действий)
                     * @details При достижении 0 существо засыпает (выбирается умение восстанавливающее наибольшее кол-во энергии)
                     */
                    static const std::string Energy;

                    /**
                     * @brief Голод (при достижении 0 существо умирает)
                     */
                    static const std::string Food;

                    /**
                     * @brief Жажда (при достижении 0 существо умирает)
                     */
                    static const std::string Water;
                };

                /**
                 * @brief Социальные характеристики
                 */
                struct Social
                {

                    /**
                     * @brief Влиятельность]
                     */
                    static const std::string Influence;

                    /**
                     * @brief Привлекательность
                     * @details Используется для выбора партнера для размножения
                     */
                    static const std::string Attractivnes;
                };
            };
            static IdType curId;

        private:
            std::map<IdType, WishInfo> _wishes;
            std::map<IdType, AddictionInfo> _addictions;
            std::map<IdType, SkillInfo> _skills;
            std::map<std::string, int> _stats;
            SkillHistoryManager *_history;
            Inventory *_Inventory;

        public:
            Character();
            ~Character();

            /**
             * @brief Выполнить следующее действие (в зависимости от желаний существа)
             *
             * @param ctx Контекст действий
             */
            void makeAction(Context *ctx);

            /**
             * @brief Получить кол-во заданного ресурса в интвентаре
             *
             * @param resourceId ИД типа ресурса
             * @return Кол-во доступных ресурсов
             */
            int getResourceCount(IdType resourceId);

            /**
             * @brief Изменить уровень желания
             *
             * @param wishId ИД изменяемого желания
             * @param modifyLvl Уровень изменения желания
             */
            void modifyWish(IdType wishId, int modifyLvl);

            /**
             * @brief Инвентарь персонажа
             */
            inline Inventory *inventory()
            {
                return _Inventory;
            }

            /**
             * @brief Характеристика персонажа
             *
             * @param stat Название характеристики
             */
            int stat(std::string stat)
            {
                return _stats[stat];
            }

            /**
             * @brief Задать характеристику персонажа
             *
             * @param stat Название характеристики
             * @param val Новое значение
             */
            void stat(std::string stat, uint val)
            {
                _stats[stat] = val;
            }

            std::vector<WishInfo> wishes();

            /**
             * @brief Список склонностей персонажа
             */
            std::vector<AddictionInfo> addictions();

            /**
             * @brief Задать новый список склонностей персонажа
             *
             * @param adds Новый список зависимостей
             */
            void addictions(std::vector<AddictionInfo> adds);

            void addWishHistory(const SkillResult& sr);

            const SkillHistoryManager *history() const
            {
                return _history;
            }

            std::map<IdType, SkillInfo> skills()
            {
                return _skills;
            }

            void addSkill(Skill* skill);

            SkillInfo* skill(IdType skillId);
        };
    }
}