/**
 * File contains declaraion of Face class.
 * @file    Face.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef FACE_HPP
#define FACE_HPP

#include "Vertex.hpp"
#include "Bound.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		class Object3D;

		/**
		 * Class represents face.
		 */
		class Face
		{
		public:
			Face();
			Face(Vertex* v1, Vertex* v2, Vertex* v3);
			virtual ~Face();

			void CloneFrom(Face* pFace);
			bool equals_pointersmatch(Face* pFace);
			bool equals(Face* pOtherObject);
	
			Bound getBound();
			Vector getNormal();
			float getArea();
			void invert();
			bool simpleClassify();
			void rayTraceClassify(Object3D& object);
			bool hasPoint(const Vector& point);

			Vertex* v1;
			Vertex* v2;
			Vertex* v3;

			static int UNKNOWN;
			static int INSIDE;
			static int OUTSIDE;
			static int SAME;
			static int OPPOSITE;

			static int UP;
			static int DOWN;
			static int ON;
			static int NONE;

			int status;
			static float TOL;
			int getStatus();
			int linePositionInX(const Vector& point, const Vector& pointLine1, const Vector& pointLine2);
			int linePositionInY(const Vector& point, const Vector& pointLine1, const Vector& pointLine2);
			int linePositionInZ(const Vector& point, const Vector& pointLine1, const Vector& pointLine2);
		};
	}
}
#endif
