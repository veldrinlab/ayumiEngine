/**
 * File contains declaration of MD2 format loading header and helper structrs and constants.
 * @file    FileMD2.hpp
 * @author  Szymon "Veldrin" Jab�o�ski
 * @date    2011-07-10
 */

#ifndef FILEMD2
#define FILEMD2

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Some useful identification tools.
		 */
		#define MD2_IDENT (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')
		#define	MD2_VERSION 8
		#define NUMVERTEXNORMALS 162

		/**
		 * Predefined MD2 mesh normals.
		 */
		static float avertexnormals[NUMVERTEXNORMALS][3] = 
		{
			{-0.525731f, 0.000000f, 0.850651f},
			{-0.442863f, 0.238856f, 0.864188f},
			{-0.295242f, 0.000000f, 0.955423f},
			{-0.309017f, 0.500000f, 0.809017f},
			{-0.162460f, 0.262866f, 0.951056f},
			{0.000000f, 0.000000f, 1.000000f},
			{0.000000f, 0.850651f, 0.525731f},
			{-0.147621f, 0.716567f, 0.681718f},
			{0.147621f, 0.716567f, 0.681718f},
			{0.000000f, 0.525731f, 0.850651f},
			{0.309017f, 0.500000f, 0.809017f},
			{0.525731f, 0.000000f, 0.850651f},
			{0.295242f, 0.000000f, 0.955423f},
			{0.442863f, 0.238856f, 0.864188f},
			{0.162460f, 0.262866f, 0.951056f},
			{-0.681718f, 0.147621f, 0.716567f},
			{-0.809017f, 0.309017f, 0.500000f},
			{-0.587785f, 0.425325f, 0.688191f},
			{-0.850651f, 0.525731f, 0.000000f},
			{-0.864188f, 0.442863f, 0.238856f},
			{-0.716567f, 0.681718f, 0.147621f},
			{-0.688191f, 0.587785f, 0.425325f},
			{-0.500000f, 0.809017f, 0.309017f},
			{-0.238856f, 0.864188f, 0.442863f},
			{-0.425325f, 0.688191f, 0.587785f},
			{-0.716567f, 0.681718f, -0.147621f},
			{-0.500000f, 0.809017f, -0.309017f},
			{-0.525731f, 0.850651f, 0.000000f},
			{0.000000f, 0.850651f, -0.525731f},
			{-0.238856f, 0.864188f, -0.442863f},
			{0.000000f, 0.955423f, -0.295242f},
			{-0.262866f, 0.951056f, -0.162460f},
			{0.000000f, 1.000000f, 0.000000f},
			{0.000000f, 0.955423f, 0.295242f},
			{-0.262866f, 0.951056f, 0.162460f},
			{0.238856f, 0.864188f, 0.442863f},
			{0.262866f, 0.951056f, 0.162460f},
			{0.500000f, 0.809017f, 0.309017f},
			{0.238856f, 0.864188f, -0.442863f},
			{0.262866f, 0.951056f, -0.162460f},
			{0.500000f, 0.809017f, -0.309017f},
			{0.850651f, 0.525731f, 0.000000f},
			{0.716567f, 0.681718f, 0.147621f},
			{0.716567f, 0.681718f, -0.147621f},
			{0.525731f, 0.850651f, 0.000000f},
			{0.425325f, 0.688191f, 0.587785f},
			{0.864188f, 0.442863f, 0.238856f},
			{0.688191f, 0.587785f, 0.425325f},
			{0.809017f, 0.309017f, 0.500000f},
			{0.681718f, 0.147621f, 0.716567f},
			{0.587785f, 0.425325f, 0.688191f},
			{0.955423f, 0.295242f, 0.000000f},
			{1.000000f, 0.000000f, 0.000000f},
			{0.951056f, 0.162460f, 0.262866f},
			{0.850651f, -0.525731f, 0.000000f},
			{0.955423f, -0.295242f, 0.000000f},
			{0.864188f, -0.442863f, 0.238856f},
			{0.951056f, -0.162460f, 0.262866f},
			{0.809017f, -0.309017f, 0.500000f},
			{0.681718f, -0.147621f, 0.716567f},
			{0.850651f, 0.000000f, 0.525731f},
			{0.864188f, 0.442863f, -0.238856f},
			{0.809017f, 0.309017f, -0.500000f},
			{0.951056f, 0.162460f, -0.262866f},
			{0.525731f, 0.000000f, -0.850651f},
			{0.681718f, 0.147621f, -0.716567f},
			{0.681718f, -0.147621f, -0.716567f},
			{0.850651f, 0.000000f, -0.525731f},
			{0.809017f, -0.309017f, -0.500000f},
			{0.864188f, -0.442863f, -0.238856f},
			{0.951056f, -0.162460f, -0.262866f},
			{0.147621f, 0.716567f, -0.681718f},
			{0.309017f, 0.500000f, -0.809017f},
			{0.425325f, 0.688191f, -0.587785f},
			{0.442863f, 0.238856f, -0.864188f},
			{0.587785f, 0.425325f, -0.688191f},
			{0.688191f, 0.587785f, -0.425325f},
			{-0.147621f, 0.716567f, -0.681718f},
			{-0.309017f, 0.500000f, -0.809017f},
			{0.000000f, 0.525731f, -0.850651f},
			{-0.525731f, 0.000000f, -0.850651f},
			{-0.442863f, 0.238856f, -0.864188f},
			{-0.295242f, 0.000000f, -0.955423f},
			{-0.162460f, 0.262866f, -0.951056f},
			{0.000000f, 0.000000f, -1.000000f},
			{0.295242f, 0.000000f, -0.955423f},
			{0.162460f, 0.262866f, -0.951056f},
			{-0.442863f, -0.238856f, -0.864188f},
			{-0.309017f, -0.500000f, -0.809017f},
			{-0.162460f, -0.262866f, -0.951056f},
			{0.000000f, -0.850651f, -0.525731f},
			{-0.147621f, -0.716567f, -0.681718f},
			{0.147621f, -0.716567f, -0.681718f},
			{0.000000f, -0.525731f, -0.850651f},
			{0.309017f, -0.500000f, -0.809017f},
			{0.442863f, -0.238856f, -0.864188f},
			{0.162460f, -0.262866f, -0.951056f},
			{0.238856f, -0.864188f, -0.442863f},
			{0.500000f, -0.809017f, -0.309017f},
			{0.425325f, -0.688191f, -0.587785f},
			{0.716567f, -0.681718f, -0.147621f},
			{0.688191f, -0.587785f, -0.425325f},
			{0.587785f, -0.425325f, -0.688191f},
			{0.000000f, -0.955423f, -0.295242f},
			{0.000000f, -1.000000f, 0.000000f},
			{0.262866f, -0.951056f, -0.162460f},
			{0.000000f, -0.850651f, 0.525731f},
			{0.000000f, -0.955423f, 0.295242f},
			{0.238856f, -0.864188f, 0.442863f},
			{0.262866f, -0.951056f, 0.162460f},
			{0.500000f, -0.809017f, 0.309017f},
			{0.716567f, -0.681718f, 0.147621f},
			{0.525731f, -0.850651f, 0.000000f},
			{-0.238856f, -0.864188f, -0.442863f},
			{-0.500000f, -0.809017f, -0.309017f},
			{-0.262866f, -0.951056f, -0.162460f},
			{-0.850651f, -0.525731f, 0.000000f},
			{-0.716567f, -0.681718f, -0.147621f},
			{-0.716567f, -0.681718f, 0.147621f},
			{-0.525731f, -0.850651f, 0.000000f},
			{-0.500000f, -0.809017f, 0.309017f},
			{-0.238856f, -0.864188f, 0.442863f},
			{-0.262866f, -0.951056f, 0.162460f},
			{-0.864188f, -0.442863f, 0.238856f},
			{-0.809017f, -0.309017f, 0.500000f},
			{-0.688191f, -0.587785f, 0.425325f},
			{-0.681718f, -0.147621f, 0.716567f},
			{-0.442863f, -0.238856f, 0.864188f},
			{-0.587785f, -0.425325f, 0.688191f},
			{-0.309017f, -0.500000f, 0.809017f},
			{-0.147621f, -0.716567f, 0.681718f},
			{-0.425325f, -0.688191f, 0.587785f},
			{-0.162460f, -0.262866f, 0.951056f},
			{0.442863f, -0.238856f, 0.864188f},
			{0.162460f, -0.262866f, 0.951056f},
			{0.309017f, -0.500000f, 0.809017f},
			{0.147621f, -0.716567f, 0.681718f},
			{0.000000f, -0.525731f, 0.850651f},
			{0.425325f, -0.688191f, 0.587785f},
			{0.587785f, -0.425325f, 0.688191f},
			{0.688191f, -0.587785f, 0.425325f},
			{-0.955423f, 0.295242f, 0.000000f},
			{-0.951056f, 0.162460f, 0.262866f},
			{-1.000000f, 0.000000f, 0.000000f},
			{-0.850651f, 0.000000f, 0.525731f},
			{-0.955423f, -0.295242f, 0.000000f},
			{-0.951056f, -0.162460f, 0.262866f},
			{-0.864188f, 0.442863f, -0.238856f},
			{-0.951056f, 0.162460f, -0.262866f},
			{-0.809017f, 0.309017f, -0.500000f},
			{-0.864188f, -0.442863f, -0.238856f},
			{-0.951056f, -0.162460f, -0.262866f},
			{-0.809017f, -0.309017f, -0.500000f},
			{-0.681718f, 0.147621f, -0.716567f},
			{-0.681718f, -0.147621f, -0.716567f},
			{-0.850651f, 0.000000f, -0.525731f},
			{-0.688191f, 0.587785f, -0.425325f},
			{-0.587785f, 0.425325f, -0.688191f},
			{-0.425325f, 0.688191f, -0.587785f},
			{-0.425325f, -0.688191f, -0.587785f},
			{-0.587785f, -0.425325f, -0.688191f},
			{-0.688191f, -0.587785f, -0.425325f},
		};

		/**
		 * Structure represents MD2 format vector.
		 */
		typedef float vec3_t[3];

		/**
		 * Structure represents MD2 format file header.
		 */
		typedef struct
		{
			int	ident;			
			int	version;		

			int	skinwidth;		
			int	skinheight;		

			int	framesize;		

			int	num_skins;		
			int	num_vertices;	
			int	num_st;			
			int	num_tris;		
			int	num_glcmds;		
			int	num_frames;		

			int	offset_skins;	
			int	offset_st;		
			int	offset_tris;	
			int	offset_frames;	
			int	offset_glcmds;	
			int	offset_end;		

		} md2_header_t;
		
		/**
		 * Structure represents MD2 format skin name.
		 */
		typedef struct
		{
			char name[68];

		} md2_skin_t;

		/**
		 * Structure represents MD2 format texture coords.
		 */
		typedef struct
		{
			short s;
			short t;

		} md2_texCoord_t;

		/**
		 * Structure represents MD2 format triangle.
		 */
		typedef struct
		{
		   unsigned short vertex[3];
		   unsigned short st[3];

		} md2_triangle_t;

		/**
		 * Structure represents MD2 format vertex.
		 */
		typedef struct
		{
			unsigned char v[3];
			unsigned char normalIndex;

		} md2_vertex_t;

		/**
		 * Structure represents MD2 format frame.
		 */
		typedef struct
		{
			vec3_t scale;
			vec3_t translate;
			char name[16];
			md2_vertex_t* verts;

		} md2_frame_t;

		/**
		 * Structure represents MD2 format OpenGL commands.
		 */
		typedef struct
		{
			float s;
			float t;
			int index;

		} md2_glcmd_t;
	}
}
#endif
