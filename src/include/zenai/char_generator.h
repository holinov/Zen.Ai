#pragma once
#include "stdafx.h"

namespace Zen
{
    namespace AI
    {
    	class Character;

    	class CharGenerator {
    	public:
    		CharGenerator() = default;
    		Character *generate();
    	};
    }
}