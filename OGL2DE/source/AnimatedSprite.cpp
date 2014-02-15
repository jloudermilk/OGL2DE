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
	- Element "atlas"		the root element
							FirstChildElement of the document
	- - Element "width"		child of atlas Element
							FirstChildElement of atlas
	- - - Num				child of width Element
	- - Element "height"	child of atlas Element
	- - - Num				child of height Element
	- - Element "location"	child of atlas Element
	- - - Text				child of location Element location of the image
	- -	Element "sprite"	child of atlas Element
	- - - Element "name"	child of sprite Element
	- - - - Text			child of name Element
	- - - Element "size"	child of sprite Element
	- - - - Element "x"		child of size Element
	- - - - - Num			child of x Element
	- - - - Element "y"		child of size Element
	- - - - - Num			child of y Element
	- - - Element "x1"		child of sprite Element
	- - - - Num				child of x1 Element
	- - - Element "x2"		child of sprite Element
	- - - - Num				child of x2 Element
	- - - Element "y1"		child of sprite Element
	- - - - Num				child of y1 Element
	- - - Element "y2"		child of sprite Element
	- - - - Num				child of y2 Element

	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_pSpriteSheet); // load the document
	rootNode = doc.FirstChildElement("atlas");// set the root node
	currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->ToElement();
	str = childElement->GetText();
	atlas.v2Size.m_fX = (int)str.c_str(); // this is ugly and its my xml fault

	currentNode = currentNode->NextSibling();
	childElement = currentNode->ToElement();
	str = childElement->GetText();
	atlas.v2Size.m_fY = (int)str.c_str();
	currentNode = currentNode->NextSibling();
	childElement = currentNode->ToElement();
	str = childElement->GetText();
	atlas.sLocation = str.c_str();


	//atlas.sLocation = doc.FirstChildElement("atlas")->


}