#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void)
{
}


AnimatedSprite::~AnimatedSprite(void)
{
}
AnimatedSprite::AnimatedSprite( const char* a_pSpriteSheet, GLFWwindow * window) 
{
	elapsedTime = 0;
	LoadSprites(a_pSpriteSheet);
	LoadAnimations(atlas.sAnimations.c_str());
	this->Sprite::Sprite(atlas.sSheet.c_str(),mSprites["idle"].width,mSprites["idle"].height,Vector4(1,1,1,1),window);

	/*This doesnt work for some reason
	m_minUVCoords = Vector2(mSprites["idle"].x0,mSprites["idle"].y0);
	m_maxUVCoords = Vector2(mSprites["idle"].x1,mSprites["idle"].y1);
	m_uvScale = Vector2(atlas.v2Size.m_fX,atlas.v2Size.m_fY);
	*/
	m_minUVCoords.m_fX = mSprites["idle"].y0;
	m_minUVCoords.m_fY = mSprites["idle"].x0;
	m_maxUVCoords.m_fX = mSprites["idle"].y1;
	m_maxUVCoords.m_fY = mSprites["idle"].x1;
	m_uvScale.m_fX = atlas.v2Size.m_fY;
	m_uvScale.m_fY	= atlas.v2Size.m_fX;


	SetUVData();


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
		mSprites[str].Name = str;
		mSprites[str].x0 = childElement->IntAttribute("x0");
		mSprites[str].x1 = childElement->IntAttribute("x1");
		mSprites[str].y0 = childElement->IntAttribute("y0");
		mSprites[str].y1 = childElement->IntAttribute("y1");
		mSprites[str].height = mSprites[str].y1 - mSprites[str].y0;
		mSprites[str].width = mSprites[str].x1 - mSprites[str].x0;
	}
std:printf("done");


}
void AnimatedSprite::LoadAnimations(const char* a_pAnimationSheet)
{
	/*
	XML structure
	<animation name = "teleport" fps = "30">
	<frame>tpod 0</frame>
	- Element "animation"		a root element
	- - Attribute "name"		attribute of animation Element
	- - Attribute "fps"			attribute of animation Element

	- -	Element "frame"		child of animation Element
	- - - Attribute "name"		attribute of frame Element
	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str,aniName;
	doc.LoadFile(a_pAnimationSheet); // load the document
	rootNode = doc.FirstChildElement("animation");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child

	for (childElement = currentNode->ToElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		aniName = childElement->Attribute("name");
		int i = 0;
		for (child = childElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{

			str = child->Attribute("name");
			mAnimations[aniName].push_back(str);
			i++;
		}
	}
std:printf("done");

}

void AnimatedSprite::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_location, 0); 


	modelMatrix->m_afArray[0]  = m_v2Scale.m_fX;
	modelMatrix->m_afArray[5]  = m_v2Scale.m_fY;
	modelMatrix->m_afArray[12] = m_v3Position.m_fX;
	modelMatrix->m_afArray[13] = m_v3Position.m_fY;
	modelMatrix->m_afArray[14] = m_v3Position.m_fZ;


	Matrix4 MVP =  (*Ortho * *modelMatrix) ;


	//	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, modelMatrix->m_afArray);
	//	glUniformMatrix4fv (view_location, 1, GL_FALSE, viewMatrix->m_afArray);
	//	glUniformMatrix4fv (proj_location, 1, GL_FALSE, Ortho->m_afArray);

	
	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, MVP.m_afArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts,GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);


	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	
}

void AnimatedSprite::SetAnimation(std::string animation,PlayType type)
{
	switch (type){
	case ONCE:
		break;
	case LOOP:
		break;
	case LOOPSECTION:
		break;
	case PINGPONG:
		break;
	case REVERSE:
		break;
	case RANDOMLOOP:
		break;
	case RANDOM:
		break;
	case SINGLE:
		break;
	default
		break;
	}

}
void AnimatedSprite::SetAnimation(std::string animation,PlayType type, std::string loopFrame)
{

}
void AnimatedSprite::PlayAnimation()
{

}

void AnimatedSprite::Update()
{

	this->AnimatedSprite::Draw();
	Input();

}