/**
 * File contains declaraion of Solid structure.
 * @file    Solid.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef SOLID_HPP
#define SOLID_HPP

#include "Vector.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		typedef std::vector<int> IntSet;

		/**
		 * Structure represents mesh solid geometry.
		 */
		struct Solid
		{
			VectorSet vertices;
			IntSet indices;

			/**
			 * Method is used to translate solid by vector.
			 * @param	t is translate vector.
			 */
			void Translate(const Vector& t)
			{
				for(unsigned i = 0; i < vertices.size(); i++)
				{
					Vector v = vertices[i];
					v = v + t;
					vertices[i] = v;
				}
			}

			/**
			 * Method is used to rotate solid by vectors and angle.
			 * @param	a is rotate vector.
			 * @param	b is rotate vector.
			 * @param	angle is rotate angle value.
			 */
			void Rotate(const Vector& a, const Vector& b, float angle)
			{
				for(unsigned i = 0; i < vertices.size(); i++)
				{
					Vector v = vertices[i];
					v = VectorRotate(v, a, b, angle);
					vertices[i] = v;
				}
			}

			/**
			 * Method is used to scale solid by vector.
			 * @param	s id scale vector.
			 */
			void Scale(const Vector& s)
			{
				for(unsigned i = 0; i < vertices.size(); i++)
				{
					Vector v = vertices[i];
					v = VectorScale(v, s);
					vertices[i] = v;
				}
			}
			
			/**
			 * Accessor to vertices.
			 * @return	pointer to vertices collection.
			 */
			VectorSet* getVertices()
			{
				VectorSet* newVertices = new VectorSet();

				for(unsigned i = 0; i < vertices.size(); i++)
					newVertices->push_back(vertices[i]);
				return newVertices;
			}

			/**
			 * Accessor to indices.
			 * @return	pointer to indices collection.
			 */
			IntSet* getIndices()
			{
				IntSet * newIndices = new IntSet();
				for(unsigned i = 0; i < indices.size(); i++)
					newIndices->push_back(indices[i]);
				return newIndices;
			}
		};
	}
}
#endif
