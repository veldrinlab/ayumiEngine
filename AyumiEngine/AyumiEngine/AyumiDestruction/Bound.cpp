/**
 * File contains definition of Bound class.
 * @file    Bound.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "Bound.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Class constructor with intiailize parameters.
		 * @param	p1 is face triangle first vector.
		 * @param	p2 is face triangle first vector.
		 * @param	p1 is face triangle first vector.
		 */
		Bound::Bound(const Vector& p1, const Vector& p2, const Vector& p3)
		{
			xMax = xMin = p1.x;
			yMax = yMin = p1.y;
			zMax = zMin = p1.z;
			checkVertex(p2);
			checkVertex(p3);
		}

		/**
		 * Class constructor with intiailize parameters.
		 * @param	vertices is pointer to face vertices collection.
		 */
		Bound::Bound(VectorSet* vertices)
		{
			xMax = xMin = vertices->at(0).x;
			yMax = yMin = vertices->at(0).y;
			zMax = zMin = vertices->at(0).z;
	
			for(unsigned int i=1;i<vertices->size();i++)
				checkVertex(vertices->at(i));
		}

		/**
		 * Class destructor, free allocated memory. Nothing to do.
		 */
		Bound::~Bound()
		{

		}

		/**
		 * Method is used to check if one bounding volume overlap another bounding volume.
		 * @param	bound is another bounding volume.
		 * @return	true if overlap, false otherwise.
		 */
		bool Bound::overlap(Bound& bound)
		{
			return !(xMin>bound.xMax+1e-5f)||(xMax<bound.xMin-1e-5f)||(yMin>bound.yMax+1e-5f)||(yMax<bound.yMin-1e-5f)||(zMin>bound.zMax+1e-5f)||(zMax<bound.zMin-1e-5f);
		}

		/**
		 * Method is used to check if vertex is bounding volumes mix/max vertex.
		 * @param	vertex is face vertex to check.
		 */
		void Bound::checkVertex(const Vector& vertex)
		{
			if(vertex.x > xMax)
				xMax = vertex.x;
			else if(vertex.x < xMin)
				xMin = vertex.x;	
			if(vertex.y > yMax)
				yMax = vertex.y;
			else if(vertex.y < yMin)
				yMin = vertex.y;
			if(vertex.z > zMax)
				zMax = vertex.z;
			else if(vertex.z < zMin)
				zMin = vertex.z;
		}
	}
}
