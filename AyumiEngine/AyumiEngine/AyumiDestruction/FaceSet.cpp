/**
 * File contains definition of FaceSet class.
 * @file    FaceSet.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "FaceSet.hpp"
#include "Face.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Class default constructor.
		 */
		FaceSet::FaceSet()
		{
			m_nMaxSize = 20000;
			m_nSize = 0;
			m_pFaces = new Face[m_nMaxSize];
		}

		/**
		 * Class destructor, free allocated memory.
		 */
		FaceSet::~FaceSet()
		{
			delete [] m_pFaces;
		}

		/**
		 * Accessor to face collection size.
		 * @return	face collection size.
		 */
		int FaceSet::GetSize()
		{
			return m_nSize;
		}

		/**
		 * Accessor to face collection size.
		 * @return	face collection size.
		 */
		int FaceSet::length()
		{
			return m_nSize;
		}

		/**
		 * Method is used to get face.
		 * @param	i is face index.
		 * @return	pointer to indexed face.
		 */
		Face* FaceSet::GetFace(int i)
		{
			if(i < 0) return 0;
			if(i >= m_nSize) return 0;

			return &m_pFaces[i];
		}

		/**
		 * Method is used to set face.
		 * @param	i is face index.
		 * @param	vFace is new face.
		 * @return	pointer to new face,
		 */
		void FaceSet::SetFace(int i, Face & vFace)
		{
			if(i < 0) return;
			if(i >= m_nSize) return;
			m_pFaces[i] = vFace;
		}

		/**
		 * Method is used to add face.
		 * @param	vFace is new face.
		 * @return	pointer to new face,
		 */
		Face* FaceSet::AddFace(Face& vFace)
		{
			if(m_nSize >= m_nMaxSize)
				return 0;
			m_pFaces[m_nSize] = vFace;
			m_nSize++;

			return &m_pFaces[m_nSize - 1];
		}

		/**
		 * Clas index operator.
		 * @param	index is face index.
		 * @return	face from defined index.
		 */
		Face& FaceSet::operator[](int index)
		{
			Face* pFace = GetFace(index);
			return *pFace;
		}

		/**
		 * Method is used to insert face.
		 * @param	i is face index.
		 * @param	vFace is new face.
		 * @return	pointer to new face,
		 */
		Face* FaceSet::InsertFace(int i, Face& vFace)
		{
			if(m_nSize >= m_nMaxSize)
				return 0;
		
			for(int j = m_nSize; j >= i+1; j--)
				m_pFaces[j] = m_pFaces[j-1];
		
			m_pFaces[i] = vFace;
			m_nSize++;

			return &m_pFaces[i];
		}

		/**
		 * Method is used to remove face.
		 * @param	i is face index.
		 */
		void FaceSet::RemoveFace(int i)
		{
			if(m_nSize <= 0)
				return;
			
			for(int j = i; j < m_nSize-1; j++)
				m_pFaces[j] = m_pFaces[j+1];
			m_nSize--;
		}

		/**
		 * Method is used to remove face.
		 * @param	i is face index.
		 */
		void FaceSet::remove(int i)
		{
			RemoveFace(i);
		}
	}
}