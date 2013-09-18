/**
 * File contains definition of VertexSet class.
 * @file    VertexSet.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "Vertex.hpp"
#include "VertexSet.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Method is used to get vertex pointer.
		 * @param	nIndex is index to vertex.
		 * @param	return pointer to vertex.
		 */
		Vertex* VertexPointerSet::GetVertexPtr(int nIndex)
		{
			if(nIndex < 0) return 0;
			if(static_cast<unsigned int>(nIndex) >= m_pPointers.size()) return 0;

			Vertex* pVertex = m_pPointers[nIndex];
			return pVertex;
		}

		/**
		 * Method is used to get number of vertex pointers.
		 * @return	size of vertex pointers.
		 */
		int VertexPointerSet::GetNumVertexPointers()
		{
			return m_pPointers.size();
		}

		/**
		 * Method is used to add vertex pointer.
		 * @param	pPointer is pointer to vertex.
		 */
		void VertexPointerSet::AddVertexPointer(Vertex* pPointer)
		{
			m_pPointers.push_back(pPointer);
		}

		/**
		 * Method is used to add vertex pointer.
		 * @param	pPointer is pointer to vertex.
		 */
		void VertexPointerSet::add(Vertex* pPointer)
		{
			AddVertexPointer(pPointer);
		}

		/**
		 * Class operator to get vertex pointer.
		 * @param	index is vertex index in collection.
		 * @param	return pointer to vertex.
		 */
		Vertex* VertexPointerSet::operator[](int index)
		{
			Vertex* pVertex = GetVertexPtr(index);
			return pVertex;
		}

		/**
		 * Method is used to get vertices size.
		 * @return	size of vertices collection.
		 */
		int VertexPointerSet::length()
		{
			return m_pPointers.size();
		}

		/**
		 * Class destructor, free allocated memory. Delete pointers.
		 */
		VertexSet::~VertexSet()
		{
			for(unsigned int i = 0; i < m_pVertices.size(); i++)
				delete m_pVertices[i];
		}

		/**
		 * Method is used to get vertex pointer.
		 * @param	nIndex is index to vertex.
		 * @param	return pointer to vertex.
		 */
		Vertex* VertexSet::GetVertex(int nIndex)
		{
			if(nIndex < 0) return 0;
			if(static_cast<unsigned int>(nIndex) >= m_pVertices.size()) return 0;
			Vertex * pVertex = m_pVertices[nIndex];
			return pVertex;
		}

		/**
		 * Method is used to get number of vertex pointers.
		 * @return	size of vertex pointers.
		 */
		int VertexSet::GetNumVertices()
		{
			return m_pVertices.size();
		}

		/**
		 * Method is used to add vertex.
		 * @param	vertex is vertex to add.
		 * @return	pointer to added vector.
		 */
		Vertex* VertexSet::AddVertex(const Vertex& vertex)
		{
			m_pVertices.push_back(new Vertex(vertex));
			return m_pVertices[m_pVertices.size() - 1];
		}

		/**
		 * Class operator to get vertex.
		 * @param	index is vertex index in collection.
		 * @param	return vertex.
		 */
		Vertex& VertexSet::operator[](int index)
		{
			Vertex* pVertex = GetVertex(index);
			return *pVertex;
		}

		/**
		 * Method is used to check if collection contains vector.
		 * @param	pVertex is pointer to vertex.
		 * @return	true if contains, false otherwise.
		 */
		bool VertexSet::contains(Vertex* pVertex)
		{
			for(int i = 0; i < length(); i++)
			{
				Vertex * pOurVertex = GetVertex(i);

				if(pOurVertex == pVertex)
					return true;
			}

			return false;
		}

		/**
		 * Method is used to get vertex index.
		 * @param	pVertex is pointer to vertex.
		 * @return	index if vertex is in collection, -1 otherwise.
		 */
		int VertexSet::indexOf(Vertex* pVertex)
		{
			for(int i = 0; i < length(); i++)
			{
				Vertex* pOurVertex = GetVertex(i);

				if(pOurVertex == pVertex)
					return i;
			}
			return -1;
		}

		/**
		 * Method is used to get vertices size.
		 * @return	size of vertices collection.
		 */
		int VertexSet::length()
		{
			return m_pVertices.size();
		}
	}
}