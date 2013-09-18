/**
 * File contains definition of Vector structure.
 * @file    Vector.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "Vector.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Method is used to calculate vector magnitude.
		 * @return	vector magnitude.
		 */
		float Vector::Magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		/**
		 * Method is used to normalize vector.
		 */
		void Vector::Normalise()
		{
			float maxValue = 0.0f;

			if(fabs(x) > maxValue) maxValue = fabs(x);
			if(fabs(y) > maxValue) maxValue = fabs(y);
			if(fabs(z) > maxValue) maxValue = fabs(z);
	
			if(maxValue == 0.0f)
				return;
	
			x = x / maxValue;
			y = y / maxValue;
			z = z / maxValue;

			float mag = Magnitude();
	
			if(mag == 0.0f)
				return;

			float invMag = 1.0f / mag;
			x *= invMag;
			y *= invMag;
			z *= invMag;
		}

		/**
		 * Method is used to get normalized vector.
		 * @return	normalized vector.
		 */
		Vector Vector::Normalised() const
		{
			Vector normalisedVector(x,y,z);
	
			float maxValue = 0.0f;
	
			if(fabs(normalisedVector.x) > maxValue) maxValue = fabs(normalisedVector.x);
			if(fabs(normalisedVector.y) > maxValue) maxValue = fabs(normalisedVector.y);
			if(fabs(normalisedVector.z) > maxValue) maxValue = fabs(normalisedVector.z);
	
			if(maxValue == 0.0f)
				return Vector(x,y,z);
		
			normalisedVector.x = normalisedVector.x / maxValue;
			normalisedVector.y = normalisedVector.y / maxValue;
			normalisedVector.z = normalisedVector.z / maxValue;
	
			float mag = normalisedVector.Magnitude();
	
			if(mag == 0.0f)
				return Vector(x,y,z);
	
			float invMag = 1.0f / mag;
			normalisedVector.x *= invMag;
			normalisedVector.y *= invMag;
			normalisedVector.z *= invMag;
	
			return normalisedVector;
		}

		/**
		 * Class addition operator.
		 * @param	v is other vector.
		 */
		Vector Vector::operator+(const Vector& v) const
		{
			return Vector(x + v.x, y + v.y, z + v.z);
		}
	
		/**
		 * Class substract operator.
		 * @param	v is other vector.
		 */
		Vector Vector::operator-(const Vector& v) const
		{
			return Vector(x - v.x, y - v.y, z - v.z);
		}
		
		/**
		 * Class addition operator.
		 * @param	v is other vector.
		 */
		void Vector::operator+=(const Vector& v)
		{
			x += v.x; y += v.y; z += v.z;
		}

		/**
		 * Class substract operator.
		 * @param	v is other vector.
		 */
		void Vector::operator-=(const Vector& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
		}

		/**
		 * Class multiply by scalar operator.
		 * @param	s is scalar.
		 */
		void Vector::operator*=(float s)
		{
			x *= s; y *= s; z *= s;
		}
		
		/**
		 * Class negation operator.
		 * @return	inverted vector.
		 */
		Vector Vector::operator-() const
		{
			return Vector(-x, -y, -z);
		}

		/**
		 * Function is used to get vector via vector multiply result.
		 * @param	a is vector.
		 * @param	b is vector.
		 * @return	result vector.
		 */
		float operator*(const Vector& a, const Vector& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		/**
		 * Function is used to get vector via scalar multiply result.
		 * @param	v is vector.
		 * @param	s is scalar.
		 * @return	result vector.
		 */
		Vector operator*(const Vector& v, float s)
		{
			return Vector(v.x * s, v.y * s, v.z * s);
		}

		/**
		 * Function is used to get scalar via vector multiply result.
		 * @param	s is scalar.
		 * @param	v is vector.
		 * @return	result vector.
		 */
		Vector operator*(float s, const Vector& v)
		{
			return Vector(v.x * s, v.y * s, v.z * s);
		}

		/**
		 * Method is used to get cross vector.
		 * @param	a is first vector.
		 * @param	b is second vector.
		 * @return	cross vector.
		 */
		Vector VectorCross(const Vector& a, const Vector& b)
		{
			return Vector(
						a.y * b.z - a.z * b.y,
						a.z * b.x - a.x * b.z,
						a.x * b.y - a.y * b.x
					);
		}

		/**
		 * Method is used to get scale vector.
		 * @param	a is first vector.
		 * @param	b is second vector.
		 * @return	scale vector.
		 */
		Vector VectorScale(const Vector& a, const Vector& b)
		{
			return Vector(
				a.x * b.x,
				a.y * b.y,
				a.z * b.z);
		}

		/**
		 * Method is used to get rotate vector.
		 * @param	p is first vector.
		 * @param	p1 is second vector.
		 * @param	theta is angle.
		 * @return	rotate vector.
		 */
		Vector VectorRotate(Vector p, const Vector& p1, const Vector& p2, float theta)
		{
			Vector q,r;
			float costheta,sintheta;

			r.x = p2.x - p1.x;
			r.y = p2.y - p1.y;
			r.z = p2.z - p1.z;
			p.x -= p1.x;
			p.y -= p1.y;
			p.z -= p1.z;
			r.Normalise();

			costheta = cos(theta);
			sintheta = sin(theta);

			q.x += (costheta + (1 - costheta) * r.x * r.x) * p.x;
			q.x += ((1 - costheta) * r.x * r.y - r.z * sintheta) * p.y;
			q.x += ((1 - costheta) * r.x * r.z + r.y * sintheta) * p.z;

			q.y += ((1 - costheta) * r.x * r.y + r.z * sintheta) * p.x;
			q.y += (costheta + (1 - costheta) * r.y * r.y) * p.y;
			q.y += ((1 - costheta) * r.y * r.z - r.x * sintheta) * p.z;

			q.z += ((1 - costheta) * r.x * r.z - r.y * sintheta) * p.x;
			q.z += ((1 - costheta) * r.y * r.z + r.x * sintheta) * p.y;
			q.z += (costheta + (1 - costheta) * r.z * r.z) * p.z;

			q.x += p1.x;
			q.y += p1.y;
			q.z += p1.z;

			return q;
		}
	}
}
