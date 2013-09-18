/**
 * File contains declaraion of FaceSet class.
 * @file    FaceSet.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef FACESET_HPP
#define FACESET_HPP

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		class Face;

		/**
		 * Class represents face collection
		 */
		class FaceSet
		{
		private:
			Face* m_pFaces;
			int m_nMaxSize;
			int m_nSize;
		public:
			FaceSet();
			virtual ~FaceSet();

			int GetSize();
			Face* GetFace(int i);
			void SetFace(int i, Face& vFace);
			Face* AddFace(Face& vFace);
			Face* InsertFace(int i, Face& vFace);
			void RemoveFace(int i);
			Face* get(int i) { return GetFace(i); }
			void remove(int i);
			Face& operator[](int index);
			int length();
		};
	}
}
#endif
