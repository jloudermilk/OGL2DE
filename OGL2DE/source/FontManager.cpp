#include "FontManager.h"


FontManager::FontManager(void)
{
}


FontManager::~FontManager(void)
{
}

void FontManager::LoadFont(const char * a_pFontSheet)
{
	
	/*
	XML structure
	- Element "TextureAtlas"	the root element
	- - Attribute "imagePath"	attribute of TextureAtlas Element
	- - Attribute "width"		attribute of TextureAtlas Element
	- - Attribute "height"		attribute of TextureAtlas Element


	- -	Element "char"			child of TextureAtlas Element
	- - - Attribute "name"		attribute of char Element
	- - - Attribute "x"			attribute of char Element
	- - - Attribute "y"			attribute of char Element
	- - - Attribute "width"		attribute of char Element
	- - - Attribute "height"	attribute of char Element
	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	char ch;
	doc.LoadFile(a_pFontSheet); // load the document
	rootNode = doc.FirstChildElement("TextureAtlas");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->ToElement();
	FontAtlas.sSheet = childElement->Attribute("imagePath");
	FontAtlas.v2Size.m_fX = (float)childElement->IntAttribute("width"); 
	FontAtlas.v2Size.m_fY = (float)childElement->IntAttribute("height");
	
	

	for (childElement = currentNode->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		if(str.length() > 1)
		{
		
			if(str == "&amp")
			ch = '&';
			
			else if(str =="&apos")
				ch = '\'';
			
			else if(str ==	"&astr")
				ch = '*';
			
			else if(str ==	"&bar" )
				ch = '|';
			
			else if(str ==	"&bslsh")
				ch = '\\';
			
			else if(str ==	"&col" )
				ch = ':';
			
			else if(str ==	"&fslsh")
				ch = '/';
			
			else if(str ==	"&gt" )
				ch = '>';
			
			else if(str ==	"&lt" )
				ch = '<';
			
			else if(str ==	"&quest") 
				ch = '?';
			
			else if(str ==	"&quot" )
				ch = '\"';
			
			else if(str ==	"&under")
				ch = '_';


		}
		else{
			ch = str.at(0);
		}
		charMap[ch].Name = str;
		charMap[ch].x0 = childElement->IntAttribute("x");
		charMap[ch].y0 = childElement->IntAttribute("y");
		charMap[ch].width = childElement->IntAttribute("width");
		charMap[ch].height =childElement->IntAttribute("height");
		charMap[ch].x1 = charMap[ch].x0 + charMap[ch].width;	
		charMap[ch].y1 = charMap[ch].y0 + charMap[ch].height;
		}
	
std:printf("done");
}
void FontManager::DrawString(std::string str,Vector2 pos,float scale)
{

}