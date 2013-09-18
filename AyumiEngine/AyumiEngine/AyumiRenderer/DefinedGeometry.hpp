/**
 * File contains definition of defined in-engine geometry like quad for FrameBuffer/Sprites
 * and bounding volume/frustrum mesg geometry data.
 * @file    DefinedGeometry.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#ifndef DEFINEDGEOMETRY_HPP
#define DEFINEDGEOMETRY_HPP

#include <GL/glew.h>

const int quadVertexAmount = 4;
const int quadTriangleAmount = 2;

const GLfloat quadVertices[quadVertexAmount*3] =
{
	1.000000f, 1.000000f, 0.000000f,
	-1.000000f, 1.000000f, 0.000000f,
	-1.000000f, -1.000000f, 0.000000f,
	1.000000f, -1.000000f, 0.000000f
};

const GLfloat quadNormals[quadVertexAmount*3] =
{
	0.000000f, 0.000000f, 1.000000f,
	0.000000f, 0.000000f, 1.000000f,
	0.000000f, 0.000000f, 1.000000f,
	0.000000f, 0.000000f, 1.000000f
};

const GLfloat quadUV[quadVertexAmount*2] =
{
	1.000000f, 0.000000f, 
	0.000000f, 0.000000f,
	0.000000f, 1.000000f,
	1.000000f, 1.000000f
};

const unsigned int quadIndices[quadTriangleAmount*3] =
{
	0,1,2,
	0,2,3
};

const int boxVertexAmount = 24;
const int boxTriangleAmount = 12;

const GLfloat boxVertices[boxVertexAmount*3] =
{
	1.000000f, 1.000000f, -1.000000f,
	1.000000f, -1.000000f, -1.000000f,
	-1.000000f, -1.000000f, -1.000000f,
	-1.000000f, 1.000000f, -1.000000f,
	1.000000f, 1.000000f, 1.000000f,
	-1.000000f, 1.000000f, 1.000000f,
	-1.000000f, -1.000000f, 1.000000f,
	1.000000f, -1.000001f, 1.000000f,
	1.000000f, 1.000000f, -1.000000f,
	1.000000f, 1.000000f, 1.000000f,
	1.000000f, -1.000001f, 1.000000f,
	1.000000f, -1.000000f, -1.000000f,
	1.000000f, -1.000000f, -1.000000f,
	1.000000f, -1.000001f, 1.000000f,
	-1.000000f, -1.000000f, 1.000000f,
	-1.000000f, -1.000000f, -1.000000f,
	-1.000000f, -1.000000f, -1.000000f,
	-1.000000f, -1.000000f, 1.000000f,
	-1.000000f, 1.000000f, 1.000000f,
	-1.000000f, 1.000000f, -1.000000f,
	1.000000f, 1.000000f, 1.000000f,
	1.000000f, 1.000000f, -1.000000f,
	-1.000000f, 1.000000f, -1.000000f,
	-1.000000f, 1.000000f, 1.000000f

};

const unsigned int boxIndices[boxTriangleAmount*3] =
{
	0, 1, 2,
	0, 2, 3,
	4, 5, 6,
	4, 6, 7,
	8, 9, 10,
	8, 10, 11,
	12, 13, 14,
	12, 14, 15,
	16, 17, 18,
	16, 18, 19,
	20, 21, 22,
	20, 22, 23
};

const GLfloat octNode[boxVertexAmount*3] =
{
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f
};
#endif
