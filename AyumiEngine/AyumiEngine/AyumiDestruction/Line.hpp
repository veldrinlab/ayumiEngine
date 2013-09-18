/**
 * File contains declaraion of Line class.
 * @file    Line.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef LINE_HPP
#define LINE_HPP

#include "Vector.hpp"
#include "Face.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Class represents line.
		 */
		class Line
		{
		public:
			Vector point;
			Vector direction;
			static float TOL;

			Line();
			Line(Face* face1, Face* face2);
			Line(const Vector& direction, const Vector& point);

			Vector getPoint();
			Vector getDirection();
			void setPoint(const Vector& point);
			void setDirection(const Vector& direction);
			float computePointToPointDistance(const Vector& otherPoint);
			Vector computeLineIntersection(Line* otherLine);
			Vector computePlaneIntersection(const Vector& normal, const Vector& planePoint, bool& bResult);
			void perturbDirection();
		};
	}
}
#endif
