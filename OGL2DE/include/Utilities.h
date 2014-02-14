#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_
#include <GL\glew.h>
#include <GLFW\glfw3.h>


//Terry's Math lib
#include <TerrehByteMath.h>
//other helper functions
#include "GLLog.h"
#include "TextFileReader.h"


#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <functional>



using namespace tbyte;

extern Matrix4 * Ortho;


// keep track of window size for things like the viewport and the mouse cursor
extern int g_gl_width;
extern int g_gl_height;



struct Vertex
{
	union
	{
		struct 
		{
			Vector3 Pos;
			Vector4 Color;
			Vector2 UV;
		};
		
		struct
		{
			float X, Y, Z;
			float R, G, B, A;
			float U, V;
		};
	};
	

	bool operator == (const Vertex& rhs)
	{
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z && U == rhs.U && V == rhs.V && R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A );
	}
};




	void ViewLookAt( Vector4& eye,  Vector4& to,  Vector4& up,Matrix4 * mat);

	void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar,Matrix4 * mat);

	void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar,Matrix4 * mat);

	void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar,Matrix4 * mat);





GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat , unsigned int* a_uiWidth , unsigned int* a_uiHeight, unsigned int* a_uiBPP  );

#endif