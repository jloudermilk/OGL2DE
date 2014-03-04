#include "FontManager.h"


FontManager::FontManager(void)
{


/*	iSprite.LoadVertShader("../resources/fontVert.glsl");
	iSprite.LoadFragShader("../resources/fontFrag.glsl");
	iSprite.LinkShaders();
	*/
	glGenBuffers(1,&PositionBuffer);
	glGenBuffers(1,&ColorBuffer);
	glGenBuffers(1,&UVBuffer);
	glGenBuffers(1,&MatrixBuffer);


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
	FontAtlas.fKerning = (float)childElement->IntAttribute("kerning");
	
	iSprite.LoadTexture(FontAtlas.sSheet.c_str());
	iSprite.m_uvScale = FontAtlas.v2Size;
	GLint uvAttrib = glGetAttribLocation(iSprite.m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);
	iSprite.matrix_location = glGetUniformLocation (iSprite.m_ShaderProgram, "matrix");

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
		charMap[ch].offset = childElement->IntAttribute("offset");
		}
	//need to add a space
	//these could get moved to the xml file
	ch = ' ';
	charMap[ch].Name = " ";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 8;
	charMap[ch].height =8;
	charMap[ch].x1 = 0;	
	charMap[ch].y1 = 0;
	charMap[ch].offset = 0;
	ch = '\n';
	charMap[ch].Name = "&ret";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 0;
	charMap[ch].height =0;
	charMap[ch].x1 = 0;	
	charMap[ch].y1 = 0;
	charMap[ch].offset = 0;
	
	
}
void FontManager::DrawString(std::string str,Vector2 pos,float scale)
{
	LoadString(str,pos,scale);
	glBlendFunc (iSprite.m_uSourceBlendMode, iSprite.m_uDestinationBlendMode);
	glUseProgram(iSprite.m_ShaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i (iSprite.tex_location, 0); 

	iSprite.SetScale(scale);

	Char c;

	float kerning = 0;
	float newPos = 0;
	for(int i = 0; i < DrawList.size();i++)
	{
		c = DrawList[i];
 		if(i != 0){
			if(c.Name == "&ret"){
			pos.m_fX -= 20;
			newPos = pos.m_fY;
			}
			else{
			newPos = iSprite.GetPosition().m_fX + c.width/2 + DrawList[i-1].width/2 + FontAtlas.fKerning;
			}
			iSprite.SetPosition(Vector3(newPos,pos.m_fX,0.f));
	}
		else
		iSprite.SetPosition(Vector3(pos.m_fY,pos.m_fX,0.f));

		iSprite.m_minUVCoords = Vector2(c.x0,c.y0) ;
		iSprite.m_maxUVCoords = Vector2(c.x1,c.y1) ;
		iSprite.SetScale(c.width*scale,c.height*scale);

		//Set scale of each char
	
		iSprite.SetUVData();

		iSprite.modelMatrix->m_afArray[0]  = iSprite.GetScale().m_fX *iSprite.m_fZoom;
		iSprite.modelMatrix->m_afArray[5]  = iSprite.GetScale().m_fY *iSprite.m_fZoom;
		iSprite.modelMatrix->m_afArray[12] = iSprite.GetPosition().m_fX;
		iSprite.modelMatrix->m_afArray[13] = iSprite.GetPosition().m_fY  - (c.offset *iSprite.m_fZoom); //this is going to need to change for and use the offest variable from each char
		iSprite.modelMatrix->m_afArray[14] = iSprite.GetPosition().m_fZ;


	*iSprite.MVP =  (*Ortho * *iSprite.modelMatrix) ;


	//	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, modelMatrix->m_afArray);
	//	glUniformMatrix4fv (view_location, 1, GL_FALSE, viewMatrix->m_afArray);
	//	glUniformMatrix4fv (proj_location, 1, GL_FALSE, Ortho->m_afArray);

	
	glUniformMatrix4fv (iSprite.matrix_location, 1, GL_FALSE, iSprite.MVP->m_afArray);
	iSprite.Quad::Draw();
	kerning = c.width/2 + FontAtlas.fKerning;

	}

}
void FontManager::LoadString(std::string str,Vector2 pos,float scale)
{
	DrawList.clear();
	char c;
	for(CharCount = 0; CharCount < str.length();CharCount++)
	{
		c = str.at(CharCount);
		DrawList.push_back(charMap[c]);

	}
}