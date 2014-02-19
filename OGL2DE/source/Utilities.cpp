#include <Utilities.h>

Matrix4  * Ortho;
int g_gl_width = 1024;
int g_gl_height = 720;
double deltaTime = 0;


	void ViewLookAt( Vector4& vCameraPos,  Vector4& vTargetPos,  Vector4& up_direction,Matrix4 * mat)
	{
		Vector4 vForward = vTargetPos-vCameraPos;
		vForward.Normalise();
		
		Vector4 vRight =vForward.CrossProduct(up_direction);
		vRight.Normalise();

		Vector4 vUp = vForward.CrossProduct(vRight);
		
		mat->m_afArray[0] = vRight.m_fX; 
		mat->m_afArray[4] = vRight.m_fY; 
		mat->m_afArray[8] = vRight.m_fZ; 
		mat->m_afArray[12] = -(vRight.DotProduct(vCameraPos));   

		mat->m_afArray[1] = vUp.m_fX;
		mat->m_afArray[5] = vUp.m_fY;
		mat->m_afArray[9] = vUp.m_fZ;
		mat->m_afArray[13] = -(vUp.DotProduct(vCameraPos));  

		mat->m_afArray[2] = vForward.m_fX; 
		mat->m_afArray[6] = vForward.m_fY; 
		mat->m_afArray[10] = vForward.m_fZ; 
		mat->m_afArray[14] = -(vForward.DotProduct(vCameraPos));   

		mat->m_afArray[3] = 0.0f;
		mat->m_afArray[7] = 0.0f;
		mat->m_afArray[11] = 0.0f;
		mat->m_afArray[15] = 1.0f;
	}
	
	void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar,Matrix4 * mat)
	{
		float       deltaX = a_fRight - a_fLeft;
		float       deltaY = a_fTop - a_fBottom;
		float       deltaZ = a_fNear - a_fFar;

		mat->m_afArray[0] = 2.f / deltaX;
		mat->m_afArray[1] = 0.f;
		mat->m_afArray[2] = 0.f;
		mat->m_afArray[3] = 0.f;

		mat->m_afArray[4] = 0.f;
		mat->m_afArray[5] = 2.f / deltaY;
		mat->m_afArray[6] = 0.f;
		mat->m_afArray[7] = 0.f;

		mat->m_afArray[8] = 0.f;
		mat->m_afArray[9] = 0.f;
		mat->m_afArray[10] = 2.f / deltaZ;
		mat->m_afArray[11] = 0.f;

		mat->m_afArray[12] = ((a_fLeft + a_fRight )/(a_fLeft  - a_fRight));
		mat->m_afArray[13] = ((a_fBottom + a_fTop )/(a_fBottom - a_fTop));
		mat->m_afArray[14] = (-(a_fNear + a_fFar)/(a_fFar - a_fNear));
		mat->m_afArray[15] = 1.f;
	}

	void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar,Matrix4 * mat)
	{
		mat->m_afArray[0] = 2 / a_fWidth;
		mat->m_afArray[1] = 0;
		mat->m_afArray[2] = 0;
		mat->m_afArray[3] = 0;

		mat->m_afArray[4] = 0;
		mat->m_afArray[5] = 2 / a_fHeight;
		mat->m_afArray[6] = 0;
		mat->m_afArray[7] = 0;

		mat->m_afArray[8] = 0;
		mat->m_afArray[9] = 0;
		mat->m_afArray[10] = 1 / (a_fFar - a_fNear);
		mat->m_afArray[11] = 0;

		mat->m_afArray[12] = 0;
		mat->m_afArray[13] = 0;
		mat->m_afArray[14] = a_fNear / (a_fNear - a_fFar);
		mat->m_afArray[15] = 1;
	}

	void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar,Matrix4 *mat)
	{
		float halfAngleRadians = 0.5f * a_fUpFOV;
		float cot = 1 / tanf(halfAngleRadians);

		mat->m_afArray[0] = cot / a_fAspectRatio;
		mat->m_afArray[1] = 0;
		mat->m_afArray[2] = 0;
		mat->m_afArray[3] = 0;

		mat->m_afArray[4] = 0;
		mat->m_afArray[5] = cot;
		mat->m_afArray[6] = 0;
		mat->m_afArray[7] = 0;

		mat->m_afArray[8] = 0;
		mat->m_afArray[9] = 0;
		mat->m_afArray[10] = a_fFar / (a_fFar - a_fNear);
		mat->m_afArray[11] = 1;

		mat->m_afArray[12] = 0;
		mat->m_afArray[13] = 0;
		mat->m_afArray[14] = a_fNear * a_fFar / (a_fNear - a_fFar);
		mat->m_afArray[15] = 0;
	}

	double getDeltaTime()
	{
		return deltaTime;
	}
	void resetDeltaTime()
	{
		deltaTime =  glfwGetTime();
		glfwSetTime(0);
		
	}

