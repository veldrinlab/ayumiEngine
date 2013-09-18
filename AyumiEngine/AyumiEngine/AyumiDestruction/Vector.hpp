/**
 * File contains declaraion of Vector structure.
 * @file    Vector.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef VEC_HPP
#define VEC_HPP

#include <math.h>
#include <vector>
#include <stdlib.h>

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		struct Vector;
		typedef std::vector<Vector> VectorSet;

		/**
		 * Structure represents vector.
		 */
		struct Vector
		{
			float x;
			float y;
			float z;

			Vector();
			Vector(float xv, float yv, float zv);
			Vector(const Vector& v);

			void Normalise();
			Vector Normalised() const;
			float Magnitude()	const;
			Vector operator-() const;
			Vector operator-(const Vector& v) const;
			Vector operator+(const Vector& v) const;
			void operator+=(const Vector& v);
			void operator-=(const Vector& v);
			void operator*=(float s);
			bool operator==(const Vector& other) const;
			bool operator!=(const Vector& other) const;
			float&	operator[](int index);
			const float& operator[](int index) const;

		};

		/**
		 * Class default constructor.
		 */
		inline Vector::Vector() : x(0.0f), y(0.0f), z(0.0f) {}
		
		/**
		 * Class constructor with initialize parametres.
		 * @param	xv is x value.
		 * @param	yv is y value.
		 * @param	zv is z value.
		 */
		inline Vector::Vector(float xv, float yv, float zv) : x(xv), y(yv), z(zv){}

		/**
		 * Class constructor with initialize parametres.
		 * @param	v is source vector.
		 */
		inline Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z){}

		/**
		 * Class assign operator.
		 * @param	other is source vector.
		 * @return	true if equal, false otherwise.
		 */
		inline bool	Vector::operator==(const Vector& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		/**
		 * Class not assign operator.
		 * @param	other is source vector.
		 * @return	true if not equal, false otherwise.
		 */
		inline bool	Vector::operator!=(const Vector& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z);
		}

		/**
		 * Class index operator.
		 * @param	index is vector index
		 * @return	vector value.
		 */
		inline float& Vector::operator[](int index)
		{
			return reinterpret_cast<float*>(this)[index];
		}

		/**
		 * Class index operator.
		 * @param	index is vector index
		 * @return	vector value.
		 */
		inline const float&	Vector::operator[](int index) const
		{
			return reinterpret_cast<const float*>(this)[index];
		}

		float operator*(const Vector& a, const Vector& b);
		Vector operator*(const Vector &v, float s);
		Vector operator*(float s, const Vector& v);
		Vector VectorScale(const Vector& a, const Vector& b);
		Vector VectorCross(const Vector& a, const Vector& b);
		Vector VectorRotate(Vector p, const Vector& p1, const Vector& p2, float theta);
	}
}
#endif
