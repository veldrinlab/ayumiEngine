/**
 * File contains definition of Line class.
 * @file    Line.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "Line.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		float Line::TOL = 1e-5f;

		/**
		 * Class default constructor.
		 */
		Line::Line()
		{
			point = Vector(0.0,0.0,0.0);
			direction = Vector(1,0,0);
		}

		/**
		 * Class constructor with initialize parameteres.
		 * @param	face1 is first face.
		 * @param	face2 is second face.
		 */
		Line::Line(Face * face1, Face * face2)
		{
			Vector normalFace1 = face1->getNormal();
			Vector normalFace2 = face2->getNormal();
			direction = VectorCross(normalFace1, normalFace2);

			if (!(direction.Magnitude()<TOL))
			{
				float d1 = -(normalFace1.x*face1->v1->x + normalFace1.y*face1->v1->y + normalFace1.z*face1->v1->z);
				float d2 = -(normalFace2.x*face2->v1->x + normalFace2.y*face2->v1->y + normalFace2.z*face2->v1->z);
				if(fabs(direction.x)>TOL)
				{
					point.x = 0;
					point.y = (d2*normalFace1.z - d1*normalFace2.z)/direction.x;
					point.z = (d1*normalFace2.y - d2*normalFace1.y)/direction.x;
				}
				else if(fabs(direction.y)>TOL)
				{
					point.x = (d1*normalFace2.z - d2*normalFace1.z)/direction.y;
					point.y = 0;
					point.z = (d2*normalFace1.x - d1*normalFace2.x)/direction.y;
				}
				else
				{
					point.x = (d2*normalFace1.y - d1*normalFace2.y)/direction.z;
					point.y = (d1*normalFace2.x - d2*normalFace1.x)/direction.z;
					point.z = 0;
				}
			}
			direction.Normalise();
		}

		/**
		 * Class constructor with initialize parameteres.
		 * @param	directioni is line direction.
		 * @param	pointi is point of line.
		 */
		Line::Line(const Vector& directioni, const Vector& pointi)
		{
			direction = directioni;
			point = pointi;
			direction.Normalise();
		}

		/**
		 * Accessor to line point.
		 * @return	point line.
		 */
		Vector Line::getPoint()
		{
			return point;
		}

		/**
		 * Accessor to line direction.
		 * @return	direction vector.
		 */
		Vector Line::getDirection()
		{
			return direction;
		}

		/**
		 * Method is used to set line point.
		 * @param	pointi is source point.
		 */
		void Line::setPoint(const Vector& pointi)
		{
			point = pointi;
		}

		/**
		 * Method is used to set line direction.
		 * @param	directioni is source direction.
		 */
		void Line::setDirection(const Vector& directioni)
		{
			direction = directioni;
		}

		/**
		 * Method is used to compute point to point distance.
		 * @param	otherPoint is vector of other point.
		 * @return	distance between points.
		 */
		float Line::computePointToPointDistance(const Vector & otherPoint)
		{
			float distance = (point - otherPoint).Magnitude();
			Vector vec = Vector(otherPoint.x - point.x, otherPoint.y - point.y, otherPoint.z - point.z);
			vec.Normalise();
			if((vec * direction) < 0 )
				return -distance;			
			else
				return distance;
		}

		/**
		 * Method is used to compute line intersection.
		 * @param	otherLine is other line pointer.
		 * @return	intersection vector.
		 */
		Vector Line::computeLineIntersection(Line* otherLine)
		{
			//x = x1 + a1*t = x2 + b1*s
			//y = y1 + a2*t = y2 + b2*s
			//z = z1 + a3*t = z2 + b3*s
	
			Vector linePoint = otherLine->getPoint(); 
			Vector lineDirection = otherLine->getDirection();

			float t;
			if(fabs(direction.y*lineDirection.x-direction.x*lineDirection.y)>TOL)
				t = (-point.y*lineDirection.x+linePoint.y*lineDirection.x+lineDirection.y*point.x-lineDirection.y*linePoint.x)/(direction.y*lineDirection.x-direction.x*lineDirection.y);
			else if (fabs(-direction.x*lineDirection.z+direction.z*lineDirection.x)>TOL)
				t=-(-lineDirection.z*point.x+lineDirection.z*linePoint.x+lineDirection.x*point.z-lineDirection.x*linePoint.z)/(-direction.x*lineDirection.z+direction.z*lineDirection.x);
			else if (fabs(-direction.z*lineDirection.y+direction.y*lineDirection.z)>TOL)
				t = (point.z*lineDirection.y-linePoint.z*lineDirection.y-lineDirection.z*point.y+lineDirection.z*linePoint.y)/(-direction.z*lineDirection.y+direction.y*lineDirection.z);
			else
				return Vector(0.0,0.0,0.0);
	
			Vector vResult = point + direction * t;
	
			return vResult;
		}

		/**
		 * Method is used to computer plane interselection.
		 * @param	normal is normal to plane.
		 * @param	planePoint is point of plane.
		 * @param	result is test result.
		 * @return	interselection point vector.
		 */
		Vector Line::computePlaneIntersection(const Vector & normal, const Vector & planePoint, bool & bResult)
		{
			bResult = true;

			//Ax + By + Cz + D = 0
			//x = x0 + t(x1 – x0)
			//y = y0 + t(y1 – y0)
			//z = z0 + t(z1 – z0)
			//(x1 - x0) = dx, (y1 - y0) = dy, (z1 - z0) = dz
			//t = -(A*x0 + B*y0 + C*z0 )/(A*dx + B*dy + C*dz)

			//float TOL = 0.00001f;
	
			float A = normal.x;
			float B = normal.y;
			float C = normal.z;
			float D = (normal * planePoint) * -1.0f;
		
			float numerator = (normal * point) + D;
			float denominator = (normal * direction);
			
			//if line is paralel to the plane...
			if(fabs(denominator)<TOL)
			{
				//if line is contained in the plane...
				if(fabs(numerator)<TOL)
					return point;
				else
				{
					bResult = false;
					return Vector(0.0,0.0,0.0);
				}
			}
			//if line intercepts the plane...
			else
			{
				float t = -numerator/denominator;
				Vector resultPoint = point + direction * t;
		
				return resultPoint;
			}
		}

		/**
		 * Method is used to get line random number.
		 * @return	line random number.
		 */
		float LineRandomNum()
		{
			int nRand = rand() % 10000;
			float fRand = (float)nRand;
			fRand *= 0.0001f;
			fRand *= 2.0f;
			fRand -= 1.0f;
			return fRand;
		}

		/**
		 * Method is used to perturb line direction.
		 */
		void Line::perturbDirection()
		{
			direction.x += LineRandomNum() * 0.001f;			
			direction.y += LineRandomNum() * 0.001f;			
			direction.z += LineRandomNum() * 0.001f;
		}
	}
}
