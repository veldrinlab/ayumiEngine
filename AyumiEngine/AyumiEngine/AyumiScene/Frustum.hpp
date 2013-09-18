/**
 * File contains declaration of Frustum class.
 * @file	Frustum.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-30
 */

#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP

#include "Camera.hpp"
#include "..\AyumiMath\CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiScene
	{
		/**
		 * Enumeration represents frustum planes.
		 */
		enum FrustumSide
		{
			RIGHT,
			LEFT,
			BOTTOM,
			TOP,
			BACK,
			FRONT
		}; 

		/**
		 * Enumeration represents each frustum plane data.
		 */
		enum PlaneData
		{
			_A = 0,
			_B = 1,
			_C = 2,
			_D = 3
		};
		
		/**
		 * Enumeration represents frustum test results. OUTSIDE whend cube/sphere is outisde of 
		 * frustum, PARTIALLY_INSIDE when part of cube/sphere is inside of frustum and INSIDE when cube/sphere
		 * is inside of frustum. Use to traverse OctTree.
		 */
		enum FrustumTestResult
		{
			OUTSIDE = 0,
			PARTIALLY_INSIDE = 1,
			INSIDE = 2
		};

		/**
		 * Class represents frustum which is the region of space in the modeled world that may appear
		 * on the screen; it is the field of view of the notional camera. With calculated frustum and scene
		 * containted in OctTree structure engine removes objects ie completely outside the viewing frustum
		 * from the rendering process.
		 */
		class Frustum
		{
		private:
			float frustumPlanes[6][4];

			void normalizePlane(float frustum[6][4], const int side);

		public:
			Frustum();
			~Frustum();

			void calculateFrustum(Camera* currentCamera);
			bool isPointInFrustum(const float x, const float y, const float z);
			FrustumTestResult isSphereInFrustum(const float x, const float y, const float z, const float radius);
			FrustumTestResult isCubeInFrustum(const float x, const float y, const float z, const  float size);
		};
	}
}
#endif
