#pragma once
#include "stdafx.h"

namespace Zen{
	namespace AI{

		/**
		 * @brief Предмет
		 */
		class Item : public HasId, public HasName{
		public:
			Item(IdType id, std::string name) 
				: HasId(id)
				, HasName(name)
			{};
		};
	}
}