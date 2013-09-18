/**
 * File contains declaration of Mesh class.
 * @file    Mesh.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#ifndef MESH_HPP
#define MESH_HPP

#include "Resource.hpp"
#include "../AyumiUtils/Vertex.hpp"
#include "../AyumiMath/CommonMath.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class represents one of basic Engine resource - Mesh resource. Mesh is required in any
		 * kind of 2D/3D games, engines and tools. It is used to store geometry data: vertices, normals,
		 * tangents, texture uv coordinates and indices for faster rendering of triangles. Class store
		 * arrays of data, and also can calculate some necessary data like normals and tangents from
		 * vertices and indices. It is also used to calculate Bounding Volumes. Mesh resource store
		 * data in special Vertex<> structure.
		 */
		class Mesh : public Resource
		{
		private:
			AyumiUtils::Vertex<>* vertices;
			unsigned int* indices;
			int verticesAmount;
			int trianglesAmount;
			bool componentMesh;
		public:
			Mesh();
			Mesh(const Mesh& resource);
			Mesh(const char* name, const char* filePath);
			~Mesh();

			AyumiUtils::Vertex<>& operator[] (const unsigned int i);
			const AyumiUtils::Vertex<>& operator[] (const unsigned int i) const;

			void initializeVerticesArray();
			void initializeIndicesArray();
			void initializeDataArrays();
			void calculateNormals();
			void calculateTangent();

			AyumiUtils::Vertex<>* getVertices() const;
			unsigned int* getIndices() const;
			int getVerticesAmount() const;
			int getTrianglesAmount() const;
			bool isComponentMesh() const;

			void setIndex(const int arrayIndex, const unsigned int index);
			void setVerticesAmount(const int verticesAmount);
			void setTrianglesAmount(const int trianglesAmount);
			void setResourceData(const char* name, const char* filePath);
			void setAsComponentMesh();
		};
	}
}
#endif