/**
 * File contains definition of Frustum class.
 * @file	Frustum.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-30
 */

#include "Frustum.hpp"

using namespace AyumiEngine::AyumiMath;

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Class default constructor. Initialize empty frustum volume.
		 */
		Frustum::Frustum()
		{
			for(int i = 0; i < 6; ++i)
				for(int j = 0; j < 4; ++j)
					frustumPlanes[i][j] = 0.0f;
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		Frustum::~Frustum()
		{
			
		}

		/**
		 * Private method which is used to normalize frustum plane.
		 * @param	frustum is calculated frustum data.
		 * @param	side is frustum side.
		 */
		void Frustum::normalizePlane(float frustum[6][4], const int side)
		{
			float magnitude = static_cast<float>(sqrt( frustum[side][0] * frustum[side][0] + 
										   frustum[side][1] * frustum[side][1] + 
										   frustum[side][2] * frustum[side][2]));

			frustum[side][0] /= magnitude;
			frustum[side][1] /= magnitude;
			frustum[side][2] /= magnitude;
			frustum[side][3] /= magnitude; 
		}

		/**
		 * Method is used to calculate current camera frustum.
		 * @param	currentCamera is pointer to current scene camera.
		 */
		void Frustum::calculateFrustum(Camera* currentCamera)
		{
			Matrix4D projectionMatrix;
			Matrix4D viewMatrix;
			Matrix4D clip;

			currentCamera->setProjectionMatrix(&projectionMatrix);
			currentCamera->setViewMatrix(&viewMatrix);

			clip = transpose(projectionMatrix * viewMatrix);

			frustumPlanes[RIGHT][0] = clip[ 3] - clip[ 0];
			frustumPlanes[RIGHT][1] = clip[ 7] - clip[ 4];
			frustumPlanes[RIGHT][2] = clip[11] - clip[ 8];
			frustumPlanes[RIGHT][3] = clip[15] - clip[12];
			normalizePlane(frustumPlanes, RIGHT);

			frustumPlanes[LEFT][0] = clip[ 3] + clip[ 0];
			frustumPlanes[LEFT][1] = clip[ 7] + clip[ 4];
			frustumPlanes[LEFT][2] = clip[11] + clip[ 8];
			frustumPlanes[LEFT][3] = clip[15] + clip[12];
			normalizePlane(frustumPlanes, LEFT);

			frustumPlanes[BOTTOM][0] = clip[ 3] + clip[ 1];
			frustumPlanes[BOTTOM][1] = clip[ 7] + clip[ 5];
			frustumPlanes[BOTTOM][2] = clip[11] + clip[ 9];
			frustumPlanes[BOTTOM][3] = clip[15] + clip[13];
			normalizePlane(frustumPlanes, BOTTOM);

			frustumPlanes[TOP][0] = clip[ 3] - clip[ 1];
			frustumPlanes[TOP][1] = clip[ 7] - clip[ 5];
			frustumPlanes[TOP][2] = clip[11] - clip[ 9];
			frustumPlanes[TOP][3] = clip[15] - clip[13];
			normalizePlane(frustumPlanes, TOP);

			frustumPlanes[BACK][0] = clip[ 3] - clip[ 2];
			frustumPlanes[BACK][1] = clip[ 7] - clip[ 6];
			frustumPlanes[BACK][2] = clip[11] - clip[10];
			frustumPlanes[BACK][3] = clip[15] - clip[14];
			normalizePlane(frustumPlanes, BACK);

			frustumPlanes[FRONT][0] = clip[ 3] + clip[ 2];
			frustumPlanes[FRONT][1] = clip[ 7] + clip[ 6];
			frustumPlanes[FRONT][2] = clip[11] + clip[10];
			frustumPlanes[FRONT][3] = clip[15] + clip[14];
			normalizePlane(frustumPlanes, FRONT);
		}

		/**
		 * Method is used to check if 3D point is inside of calculated frustum.
		 * @param	x is point origin x value.
		 * @param	y is point origin y value.
		 * @param	z is point origin z value.
		 * @return	true if point is in frustum, false otherwise.
		 */
		bool Frustum::isPointInFrustum(const float x, const float y, const float z)
		{
			for(int i = 0; i < 6; ++i)
			{
				if(frustumPlanes[i][0] * x + frustumPlanes[i][1] * y + frustumPlanes[i][2] * z + frustumPlanes[i][3] <= 0)
					return false;
			}
			return true;
		}
	
		/**
		 * Method is used to check if bounding sphere is inside, partialy inside or outside of frustum.
		 * @param	x is sphere origin x valeu.
		 * @param	y is sphere origin y value.
		 * @param	z is sphere origin z value.
		 * @param	radius is spehere radius.
		 * @return	OUTSIDE enumeration when sphere is outise, PARTIALLY_INSIDE when sphere is partialy
					inside or INSIDE enumeration when sphere is in frustum.
		 */	
		FrustumTestResult Frustum::isSphereInFrustum(const float x, const float y, const float z, const float radius)
		{
			int c = 0;
			float d = 0.0f;
			
			for(int i = 0; i < 6; i++)
			{
				d = frustumPlanes[i][0] * x + frustumPlanes[i][1] * y + frustumPlanes[i][2] * z + frustumPlanes[i][3];
				if(d <= -radius)
					return OUTSIDE;
				if(d > radius)
					c++;
			}
			return (c == 6) ? INSIDE : PARTIALLY_INSIDE;
		}

		/**
		 * Method is used to check if bounding box is inside, partialy inside or outside of frustum.
		 * @param	x is box origin x valeu.
		 * @param	y is box origin y value.
		 * @param	z is box origin z value.
		 * @param	size is box size.
		 * @return	OUTSIDE enumeration when box is outise, PARTIALLY_INSIDE when box is partialy
					inside or INSIDE enumeration when box is in frustum.
		 */	
		FrustumTestResult Frustum::isCubeInFrustum(const float x, const float y, const float z, const  float size)
		{
			int c = 0;
			int c2 = 0;

			for(int i = 0; i < 6; ++i)
		    {
				c = 0;
				if(frustumPlanes[i][0] * (x - size) + frustumPlanes[i][1] * (y - size) + frustumPlanes[i][2] * (z - size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x + size) + frustumPlanes[i][1] * (y - size) + frustumPlanes[i][2] * (z - size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x - size) + frustumPlanes[i][1] * (y + size) + frustumPlanes[i][2] * (z - size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x + size) + frustumPlanes[i][1] * (y + size) + frustumPlanes[i][2] * (z - size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x - size) + frustumPlanes[i][1] * (y - size) + frustumPlanes[i][2] * (z + size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x + size) + frustumPlanes[i][1] * (y - size) + frustumPlanes[i][2] * (z + size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x - size) + frustumPlanes[i][1] * (y + size) + frustumPlanes[i][2] * (z + size) + frustumPlanes[i][3] > 0)
					c++;
				if(frustumPlanes[i][0] * (x + size) + frustumPlanes[i][1] * (y + size) + frustumPlanes[i][2] * (z + size) + frustumPlanes[i][3] > 0)
					c++;
				if(c == 0)
					return OUTSIDE;
				if(c == 8)
					c2++;
		   }
		   return (c2 == 6) ? INSIDE : PARTIALLY_INSIDE;
		}
	}
}
