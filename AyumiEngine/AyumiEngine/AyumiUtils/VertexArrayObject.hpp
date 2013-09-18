/**
 * File contains declaraion of VertexArrayObject class.
 * @file    VertexArrayObject.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP

#include <GL/glew.h>

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents OpenGL Vertex Array Object which used to strore the set of bindings between
		 * Vertex Attributes and user's source vertex data. In render cycle user only need to bind Vertex Array
		 * Object connected which entity Vertex Buffers Objects. 
		 */
		class VertexArrayObject
		{
		private:
			GLuint vao;

		public:
			VertexArrayObject();
			VertexArrayObject(const VertexArrayObject& vertexArray);
			~VertexArrayObject();

			void bindVertexArray();
			void unbindVertexArray();

			GLuint getVAO() const;
		};
	}
}
#endif
