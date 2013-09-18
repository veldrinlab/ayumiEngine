/**
 * File contains declaraion of Vertex class.
 * @file    Vertex.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef VERT_HPP
#define VERT_HPP

#include <stdio.h>

#include "Vector.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		class VertexPointerSet;

		/**
		 * Class represents face vertex.
		 */
		class Vertex
		{
		private:
			VertexPointerSet * adjacentVertices;

		public:
			float x;
			float y;
			float z;

			//jakis enum
			static int UNKNOWN;
			static int INSIDE;
			static int OUTSIDE;
			static int BOUNDARY;

			int status;

			static float TOL;

			Vertex();
			Vertex(const Vertex& otherVertex);
			Vertex(const Vector& position);
			Vertex(const Vector& position, int eStatus);
	
			Vertex(float x, float y, float z);
			Vertex(float x, float y, float z, int eStatus);

			virtual ~Vertex();
	
			bool equals(Vertex* vertex);
			void setStatus(int eStatus);
			Vector getPosition();
			int getStatus();
			void addAdjacentVertex(Vertex* adjacentVertex);
			void mark(int eStatus);

			Vertex& operator=(const Vertex& v);
		};
	}
}
#endif

