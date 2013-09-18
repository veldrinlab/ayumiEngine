/**
 * File contains definition of VertexArrayObject class.
 * @file    VertexArrayObject.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-06
 */

#include "VertexArrayObject.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class default constructor, generate vertex array object.
		 */
		VertexArrayObject::VertexArrayObject()
		{
			glGenVertexArrays(1,&vao);
			glBindVertexArray(vao);
		}

		/**
		 * Class copy constructor.
		 * @param	vertexArray is copu source object.
		 */
		VertexArrayObject::VertexArrayObject(const VertexArrayObject& vertexArray)
		{
			this->vao = vertexArray.vao;
		}

		/**
		 * Class destructor, free allocated memory. Delete generated vertex array object.
		 */
		VertexArrayObject::~VertexArrayObject()
		{
			glDeleteVertexArrays(1,&vao);
		}

		/**
		 * Method is used to bind vertex array. Is is basic part of rendering cycle together with
		 * entity material binding.
		 */
		void VertexArrayObject::bindVertexArray()
		{
			glBindVertexArray(vao);
		}

		/**
		 * Method is used to unbind vertex array. Is is basic part of rendering cycle together with
		 * entity material unbinding.
		 */
		void VertexArrayObject::unbindVertexArray()
		{
			glBindVertexArray(0);
		}

		/**
		 * Accessor to private vertex array object id.
		 * @return	vao id.
		 */
		GLuint VertexArrayObject::getVAO() const
		{
			return vao;
		}
	}
}
