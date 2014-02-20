#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Utilities.h"
#include "Quad.h"
#include <SOIL.h>


class Sprite: public Quad
{
public:
	Sprite(void);
	~Sprite(void);
	Sprite( const char* a_pTexture, int a_iWidth, int a_iHeight, Vector4 a_v4Color,GLFWwindow* );
	void SetUVData();	
	virtual void Draw();
	void Input();


	void SetVertexData( Vertex* a_vertexData );
	const Vertex* GetVertexData() const;


protected:

	Vector2 m_v2Scale;
	Vector3 m_v3Position;
	Vector4 m_v4SpriteColor;

	Vector2 m_minUVCoords;
	Vector2 m_maxUVCoords;
	Vector2 m_uvScale;
	float m_fZoom;

	Vertex m_aoVerts[4];

	Matrix4* modelMatrix;
	Matrix4* viewMatrix;

	unsigned int m_uiTexture;
	GLFWwindow * GameWindow;
	//used later
	unsigned int	m_uSourceBlendMode;
	unsigned int	m_uDestinationBlendMode;
	int tex_location;
	int matrix_location;
	int proj_location;
	int view_location;




};



inline void	Sprite::SetVertexData( Vertex* a_vertexData )
{
	memcpy( &m_aoVerts, a_vertexData, sizeof(Vertex) * 4 );
}

inline const Vertex* Sprite::GetVertexData() const
{
	return static_cast<const Vertex*>( m_aoVerts );
}


#endif
