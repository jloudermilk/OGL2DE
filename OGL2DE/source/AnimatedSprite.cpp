#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void)
{
}


AnimatedSprite::~AnimatedSprite(void)
{
}
AnimatedSprite::AnimatedSprite( const char* a_pSpriteSheet, GLFWwindow * window)
{

	LoadSprites(a_pSpriteSheet);

}

void AnimatedSprite::LoadSprites(const char* a_pSpriteSheet)
{
	/*
	XML structure
	- Element "atlas"			the root element
	- - Attribute "width"		attribute of atlas Element
	- - Attribute "height"		attribute of atlas Element
	- - Attribute "sheet"		attribute of atlas Element
	- - Attribute "animations"	attribute of atlas Element
	
	- -	Element "sprite"		child of atlas Element
	- - - Attribute "name"		attribute of sprite Element
	- - - Attribute "x0"		attribute of sprite Element
	- - - Attribute "x1"		attribute of sprite Element
	- - - Attribute "y0"		attribute of sprite Element
	- - - Attribute "y1"		attribute of sprite Element
	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_pSpriteSheet); // load the document
	rootNode = doc.FirstChildElement("atlas");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->ToElement();
	atlas.v2Size.m_fX = childElement->IntAttribute("width"); 
	atlas.v2Size.m_fY = childElement->IntAttribute("height");
	atlas.sSheet = childElement->Attribute("sheet");
	atlas.sAnimations = childElement->Attribute("animations");


	for (childElement = currentNode->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
	str = childElement->Attribute("name");
	mFrames[str].Name = str;
	mFrames[str].x0 = childElement->IntAttribute("x0");
	mFrames[str].x1 = childElement->IntAttribute("x1");
	mFrames[str].y0 = childElement->IntAttribute("y0");
	mFrames[str].y1 = childElement->IntAttribute("y1");
	mFrames[str].height = mFrames[str].y1 - mFrames[str].y0;
	mFrames[str].width = mFrames[str].x1 - mFrames[str].x0;
	}
	std:printf("done");


}