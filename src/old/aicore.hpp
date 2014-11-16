#pragma once

#include <vector>
#include "stdafx.h"
#include "log.h"


namespace Zen{
	using namespace Log;
	using namespace std;

	namespace AI{

		class HasName {
		private:
			std::string _name;
		public:
			HasName(std::string n)
				:_name(n)
			{}
			virtual ~HasName(){}

			const std::string getName(){
				return _name;
			}

			void setName(const std::string n){
				_name = n;
			}
		};

		template<typename T, typename K>
		class Manager {
		protected:
			std::vector<T*> _list;
			std::map<K,T*> _map;

		public:
			Manager()
				:_list()
				,_map()
			{};

			void add(T* i){
				_map[i->getId()]=i;
				_list.push_back(i);
			}

			T* get(K k){
				return _map[k];
			}

			virtual ~Manager(){
				for(auto&& i : _list) {
					delete i;
				}
			}
		};


		class Item : public HasName{
		private:
			/* data */
		public:
			Item(std::string name)
				:HasName(name)
			{}

			virtual ~Item(){};
		};

		/**
		 * @brief Требование умения
		 */
		class Requirement {
		private:

		public:
			Requirement() = default;
			virtual ~Requirement(){};
		};

		/**
		 * @brief Действие умения
		 */
		class Action : public HasName{
		private:
		public:
			Action(std::string name)
				:HasName(name)
			{}

			virtual ~Action(){};
		};

		/**
		 *  ID скилла
		 */
		typedef unsigned long SkillId;

		/**
		 * ID желания
		 */
		typedef unsigned long WishId;

		/**
		 * @brief Желание ИИ
		 */
		class Wish : public HasName {
		protected:
			
			WishId _wishId;
		
		public:
			Wish(WishId id, std::string name)
				:HasName(name)
				,_wishId(id)
			{}
			virtual ~Wish(){};

			const SkillId getId(){
				return _wishId;
			}
		};

		class WishToEat : public Wish {
		public:
			WishToEat()
				:Wish(0,"To eat")
			{};
		};

		class WishToSleep : public Wish {
		public:
			WishToSleep()
				:Wish(1,"To sleep")
			{};
		};

		class PersonWish {
		private:
			uint _wishLevel;
			Wish* _wish;
		public:
			PersonWish(Wish* wish,uint lvl) 
				:_wishLevel(lvl)
				,_wish(wish)
			{};

			PersonWish(const PersonWish& o) = default;

			const uint getLvl(){
				return _wishLevel;
			}

			void setLvl(uint lvl){
				_wishLevel = lvl;
			}

			/*const SkillId getId(){
				return _wishId;
			}*/

			Wish* getInfo(){
				return _wish;
			}
		};

		class WishManagerImpl : Manager<Wish,WishId> {
		public:
			WishManagerImpl() : Manager<Wish,WishId>()
			{
				add(new WishToEat());
				add(new WishToSleep());
			};

			Wish* getWish(WishId id){
				return get(id);
			}

			std::vector<PersonWish> populateWishes(){
				std::vector<PersonWish> ss;
				MTLog::Instance().Debug()<<"Populating wishes: " << _list.size();
				for(auto&& s : _list) {
					ss.push_back(PersonWish(s,10));
				}
				return ss;
			}
		};

		/**
		 * @brief Описание умения персонажа
		 */
		class Skill : public HasName{
		protected:
			/** 
			 * ИД Умения 
			 */
			SkillId _skillId;

			/** 
			 * Требования умения 
			 */
			std::vector<Requirement*> _required;

			/** 
			 * Действия умения 
			 */
			std::vector<Action*> _actions;
			
			/**
			 * @brief Желания на которые влияет умение
			 */
			std::vector<WishId> _affectedWishes;

		public:
			Skill(SkillId id,std::string name)
				:HasName(name)
				,_skillId(id)
				,_required()
				,_actions()
				,_affectedWishes()
			{}
			
			Skill(SkillId id,std::string name,std::vector<WishId> affects,std::vector<Requirement*> required,std::vector<Action*> actions)
				:HasName(name)
				,_skillId(id)
				,_required(required)
				,_actions(actions)
				,_affectedWishes(affects)
			{}

			virtual ~Skill(){};

			const SkillId getId(){
				return _skillId;
			}

			const std::vector<WishId> getWishes(){
				return _affectedWishes;
			}
		};

		class CollectFoodSkill : public Skill {
		public:
			CollectFoodSkill()
				:Skill(0,"Collect food",{0},{},{})
			{}
			;
		};


		class RestSkill : public Skill {
		public:
			RestSkill()
				:Skill(1,"Rest",{1},{},{})
			{}
			;
		};

		/** 
		 * Информация о текущем умении ИИ 
		 */
		class PersonSkill {
		private:
			Skill* _skill;
			short _lvl;
			short _successCount; 
		public:
			PersonSkill(Skill* skill)
				: _skill(skill)
				, _lvl(5)
				, _successCount(0)
			{};

			PersonSkill(const PersonSkill& o) = default;

			const short getLvl(){
				return _lvl;
			}

			Skill* getInfo(){
				return _skill;
			}

			void setLvl(short lvl){
				_lvl = lvl;
			}

			const short getSuccessCount(){
				return _successCount;
			}

			void incrementSuccessCount(){
				_successCount++;
			}
		};

		/**
		 * @brief Класс менеджер умений
		 */
		class SkillManagerImpl : Manager<Skill,SkillId> {
		public:		
			SkillManagerImpl() : Manager<Skill,SkillId>()
			{
				add(new CollectFoodSkill());
				add(new RestSkill());
			}

			Skill* getSkill(SkillId id){
				return get(id);
			}

			std::vector<PersonSkill> populateSkills(){
				std::vector<PersonSkill> ss;
				MTLog::Instance().Debug()<<"Populating skills: " << _list.size();
				for(auto&& s : _list) {
					ss.push_back(PersonSkill(s));
				}
				return ss;
			}
		};

        typedef Loki::SingletonHolder<SkillManagerImpl> SkillManager;
        typedef Loki::SingletonHolder<WishManagerImpl> WishManager;



		class Person {
		private:
			std::vector <PersonWish> _wishes;
			std::vector <PersonSkill> _skills;
			std::string _name;
		public:
			Person(std::string name):
				_name(name)
			{
				_skills = SkillManager::Instance().populateSkills();
				_wishes = WishManager::Instance().populateWishes();
			};

			~Person(){
			}

			void LogPerson(){
				std::stringstream ss;

				auto log = MTLog::Instance();
				ss 	<< endl << "Perosn: " << _name << endl
					<< "Wishes:" << endl;

				for(auto&& w : _wishes) {
					auto info = w.getInfo();
					ss << "\t" << info->getName() << " : " << w.getLvl() << endl;
				}

				ss << endl << "Skills:" << endl;
				for(auto&& a : _skills) {
					auto info = a.getInfo();
					ss 	<< "* "<< info->getName() << " (" << a.getSuccessCount()<< ":" << a.getLvl() << ")" << endl
						<< "Affects wishes:" << endl;
					for(auto&& widx : info->getWishes()) {
						auto w = WishManager::Instance().getWish(widx);
						ss << "\t" << w->getName() << endl;
					}
				}

				log.Info() << ss.str();
			}
		};
	}
}