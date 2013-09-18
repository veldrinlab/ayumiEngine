/**
 * File contains declaraion of Object3D class.
 * @file    Object3D.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Segment.hpp"
#include "Solid.hpp"
#include "Bound.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		class Vertex;
		class Face;
		class VertexSet;
		class FaceSet;

		/**
		 * Class represents 3d object.
		 */
		class Object3D
		{
		public:
			VertexSet* vertices;
			FaceSet* faces;
			Bound* bound;
	
			Object3D();
			Object3D(Solid * solid);
			virtual ~Object3D();
	
			int getNumFaces();
			Face* getFace(int index);
			Bound& getBound();

			static float TOL;

			Face* addFace(Vertex* v1, Vertex* v2, Vertex* v3);
			Vertex* addVertex(const Vector& pos, int status);

			void splitFaces(Object3D* pObject);
			float computeDistance(Vertex& vertex, Face& face);
			void splitFace(int facePos, Segment& segment1, Segment& segment2);
			void breakFaceInTwo(int facePos, const Vector& newPos, int splitEdge);
			void breakFaceInTwo(int facePos, const Vector& newPos, Vertex& endVertex);
			void breakFaceInThree(int facePos, const Vector& newPos1, const Vector& newPos2, Vertex& startVertex, Vertex& endVertex);
			void breakFaceInThree(int facePos, const Vector& newPos1, const Vector& newPos2, int splitEdge);
			void breakFaceInThree(int facePos, const Vector& newPos, Vertex& endVertex);
			void breakFaceInThree(int facePos, const Vector& newPos);
			void breakFaceInFour(int facePos, const Vector& newPos1, const Vector& newPos2, Vertex& endVertex);
			void breakFaceInFive(int facePos, const Vector& newPos1, const Vector& newPos2, int linedVertex);
			void classifyFaces(Object3D& pObject);
			void invertInsideFaces();
		};
	}
}
#endif 
