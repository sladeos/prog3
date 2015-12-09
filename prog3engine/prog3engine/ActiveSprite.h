#ifndef ACTIVESPRITE_H
#define ACTIVESPRITE_H

#include "Sprite.h"
#include <string>
#include <SDL.h>

namespace gengine {
	class ActiveSprite :
		public Sprite
	{
	public:
		ActiveSprite();
		~ActiveSprite();
	};
}

#endif

