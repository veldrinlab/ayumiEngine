/**
 * File contains definition of GeoModifier class.
 * @file    GeoModifier.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "GeoModifier.hpp"
#include "VertexSet.hpp"

using namespace AyumiEngine::AyumiScene;
using namespace AyumiEngine::AyumiResource;

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		/**
		 * Class constructor with initialize parameters.
		 * @param	mesh is pointer to first mesh.
		 * @param	mesh2 is pointer to second mesh.
		 */
		GeoModifier::GeoModifier(SceneEntity* mesh, SceneEntity* mesh2)
		{
			firstObject = new Object3D(convertMeshToSolid(mesh));
			secondObject = new Object3D(convertMeshToSolid(mesh2));
	
			firstObject ->splitFaces(secondObject);
			secondObject->splitFaces(firstObject);
			firstObject ->classifyFaces(*secondObject);
			secondObject->classifyFaces(*firstObject);
		}

		/**
		 * Class destructor, free allocated memory. Delete objects data.
		 */
		GeoModifier::~GeoModifier()
		{
			delete firstObject;
			delete secondObject;
		}

		/**
		 * Method is used to perform CSG and get mesh difference.
		 * @return	result mesh.
		 */
		Mesh* GeoModifier::getDifference()
		{
			secondObject->invertInsideFaces();
			Solid* result = composeSolid(Face::OUTSIDE, Face::OPPOSITE, Face::INSIDE);
			secondObject->invertInsideFaces();
			return convertSolidToMesh(result);
		}

		/**
		 * Method is used to compose result solid.
		 * @param	faceStatus1 is face status.
		 * @param	faceStatus2 is face status.
		 * @param	faceStatus3 is face status.
		 * @return	pointer to result solid.
		 */
		Solid* GeoModifier::composeSolid(int faceStatus1, int faceStatus2, int faceStatus3) 
		{
			VertexSet* vertices = new VertexSet();
			IntSet* indices = new IntSet();
	
			groupObjectComponents(*firstObject, *vertices, *indices, faceStatus1, faceStatus2);
			groupObjectComponents(*secondObject, *vertices, *indices, faceStatus3, faceStatus3);
	
			VectorSet * vectors = new VectorSet();

			for(int i = 0; i < vertices->GetNumVertices(); i++)
			{
				Vertex * pVertex = vertices->GetVertex(i);
				vectors->push_back(pVertex->getPosition());
			}
	
			Solid* result = new Solid();
			result->indices = *indices;
			result->vertices = *vectors;
			delete indices;
			delete vertices;
			delete vectors;

			return result;
		}

		/**
		 * Method is used to group object components.
		 * @param	object is source object.
		 * @param	vertices is other object vertices.
		 * @pram	indices is other object indices.
		 * @param	faceStatus1 is face status.
		 * @param	faceStatus2 is face status.
		 */
		void GeoModifier::groupObjectComponents(Object3D& object, VertexSet& vertices, IntSet& indices, int faceStatus1, int faceStatus2)
		{
			//for each face..
			for(int i = 0; i < object.getNumFaces(); ++i)
			{
				Face& face = *(object.getFace(i));

				if(face.getStatus()==faceStatus1 || face.getStatus()==faceStatus2)
				{
					VertexPointerSet faceVerts;
					faceVerts.add(face.v1);
					faceVerts.add(face.v2);
					faceVerts.add(face.v3);

					for(int j=0;j<faceVerts.length();j++)
					{
						if(vertices.contains(faceVerts[j]))
							indices.push_back(vertices.indexOf(faceVerts[j]));
						else
						{
							indices.push_back(vertices.length());
							vertices.AddVertex(*faceVerts[j]);
						}
					}
				}
			}
		}

		/**
		 * Method is used to convert mesh data to solid data.
		 * @param	mesh is pointer to scene entity.
		 * @return	pointer to created solid data.
		 */
		Solid* GeoModifier::convertMeshToSolid(SceneEntity* mesh)
		{
			Solid* solid = new Solid();
	
			for(int i = 0; i < mesh->entityGeometry.geometryMesh->getVerticesAmount(); ++i)
			{
				float x = mesh->entityGeometry.geometryMesh->getVertices()[i].x;
				float y = mesh->entityGeometry.geometryMesh->getVertices()[i].y;
				float z = mesh->entityGeometry.geometryMesh->getVertices()[i].z;

				solid->vertices.push_back(Vector(x,y,z));
			}

			for(int i = 0; i < mesh->entityGeometry.geometryMesh->getTrianglesAmount()*3; ++i)
			{
				unsigned int index = mesh->entityGeometry.geometryMesh->getIndices()[i];
				solid->indices.push_back(index);
			}
			return solid;
		}

		/**
		 * Method is used to convert solid to mesh data.
		 * @param	solid is pointer to solid data.
		 * @return	pointer to mesh data.
		 */
		Mesh* GeoModifier::convertSolidToMesh(Solid* solid)
		{
			Mesh* result = new Mesh();
			result->setVerticesAmount(solid->vertices.size());
			result->setTrianglesAmount(solid->indices.size()/3);
			result->initializeDataArrays();
	
			int coordCounter = 0;
			for(unsigned i = 0; i < solid->vertices.size(); ++i)
			{
				result->getVertices()[i].x = solid->vertices[i].x;
				result->getVertices()[i].y = solid->vertices[i].y;
				result->getVertices()[i].z = solid->vertices[i].z;
		
				if(coordCounter == 0)
				{
					result->getVertices()[i].u = 0.0f;
					result->getVertices()[i].v = 1.0f;
				}
				else if(coordCounter == 1)
				{
					result->getVertices()[i].u = 1.0f;
					result->getVertices()[i].v = 1.0f;
				}
				else if(coordCounter == 2)
				{
					result->getVertices()[i].u = 1.0f;
					result->getVertices()[i].v = 0.0f;
				}
				coordCounter = (coordCounter + 1) % 3;
			}

			for(unsigned i = 0; i < solid->indices.size(); ++i)
				result->setIndex(i,solid->indices[i]);

			result->calculateNormals();
			result->calculateTangent();

			return result;
		}
	}
}
