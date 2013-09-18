/**
 * File contains declaraion of Segment class.
 * @file    Segment.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Line.hpp"
#include "Face.hpp"
#include "Vertex.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Class represents mesh segment.
		 */
		class Segment
		{
		private:
			bool setVertex(Vertex* vertex);
			bool setEdge(Vertex* vertex1, Vertex* vertex2);
			void swapEnds();
		public:
			Segment();
			Segment(Line& line, Face& face, int sign1, int sign2, int sign3);

			/** line resulting from the two planes intersection */
			Line line;
			/** shows how many ends were already defined */
			int index;
	
			/** distance from the segment starting point to the point defining the plane */
			float startDist;
			/** distance from the segment ending point to the point defining the plane */
			float endDist;
	
			/** starting point status relative to the face */
			int startType;
			/** intermediate status relative to the face */
			int middleType;
			/** ending point status relative to the face */
			int endType;
	
			/** nearest vertex from the starting point */
			Vertex* startVertex;
			/** nearest vertex from the ending point */
			Vertex* endVertex; 
	
			/** start of the intersection point */
			Vector startPos;
			/** end of the intersection point */
			Vector endPos;

			/** define as vertex one of the segment ends */
			/** define as face one of the segment ends */
			/** define as edge one of the segment ends */
			static int VERTEX;
			static int FACE;
			static int EDGE;
	
			/** tolerance value to test equalities */
			static float TOL;// = 1e-10f;
	
			Vertex* getStartVertex();
			Vertex* getEndVertex();
			float getStartDistance();
			float getEndDistance();
			int getStartType();
			int getIntermediateType();
			int getEndType();
			int getNumEndsSet();
			Vector getStartPosition();
			Vector getEndPosition();
			bool intersect(const Segment& segment);
		};
	}
}

#endif
