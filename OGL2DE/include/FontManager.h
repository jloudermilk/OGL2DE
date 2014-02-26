#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_
#include <Utilities.h>
#include <tinyxml2.h>
#include <Sprite.h>

struct Char
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

struct Font
{
	Vector2 v2Size;
	std::string sSheet;
};
class FontManager
{
public:
	FontManager(void);
	~FontManager(void);
	void LoadFont(const char * a_pFontSheet);
	void DrawString(std::string str,Vector2 pos,float scale);

	Sprite instancedSprite;
	Font FontAtlas;
	std::map<char,Char> charMap;
	std::vector<Char> DrawList;

};

#endif // _FONT_MANAGER_H_