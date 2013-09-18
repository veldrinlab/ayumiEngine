/**
 * File contains definition of MeshFactory class.
 * @file    MeshFactory.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-10
 */

#include "MeshFactory.hpp"

using namespace std;
using namespace AyumiEngine::AyumiMath;
using namespace AyumiEngine::AyumiUtils;

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class default constructor. Set default raw parameters.
		 */
		MeshFactory::MeshFactory()
		{
			rawParams.size = 256;
			rawParams.rowScale = 1.0f;
			rawParams.columnScale = 1.0f;
			rawParams.heightScale = 1.0f;
			rawParams.maxCoord = 8.0f;
		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		MeshFactory::~MeshFactory()
		{
		
		}

		/**
		 * Method is used to create mesh resource. It implement Factory Method, depends on resource name
		 * factory choose creating method.
		 * @param	name is resource name.
		 * @param	type is name of resource type.
		 * @param	path is resource file path..
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createMeshResource(const string& name, const string& type, const string& path)
		{
			Mesh* meshResource = nullptr;

			if(type == "MESH_VEL")
				meshResource = createVelMesh(name,path);
			else if(type == "MESH_OBJ")
				meshResource = createObjMesh(name,path);
			else if(type == "MESH_3DS")
				meshResource = create3dsMesh(name,path);
			else if(type == "MESH_MD2")
				meshResource = createMD2Mesh(name,path);
			else if(type == "RAW")
				meshResource = createRawMesh(name,path);
			else if(type == "PROCEDURAL")
				meshResource = createProceduralMesh(name,1.2f);
			else
			{
				Logger::getInstance()->saveLog(Log<string>("Undefined mesh type requested!"));
				meshResource = nullptr;
			}
			return meshResource;
		}

		/**
		 * Method is used to initialize raw mesh file loading parameters.
		 * @param	size is raw file size;
		 * @param	rowScale is raw mesh row scale.
		 * @param	columnScale is raw mesh column scale.
		 * @param	heightScale is raw mesh height scale.
		 * @param	maxCoord is raw mesh max coord.
		 */
		void MeshFactory::initRawParameters(const int size, const float rowScale, const float columnScale, const float heightScale, const float maxCoord)
		{
			rawParams.size = size;
			rawParams.rowScale = rowScale;
			rawParams.columnScale = columnScale;
			rawParams.heightScale = heightScale;
			rawParams.maxCoord = maxCoord;
		}

		/**
		 * Method is used to load and create *vel text format, basic format of Engine. *vel format
		 * can be exported from Blender.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createVelMesh(const string& name, const string& path)
		{
			Mesh* meshResource = new Mesh(name.c_str(),path.c_str());
			
			int integerData = 0;
			float floatData = 0.0f;
			unsigned int indexData = 0;

			ifstream meshFile;
			meshFile.open(path);
			
			if(meshFile.is_open())
			{
				meshFile >> integerData;
				meshResource->setVerticesAmount(integerData);
				meshFile >> integerData;
				meshResource->setTrianglesAmount(integerData);

				meshResource->initializeDataArrays();
				
				for(int i = 0; i < meshResource->getVerticesAmount(); ++i)
				{
					meshFile >> floatData;
					meshResource->getVertices()[i].x = floatData;
					meshFile >> floatData;
					meshResource->getVertices()[i].y = floatData;
					meshFile >> floatData;
					meshResource->getVertices()[i].z = floatData;		
				}
				for(int i = 0; i < meshResource->getVerticesAmount(); ++i)
				{
					meshFile >> floatData;
					meshResource->getVertices()[i].nx = floatData;
					meshFile >> floatData;
					meshResource->getVertices()[i].ny = floatData;
					meshFile >> floatData;
					meshResource->getVertices()[i].nz = floatData;	
				}
				for(int i = 0; i < meshResource->getVerticesAmount(); ++i)
				{
					meshFile >> floatData;
					meshResource->getVertices()[i].u = floatData;
					meshFile >> floatData;
					meshResource->getVertices()[i].v = floatData;
				}
				for(int i = 0; i < meshResource->getTrianglesAmount()*3; ++i)
				{
					meshFile >> indexData;
					meshResource->setIndex(i,indexData);
				}
				meshResource->calculateTangent();
			}
			else
				Logger::getInstance()->saveLog(Log<string>("Vel Mesh file opening error occurred !"));	
			
			meshFile.close();

			return meshResource;
		}

		/**
		 * Method is used to load and create *obj text format, one of Engine format. It was designed
		 * by Wavefront.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createObjMesh(const string& name, const string& path)
		{
			Mesh* meshResource = new Mesh(name.c_str(),path.c_str());

			ifstream meshFile;
			string token;
			vector<Vertex<>> verts;
			Vertex<> vertexData;
			vector<Vertex<>> uv;
			Vertex<> uvData;
			vector<unsigned int> indexes;
			unsigned int indexData = 0;
			
			meshFile.open(path);
			
			if(meshFile.is_open())
			{
				while(!meshFile.eof())
				{
					meshFile >> token;

					if(token == "v")
					{
						meshFile >> vertexData.x >> vertexData.y >> vertexData.z;
						verts.push_back(vertexData);
					}
					else if(token == "vt")
					{
						meshFile >> uvData.u >> uvData.v;
						uv.push_back(uvData);
					}
					else if(token == "f")
					{
						for(int i = 0; i < 3; ++i)
						{
							meshFile >> token;
							int end = token.find_first_of("/");
							string finalIndex = token.substr(0,end);
							indexData = boost::lexical_cast<unsigned int>(finalIndex);		
							indexes.push_back(indexData);
						}
					}
				}

				meshResource->setVerticesAmount(verts.size());
				meshResource->setTrianglesAmount(indexes.size()/3);
				meshResource->initializeDataArrays();
			
				for(int i = 0; i < meshResource->getVerticesAmount(); ++i)
				{
					meshResource->getVertices()[i].x = verts.at(i).x;
					meshResource->getVertices()[i].y = verts.at(i).y;
					meshResource->getVertices()[i].z = verts.at(i).z;
					meshResource->getVertices()[i].u = uv.at(i).u;
					meshResource->getVertices()[i].v = uv.at(i).v;
				}

				for(int i = 0; i < meshResource->getTrianglesAmount()*3; ++i)
					meshResource->setIndex(i,indexes[i]-1);
					
				meshResource->calculateNormals();
				meshResource->calculateTangent();

				if (!meshFile.eof())
					Logger::getInstance()->saveLog(Log<string>(" Obj mesh file reading error occurred!"));	
				
			}
			else
				Logger::getInstance()->saveLog(Log<string>("Obj mesh file opening error occurred!"));	

			meshFile.close();

			return meshResource;
		}

		/**
		 * Method is used to load and create *3ds binary format, one of Engine format.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::create3dsMesh(const string& name, const string& path)
		{
			Mesh* meshResource = new Mesh(name.c_str(),path.c_str());

			ifstream meshFile;
			
			unsigned short dataQuantum = 0;
			unsigned short chunkID = 0;
			unsigned int chunkLength = 0;
			unsigned short faceFlags = 0;
			int i = 0;
			unsigned char charData = 0;
			
			meshFile.open(path,ios::in | ios::binary);
			
			if(meshFile.is_open())
			{
				while(!meshFile.eof())
				{
					meshFile.read(reinterpret_cast<char*>(&chunkID),sizeof(chunkID));
					meshFile.read(reinterpret_cast<char*>(&chunkLength),sizeof(chunkLength));
				
					switch(chunkID)
					{
					case 0x4d4d:
						break;
					case 0x3d3d:
						break;
					case 0x4000:
						i = 0;
						do
						{
							meshFile.read(reinterpret_cast<char*>(&charData),sizeof(charData));
							i++;
						}
						while(charData != '\0' && i < 20);
						break;
					case 0x4100:
						break;
					case 0x4110:
						meshFile.read(reinterpret_cast<char*>(&dataQuantum),sizeof(dataQuantum));
						meshResource->setVerticesAmount(dataQuantum);
						meshResource->initializeVerticesArray();
					
						for(int i = 0; i < meshResource->getVerticesAmount(); ++i)
						{
							meshFile.read(reinterpret_cast<char*>(&meshResource->getVertices()[i].x),sizeof(float));
							meshFile.read(reinterpret_cast<char*>(&meshResource->getVertices()[i].y),sizeof(float));
							meshFile.read(reinterpret_cast<char*>(&meshResource->getVertices()[i].z),sizeof(float));
						}
						break;
					case 0x4120:
						meshFile.read(reinterpret_cast<char*>(&dataQuantum),sizeof(dataQuantum));
						meshResource->setTrianglesAmount(dataQuantum);
						meshResource->initializeIndicesArray();

						for(int i = 0; i < meshResource->getTrianglesAmount()*3; i = i + 3)
						{
							unsigned short i1 = 0;
							unsigned short i2 = 0;
							unsigned short i3 = 0;

							meshFile.read(reinterpret_cast<char*>(&i1),sizeof(i1));
							meshFile.read(reinterpret_cast<char*>(&i2),sizeof(i2));
							meshFile.read(reinterpret_cast<char*>(&i3),sizeof(i3));

							meshResource->setIndex(i,i1);
							meshResource->setIndex(i+1,i2);
							meshResource->setIndex(i+2,i3);
							meshFile.read(reinterpret_cast<char*>(&faceFlags),sizeof(unsigned short));
						}
						break;
					case 0x4140:
							meshFile.read(reinterpret_cast<char*>(&dataQuantum),sizeof(dataQuantum));
					
						for(int i = 0; i < meshResource->getVerticesAmount(); ++i)
						{
							meshFile.read(reinterpret_cast<char*>(&meshResource->getVertices()[i].u),sizeof(float));
							meshFile.read(reinterpret_cast<char*>(&meshResource->getVertices()[i].v),sizeof(float));
						}
						break;
					default:
						meshFile.seekg(chunkLength-6,ios::cur);
				}
			}
				meshResource->calculateNormals();
				meshResource->calculateTangent();
			}
			else
				Logger::getInstance()->saveLog(Log<string>("3ds mesh file opening error occurred!"));	
			
			meshFile.close();

			return meshResource;
		}

		/**
		 * Method is used to load and create *md2 binary format, one of Engine format. It was used in
		 * Quake 2 for keyframe animation.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createMD2Mesh(const string& name, const string& path)
		{
			Mesh* meshResource = new Mesh[198];

			md2_header_t m_kHeader;
			md2_texCoord_t* m_pTexCoords;
			md2_triangle_t* m_pTriangles;
			md2_frame_t* m_pFrames;
		
			ifstream meshFile;
			meshFile.open(path,ios::in | ios::binary);
			
			if(meshFile.is_open())
			{
				meshFile.read(reinterpret_cast<char*>(&m_kHeader),sizeof(md2_header_t));
				if((m_kHeader.version != MD2_VERSION) || m_kHeader.ident != MD2_IDENT )
				{
					Logger::getInstance()->saveLog(Log<string>("MD2 mesh file wrong version/identification!"));	
					return meshResource;
				}

				m_pTexCoords = new md2_texCoord_t[m_kHeader.num_st];
				m_pTriangles = new md2_triangle_t[m_kHeader.num_tris];
				m_pFrames = new md2_frame_t[m_kHeader.num_frames];

				meshFile.seekg(m_kHeader.offset_st,ios::beg);
				meshFile.read(reinterpret_cast<char*>(m_pTexCoords),sizeof(md2_texCoord_t)*m_kHeader.num_st);
				meshFile.seekg(m_kHeader.offset_tris, ios::beg);
				meshFile.read(reinterpret_cast<char*>(m_pTriangles),sizeof(md2_triangle_t)*m_kHeader.num_tris);
				meshFile.seekg(m_kHeader.offset_frames,ios::beg);

				for( int i = 0; i < m_kHeader.num_frames; i++ )
				{
					m_pFrames[i].verts = new md2_vertex_t[ m_kHeader.num_vertices ];

					meshFile.read(reinterpret_cast<char*>(&m_pFrames[i].scale),sizeof(vec3_t));
					meshFile.read(reinterpret_cast<char*>(&m_pFrames[i].translate),sizeof(vec3_t));
					meshFile.read(reinterpret_cast<char*>(&m_pFrames[i].name),sizeof(char)*16);
					meshFile.read(reinterpret_cast<char*>(m_pFrames[i].verts),sizeof(md2_vertex_t)*m_kHeader.num_vertices);
				}

			}
			else
				Logger::getInstance()->saveLog(Log<string>("Md2 mesh file opening error occurred!"));	
				
			meshFile.close();

			for(int i = 0; i <198; ++i)
			{
				md2_frame_t* frame = &m_pFrames[i];

				meshResource[i].setVerticesAmount(m_kHeader.num_vertices);
				meshResource[i].setTrianglesAmount(m_kHeader.num_tris);
				meshResource[i].initializeDataArrays();
				meshResource[i].setAsComponentMesh();
				for(int j = 0; j <  m_kHeader.num_vertices; ++j)
				{
					vec3_t v;
					vec3_t n;

					v[0] = (frame->scale[0] * frame->verts[j].v[0] + frame->translate[0]);
					v[1] = (frame->scale[1] * frame->verts[j].v[1] + frame->translate[1]);
					v[2] = (frame->scale[2] * frame->verts[j].v[2] + frame->translate[2]);
					
					n[0] = avertexnormals[frame->verts[j].normalIndex][0];
					n[1] = avertexnormals[frame->verts[j].normalIndex][1];
					n[2] = avertexnormals[frame->verts[j].normalIndex][2];

					meshResource[i].getVertices()[j].x = v[0];
					meshResource[i].getVertices()[j].y = v[1];
					meshResource[i].getVertices()[j].z = v[2];
					meshResource[i].getVertices()[j].nx = n[0];
					meshResource[i].getVertices()[j].ny = n[1];
					meshResource[i].getVertices()[j].nz = n[2];
				}

				for(int vertToFound = 0; vertToFound < m_kHeader.num_vertices; ++vertToFound)
				{
					GLfloat u = 0.0f;
					GLfloat v = 0.0f;
					int k = 0;
					bool found = false;

					while(!found && (k < m_kHeader.num_tris))
					{
						if(m_pTriangles[k].vertex[0] == vertToFound)
						{
							found = true;
							u = static_cast<GLfloat>(m_pTexCoords[m_pTriangles[k].st[0]].s)/static_cast<GLfloat>(256);
							v = static_cast<GLfloat>(m_pTexCoords[m_pTriangles[k].st[0]].t)/static_cast<GLfloat>(256);
							meshResource[i].getVertices()[vertToFound].u = u;
							meshResource[i].getVertices()[vertToFound].v = v;
						}
						else if(m_pTriangles[k].vertex[1] == vertToFound)
						{
							found = true;
							u = static_cast<GLfloat>(m_pTexCoords[m_pTriangles[k].st[1]].s)/static_cast<GLfloat>(256);
							v = static_cast<GLfloat>(m_pTexCoords[m_pTriangles[k].st[1]].t)/static_cast<GLfloat>(256);
							meshResource[i].getVertices()[vertToFound].u = u;
							meshResource[i].getVertices()[vertToFound].v = v;
						}
						else if(m_pTriangles[k].vertex[2] == vertToFound)
						{
							found = true;
							u = static_cast<GLfloat>(m_pTexCoords[m_pTriangles[k].st[2]].s)/static_cast<GLfloat>(256);
							v = static_cast<GLfloat>(m_pTexCoords[m_pTriangles[k].st[2]].t)/static_cast<GLfloat>(256);
							meshResource[i].getVertices()[vertToFound].u = u;
							meshResource[i].getVertices()[vertToFound].v = v;
						}
						k++;
					}
				}

				for( int j = 0; j < m_kHeader.num_tris; ++j )
				{
					meshResource[i].setIndex(3*j,m_pTriangles[j].vertex[0]);
					meshResource[i].setIndex(3*j+1,m_pTriangles[j].vertex[1]);
					meshResource[i].setIndex(3*j+2,m_pTriangles[j].vertex[2]);
				}
				meshResource[i].calculateTangent();
			}

			for( int i = 0; i < m_kHeader.num_frames; i++ )
				delete [] m_pFrames[i].verts;

			delete [] m_pTexCoords;
			delete [] m_pTriangles;
			delete [] m_pFrames;
			
			return meshResource;
		}

		/**
		 * Method is used to load and create *md3 binary format, one of Engine format. It was used in
		 * Quake 3 for keyframe animation.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createMD3Mesh(const string& name, const string& path)
		{
			return nullptr;
		}
		
		/**
		 * Method is used to load and create *md5 binary format, one of Engine format. It was used in
		 * Quake 4/Doom3 for skeletal animation.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createMD5Mesh(const string& name, const string& path)
		{
			return nullptr;
		}

		/**
		 * Method is used to load and create terrain from height map.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createRawMesh(const string& name, const string& path)
		{
			unsigned char* fileData = new unsigned char[rawParams.size*rawParams.size];
			float* heightMap = new float[rawParams.size*rawParams.size];
			int vertexIndex = 0;

			ifstream rawFile;
			rawFile.open(path,ios::in | ios::binary);

			if(rawFile.is_open())
				rawFile.read((char*)fileData,sizeof(unsigned char)*rawParams.size*rawParams.size);
			else
				Logger::getInstance()->saveLog(Log<string>("Terrain raw file opening error occurred!"));	
			rawFile.close();

			const int terrainWidth = rawParams.size;
			const int terrainHeight = rawParams.size;		
			
			for(int i = 0; i < terrainWidth * terrainHeight; i++)
				heightMap[i] = static_cast<float>(fileData[i]);

			delete [] fileData;

			Mesh* meshResource = new Mesh(name.c_str(),path.c_str());
			meshResource->setVerticesAmount(terrainWidth*terrainHeight);
			meshResource->initializeVerticesArray();
			
			for(int z = 0; z < terrainWidth; ++z)
			{
				for(int x = 0; x < terrainHeight; ++x)
				{
					Vector3D normal;						
					meshResource->getVertices()[vertexIndex].x = (static_cast<float>(z)*rawParams.rowScale);
					meshResource->getVertices()[vertexIndex].y = ((heightMap[z*terrainWidth+x])/256.0f)*rawParams.heightScale;
					meshResource->getVertices()[vertexIndex].z = (static_cast<float>(x)*rawParams.columnScale);
					
				//	meshResource->getVertices()[vertexIndex].x = (static_cast<float>(z)*rawParams.rowScale)-(terrainWidth*0.5f*rawParams.rowScale);
				//	meshResource->getVertices()[vertexIndex].y = ((heightMap[z*terrainWidth+x])/256.0f)*rawParams.heightScale-rawParams.heightScale*0.5f;
				//	meshResource->getVertices()[vertexIndex].z = (static_cast<float>(x)*rawParams.columnScale)-(terrainHeight*0.5f*rawParams.columnScale);
					
					meshResource->getVertices()[vertexIndex].u = static_cast<float>(x)/rawParams.maxCoord;
					meshResource->getVertices()[vertexIndex].v = static_cast<float>(z)/rawParams.maxCoord;
	
					int h1 = 0; // right neighbour
					int h2 = 0; // up neighbour
					int h3 = 0; // left neighbour
					int h4 = 0; // down neighbour

					if(x != terrainWidth - 1)
						h1 = static_cast<int>(heightMap[(z*terrainWidth) + x + 1]);
					else
						h1 = 0;
					if(z != 0)
						h3 = static_cast<int>(heightMap[(z*terrainWidth) + x - 1]);
					else
						h3 = 0;
					if(z != 0)
						h2 = static_cast<int>(heightMap[((z-1)*terrainWidth) + x]);
					else
						h2 = 0;
					if(z != terrainWidth-1)
						h4 = static_cast<int>(heightMap[((z+1)*terrainWidth) + x]);
					else
						h4 = 0;

					normal.set(static_cast<float>(h3-h1),static_cast<float>(h4-h2),2.0f);
					normal.normalize();
					meshResource->getVertices()[vertexIndex].nx = normal.x();
					meshResource->getVertices()[vertexIndex].ny = normal.y();
					meshResource->getVertices()[vertexIndex].nz = normal.z();
					vertexIndex++;
				}
			}

			// 2 triangles for every quad of the terrain mesh
			const int numTriangles = (terrainWidth-1)*(terrainHeight-1)*2;
 
			// 3 indices for each triangle in the terrain mesh
			meshResource->setTrianglesAmount(numTriangles);
			meshResource->initializeIndicesArray();

			int index = 0; // Index in the index buffer

			for( int j = 0; j < terrainWidth-1; ++j)
			{
				for(int i2 = 0; i2 < terrainHeight-1; ++i2)
				{
					int vertexIndex2 = (j*terrainWidth)+i2;

					// Top triangle (T0)
					meshResource->setIndex(index++,vertexIndex2);                           // V0
					meshResource->setIndex(index++,vertexIndex2 + terrainWidth + 1);        // V3
					meshResource->setIndex(index++,vertexIndex2 + 1);// V1
					// Bottom triangle (T1)
					meshResource->setIndex(index++,vertexIndex2);                           // V0
					meshResource->setIndex(index++,vertexIndex2 + terrainWidth);            // V2
					meshResource->setIndex(index++,vertexIndex2 + terrainWidth + 1);        // V3
				}
			}
			meshResource->calculateTangent();
			delete[] heightMap;
			return meshResource;
		}

		/**
		 * Method is used to create procedural terrain mesh using Midpoint Displacement algorithm.
		 * @param	name is resource name.
		 * @param	path is resource file path.
		 * @return	loaded and created mesh resource, or nullptr when and logger error type is
		 *			not supported.
		 */
		Mesh* MeshFactory::createProceduralMesh(const string& name, const float roughness)
		{
			int size = 512;
			float gridSpacing = 1.0f;
			float heightScale = 100.0f;
			float maxCoord = 8.0f;
			int vertexIndex = 0;
			float* heightMap = new float[size*size];

			// Based on article and associated code:
			// "Fractal Terrain Generation - Midpoint Displacement" by Jason Shankel
			// (Game Programming Gems I, pp.503-507).

			srand(static_cast<unsigned int>(time(0)));

			//ustawiamy na zero
			for(int i = 0; i < size * size; ++i)
				heightMap[i] = 0.0f;
			
			int p1, p2, p3, p4, mid;
			float dH = size * 0.5f;
			float dHFactor = powf(2.0f, -roughness);
			float minH = 0.0f, maxH = 0.0f;

			for (int w = size; w > 0; dH *= dHFactor, w /= 2)
			{
				// Diamond Step.
				for (int z = 0; z < size; z += w)
				{
					for (int x = 0; x < size; x += w)
					{
						p1 = ((x + size) % size) + ((z + size) % size) * size;
						p2 = ((x + w + size) % size) + ((z + size) % size) * size;
						p3 = ((x + w + size) % size) + ((z + w + size) % size) * size;
						p4 = ((x + size) % size) + ((z + w + size) % size) * size;
						mid = ((x + (w/2) + size) % size) + ((z +(w/2) + size) % size) * size;
							
						heightMap[mid] = CommonMath::random(-dH,dH) + (heightMap[p1]+heightMap[p2]+heightMap[p3]+heightMap[p4])*0.25f;

						minH = min(minH, heightMap[mid]);
						maxH = max(maxH, heightMap[mid]);
					}
				}

				// Square step.
				for (int z = 0; z < size; z += w)
				{
					for (int x = 0; x < size; x += w)
					{
						p1 = ((x + size) % size) + ((z + size) % size) * size;
						p2 = ((x + w + size) % size) + ((z + size) % size) * size;
						p3 = ((x + (w/2) + size) % size) + ((z - (w/2) + size) % size) * size;
						p4 = ((x + (w/2) + size) % size) + ((z +(w/2) + size) % size) * size;
						mid = ((x + (w/2) + size) % size) + ((z + size) % size) * size;
						
						heightMap[mid] = CommonMath::random(-dH,dH) + (heightMap[p1]+heightMap[p2]+heightMap[p3]+heightMap[p4])*0.25f;

						minH = min(minH, heightMap[mid]);
						maxH = max(maxH, heightMap[mid]);

						p1 = ((x + size) % size) + ((z + size) % size) * size;
						p2 = ((x + size) % size) + ((z + w + size) % size) * size;
						p3 = ((x + (w/2) + size) % size) + ((z + (w/2) + size) % size) * size;
						p4 = ((x - (w/2) + size) % size) + ((z + (w/2) + size) % size) * size;
						mid = ((x + size) % size) + ((z + (w/2) + size) % size) * size;
						
						heightMap[mid] = CommonMath::random(-dH,dH) + (heightMap[p1]+heightMap[p2]+heightMap[p3]+heightMap[p4])*0.25f;

						minH = min(minH, heightMap[mid]);
						maxH = max(maxH, heightMap[mid]);
					}
				}
			}
			
			// Normalize height field so altitudes fall into range [0,255].
			for(int i = 0; i < size * size; ++i)
				heightMap[i] = 255.0f * (heightMap[i] - minH) / (maxH - minH);

			Mesh* meshResource = new Mesh(name.c_str(),"null");
			
			meshResource->setVerticesAmount(size*size);
			meshResource->initializeVerticesArray();
	
			for(int z = 0; z < size; ++z)
			{
				for(int x = 0; x < size; ++x)
				{
					meshResource->getVertices()[vertexIndex].x = static_cast<float>(z) * gridSpacing;
					meshResource->getVertices()[vertexIndex].y = (heightMap[z*size + x] / 256.0f) * heightScale;
					meshResource->getVertices()[vertexIndex].z = static_cast<float>(x) * gridSpacing;
					
					meshResource->getVertices()[vertexIndex].u = static_cast<float>(x) / maxCoord;
					meshResource->getVertices()[vertexIndex].v = static_cast<float>(z) / maxCoord;
					
					Vector3D normal;

					int h1 = 0; // right neighbour
					int h2 = 0; // up neighbour
					int h3 = 0; // left neighbour
					int h4 = 0; // down neighbour

					if(x != size - 1)
						h1 = static_cast<int>(heightMap[(z*size) + x + 1]);
					else
						h1 = 0;

					if(z != 0)
						h3 = static_cast<int>(heightMap[(z*size) + x - 1]);
					else
						h3 = 0;

					if(z != 0)
						h2 = static_cast<int>(heightMap[((z-1)*size) + x]);
					else
						h2 = 0;

					if(z != size-1)
						h4 = static_cast<int>(heightMap[((z+1)*size) + x]);
					else
						h4 = 0;

					normal.set(static_cast<float>(h3-h1),static_cast<float>(h4-h2),2.0f);
					normal.normalize();

					meshResource->getVertices()[vertexIndex].nx = normal.x();
					meshResource->getVertices()[vertexIndex].ny = normal.y();
					meshResource->getVertices()[vertexIndex].nz = normal.z();

					vertexIndex++;
				}
			}
 
			const int terrainWidth = size;
			const int terrainHeight = size;
 
			// 2 triangles for every quad of the terrain mesh
			const int numTriangles = ( size - 1 ) * ( size - 1 ) * 2; // (?) -1
 
			// 3 indices for each triangle in the terrain mesh
			meshResource->setTrianglesAmount(numTriangles);
			meshResource->initializeIndicesArray();
			
			int index = 0; // Index in the index buffer

			for( int j = 0; j < size-1; ++j)
			{
				for(int i = 0; i < size-1; ++i)
				{
					int vertexIndex = ( j * terrainWidth ) + i;

					// Top triangle (T0)
					meshResource->setIndex(index++,vertexIndex);                           // V0
					meshResource->setIndex(index++,vertexIndex + terrainWidth + 1);        // V3
					meshResource->setIndex(index++,vertexIndex + 1);                       // V1
					// Bottom triangle (T1)
					meshResource->setIndex(index++,vertexIndex);                           // V0
					meshResource->setIndex(index++,vertexIndex + terrainWidth);            // V2
					meshResource->setIndex(index++,vertexIndex + terrainWidth + 1);        // V3
				}
			}
			meshResource->calculateTangent();

			delete[] heightMap;
			return meshResource;
		}
	}
}
