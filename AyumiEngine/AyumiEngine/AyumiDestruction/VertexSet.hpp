/**
 * File contains declaraion of VertexSet class.
 * @file    VertexSet.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef VERTEXSET_HPP
#define VERTEXSET_HPP

#include <vector>

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		class Vertex;

		/**
		 * Class represents face vertex collection pointer.
		 */
		class VertexPointerSet
		{
		private:
			typedef std::vector<Vertex *> Vertices;
			Vertices m_pPointers;
		public:
			VertexPointerSet(){};
			VertexPointerSet(int nMaxSize){};
			virtual ~VertexPointerSet(){};

			Vertex* GetVertexPtr(int nIndex);
			int GetNumVertexPointers();
			void AddVertexPointer(Vertex* pPointer);
			void add(Vertex* pPointer);
			Vertex* get(int nIndex);
			int length();
			Vertex* operator[](int index);
		};

		/**
		 * Class represents face vertex collection.
		 */
		class VertexSet
		{
		private:
			typedef std::vector<Vertex *> Vertices;
			Vertices m_pVertices;
		public:
			VertexSet(){};
			VertexSet(int nMaxSize){};
			virtual ~VertexSet();
			Vertex* GetVertex(int nIndex);
			int GetNumVertices();
			Vertex* AddVertex(const Vertex& vertex);
			Vertex& operator[](int index);
			bool contains(Vertex* pVertex);
			int indexOf(Vertex* pVertex);
			int length();
		};
	}
}
#endif
