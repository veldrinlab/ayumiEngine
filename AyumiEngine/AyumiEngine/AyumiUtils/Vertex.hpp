/**
 * File contains definition of Vertex templated structure.
 * @file    Vertex.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-22
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Structure represents templated basic part of engine geometry - data of geometry mesh vertex 
		 * which store position, normals, tangents and uv coordinates of each vertex. It is used to store 
		 * 3D model Mesh data and store it in Vertex Buffer Objects for efficient rendering. Structure is
		 * templated but OpenGL use GLfloat/float type in the most situations.
		 */
		template<class T = float>
		struct Vertex
		{
			T x,y,z;
			T nx, ny, nz;
			T u, v;
			T tx,ty,tz,tw;
		};
	}
}
#endif
