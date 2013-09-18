/**
 * File contains declaraion of VertexBufferObject class.
 * @file    VertexBufferObject.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-05
 */

#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include <GL/glew.h>
#include "../AyumiResource/Mesh.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents OpenGL Vertex Buffer Object which is used to store
		 * vertex data and send them to GPU to achive maximum efficiently communication.
		 * Vertex Buffer is used to store geometry triagnle data with indices.
		 */
		class VertexBufferObject
		{
		private:
			GLuint vertexBuffer;
			GLuint indicesBuffer;
			
		public:
			GLuint vertexPosition;
			GLuint normalPosition;
			GLuint texCoordPosition;
			GLuint tangentPosition;

			VertexBufferObject();
			VertexBufferObject(const AyumiResource::Mesh& entityMesh);
			VertexBufferObject(const VertexBufferObject& vertexBuffer);
			~VertexBufferObject();

			void initializeBufferObject(const AyumiResource::Mesh& entityMesh);
			void bindBufferObject();
			void unbindBufferObject();
		};
	}
}
#endif
