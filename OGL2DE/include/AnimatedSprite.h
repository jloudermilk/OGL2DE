#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include <Sprite.h>
#include <string>
#include <tinyxml2.h>

struct AniSprite
{
	union{
		struct{
			std::string sName;
			Vector2 v2Size;
			Vector4 v4Location;
		};
		struct
		{
			std::string Name;
			float width, height;
			float x1,x2,y1,y2;
		};
	};
};
struct Atlas
{
	Vector2 v2Size;
	std::string sLocation;
};
class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(void);
	~AnimatedSprite(void);
	AnimatedSprite( const char* a_pSpriteSheet, GLFWwindow * window);

	void LoadSprites(const char* a_pSpriteSheet);

	std::map<std::string,AniSprite> mFrames;
	Atlas atlas;

};


#endif
