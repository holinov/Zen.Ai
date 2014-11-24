#pragma once
#include "stdafx.h"
#include "action.h"

namespace Zen{
	namespace AI{

		/**
		 * @brief Умение персонажа
		 */
		class Skill : public HasId, public HasName{
		private:

		public:
			Skill(IdType id, std::string name) 
				: HasId(id)
				, HasName(name)
			{};
		};

		struct SkillResult {
			IdType SkillId;
			std::vector<ActionResult> Results;
		};
	}
}