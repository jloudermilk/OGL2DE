#include "Quad.h"


Quad::Quad(void)
{

	
	//Default Shaders for Default constructor
	m_fZoom = 1;
	const char * VertexShader =	// Vertex Shaders deal with objects in 3D space
		"#version 330\n"
		"in vec3 position;"
		"in vec4 color;"
		"in vec2 texcoord;"
		"out vec4 vColor;"
		"out vec2 UV;"
		"void main() {"
		"	vColor = color;"
		"	UV = texcoord;"
		"	gl_Position = vec4 (position, 1.0);"
		"}";

	const char * FragmentShader =	// Fragment Shaders dela with pixel data
		"#version 330\n"
		"in vec4 vColor;"
		"in vec2 UV;"
		"out vec4 outColour;"
		"void main () {"
		"	outColour = vColor;"
		"}";
	// Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	// Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	// Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);


	m_aoVerts[0].Pos = Vector3(	-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = Vector3(	0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = Vector3(	-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = Vector3(	0.5f,  -0.5f,  0.0f);
	

	SetColor( 
		Vector4(1.0f,  0.0f,  0.0f, 1.0f),
		Vector4(0.0f,  1.0f,  0.0f, 1.0f), 
		Vector4(0.0f,  0.0f,  1.0f, 1.0f), 
		Vector4(1.0f,  1.0f,  1.0f, 1.0f));

	
	m_aoVerts[0].UV = Vector2(0.0f,  0.0f);
	m_aoVerts[1].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);

	GLuint elements[] =
	{
		0,1,2,3
	};
	//Gen Buffers
	glGenBuffers(1,&m_VBO);
	glGenBuffers(1,&m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//Bind Buffers
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//Enable some attributes
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram,"position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram,"color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);


	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	glBindVertexArray(0);


	modelMatrix = new Matrix4();
	viewMatrix = new Matrix4();
	MVP = new Matrix4();

	*modelMatrix = Matrix4::IdentityMatrix();
	*viewMatrix = Matrix4::IdentityMatrix();
	*MVP = Matrix4::IdentityMatrix();
	
	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");

}


Quad::~Quad(void)
{
		delete modelMatrix;
		delete viewMatrix;
		delete MVP;
}

void Quad::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_location, 0); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	

}
bool Quad::LoadVertShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * VertexShader = vs.c_str();
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	
	return printShaderInfoLog(m_VertexShader);
}
bool Quad::LoadFragShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * FragmentShader = vs.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	
	return printShaderInfoLog(m_FragmentShader);

}
bool Quad::LinkShaders()
{
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);
	
	return printProgramInfoLog(m_ShaderProgram);
}
void Quad::LoadTexture(const char* a_pTexture)
{
	
	m_uiTexture = 0;

	m_uSourceBlendMode	= GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	tex_location = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");

	m_minUVCoords = Vector2( 0.f, 0.f );
	m_maxUVCoords = Vector2( 1.f, 1.f );
	m_uvScale = Vector2( 1.f, 1.f );
	m_fZoom = 1.f;
}
void	Quad::SetUVData()
{
	m_aoVerts[0].UV = Vector2(m_minUVCoords.m_fX/m_uvScale.m_fX,m_minUVCoords.m_fY/m_uvScale.m_fY);
	m_aoVerts[1].UV = Vector2(m_minUVCoords.m_fX/m_uvScale.m_fX,m_maxUVCoords.m_fY/m_uvScale.m_fY);
	m_aoVerts[2].UV = Vector2(m_maxUVCoords.m_fX/m_uvScale.m_fX,m_minUVCoords.m_fY/m_uvScale.m_fY);
	m_aoVerts[3].UV = Vector2(m_maxUVCoords.m_fX/m_uvScale.m_fX,m_maxUVCoords.m_fY/m_uvScale.m_fY);

}
void Quad::SetColor()
{
	m_aoVerts[0].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[1].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[2].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[3].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);


}
void Quad::SetColor(Vector4 a_v4Color)
{
	m_aoVerts[0].Color = a_v4Color;
	m_aoVerts[1].Color = a_v4Color;
	m_aoVerts[2].Color = a_v4Color;
	m_aoVerts[3].Color = a_v4Color;

}
void Quad::SetColor(Vector4 a_v4Color0,Vector4 a_v4Color1,Vector4 a_v4Color2,Vector4 a_v4Color3)
{
	m_aoVerts[0].Color = a_v4Color0;
	m_aoVerts[1].Color = a_v4Color1;
	m_aoVerts[2].Color = a_v4Color2;
	m_aoVerts[3].Color = a_v4Color3;
}