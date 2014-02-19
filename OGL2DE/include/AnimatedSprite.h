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
			float x0,x1,y0,y1;
		};
	};
};
struct Atlas
{
	Vector2 v2Size;
	std::string sSheet;
	std::string sAnimations;
};

typedef std::vector<std::string> frame;

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(void);
	~AnimatedSprite(void);
	AnimatedSprite( const char* a_pSpriteSheet, GLFWwindow * window);
	virtual void Draw();
	void Update();
	void SetAnimation(std::string animation,PlayType type);
	void SetAnimation(std::string animation,PlayType type, int frame);
	void PlayAnimation();
	void SetSprite();
	void LoadSprites(const char* a_pSpriteSheet);
	void LoadAnimations(const char* a_pAnimationSheet);
	std::map<std::string,AniSprite> mSprites;
	std::map<std::string,frame> mAnimations;
	Atlas atlas;

	std::string currentAnimation, currentSprite;
	int currentFrame, loopFrame;
	PlayType currentPlayType;


double elapsedTime;

};


#endif
