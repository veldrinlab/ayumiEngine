/**
 * File contains definition of Vertex class.
 * @file    Vertex.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "Vertex.hpp"
#include "VertexSet.hpp"

namespace AyumiEngine
{
	namespace AyumiDestruction
	{
		int Vertex::UNKNOWN = 1;
		int Vertex::INSIDE = 2;
		int Vertex::OUTSIDE = 3;
		int Vertex::BOUNDARY = 4;
		float Vertex::TOL = 1e-5f;

		/**
		 * Class default constructor.
		 */
		Vertex::Vertex()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			adjacentVertices = new VertexPointerSet(50);
			status = UNKNOWN;
		}

		/**
		 * Class copy constructor.
		 * @param	v is source vertex instance.
		 */
		Vertex::Vertex(const Vertex& v)
		{
			adjacentVertices = new VertexPointerSet(50);

			for(int i = 0; i < v.adjacentVertices->length(); i++)
				adjacentVertices->add(v.adjacentVertices->GetVertexPtr(i));
	
			status = v.status;
			x = v.x;
			y = v.y;
			z = v.z;
		}

		/**
		 * Class assign operator.
		 * @param	v is source vertex.
		 */
		Vertex& Vertex::operator=(const Vertex& v)
		{
			for(int i = 0; i < v.adjacentVertices->length(); i++)
				adjacentVertices->add(v.adjacentVertices->GetVertexPtr(i));
	
			status = v.status;
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		/**
		 * Class constructor with initialize parameters.
		 * @param	position is vertex vector.
		 */
		Vertex::Vertex(const Vector& position)
		{
			x = position.x;
			y = position.y;
			z = position.z;
			adjacentVertices = new VertexPointerSet(10);
			status = UNKNOWN;
		}

		/**
		 * Class constructor with initialize parameters.
		 * @param	position is vertex position vector.
		 * @param	status is vertex status.
		 */
		Vertex::Vertex(const Vector& position, int status)
		{
			x = position.x;
			y = position.y;
			z = position.z;
			adjacentVertices = new VertexPointerSet(10);
			this->status = status;
		}

		/**
		 * Class constructor with initialize parameters.
		 * @param	x is vertex x value.
		 * @param	y is vertex y value.
		 * @param	z is vertex z value.
		 */
		Vertex::Vertex(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			adjacentVertices = new VertexPointerSet(10);
			status = UNKNOWN;
		}

		/**
		 * Class constructor with initialize parameters.
		 * @param	x is vertex x value.
		 * @param	y is vertex y value.
		 * @param	z is vertex z value.
		 * @param	status is vertex new status.
		 */
		Vertex::Vertex(float x, float y, float z, int status)
		{	
			this->x = x;
			this->y = y;
			this->z = z;
			adjacentVertices = new VertexPointerSet(10);
			this->status = status;
		}

		/**
		 * Class destructor, free allocated memory. Delete adjacnet vertices.
		 */
		Vertex::~Vertex()
		{
			delete adjacentVertices;
		}

		/**
		 * Method is used to hecks if an vertex is equal to another.
		 * @param	vertex is pointer to another vertex.
		 * @return	 true if they are equal, false otherwise. 
		 */
		bool Vertex::equals(Vertex* vertex)
		{
			bool bPositionMatch =
				(fabs(x-vertex->x)<TOL &&
				 fabs(y-vertex->y)<TOL &&
				 fabs(z-vertex->z)<TOL);

			return bPositionMatch;
		}

		/**
		 * Method is used to set vertex status.
		 * @param	status is new vertex status.
		 */
		void Vertex::setStatus(int status)
		{
			if(status>=UNKNOWN && status<=BOUNDARY)
			{
				this->status = status;
			}
		}

		/**
		 * Accessor to priavte vertex position
		 * @return	vector with vertex posistion.
		 */
		Vector Vertex::getPosition()
		{
			return Vector(x, y, z);
		} 

		/**
		 * Accessor to private vertex status.
		 * @return	vertex status.
		 */
		int Vertex::getStatus()
		{
			return status;
		}

		/**
		 * Method is used to add adjacent vecrtex.
		 * @param	adjacentVertex is adjacent vertex.
		 */
		void Vertex::addAdjacentVertex(Vertex* adjacentVertex)
		{
			bool bAlready = false;
			for(int i = 0; i < adjacentVertices->GetNumVertexPointers(); i++)
			{
				Vertex * pVertexI = adjacentVertices->GetVertexPtr(i);
				if(pVertexI == adjacentVertex)
					bAlready = true;
			}

			if(!bAlready)
				adjacentVertices->AddVertexPointer(adjacentVertex);
		}

		/**
		 * Method is used to mark vertex.
		 * @param	status is vertex status.
		 */
		void Vertex::mark(int status)
		{
			this->status = status;

			for(int i = 0; i < adjacentVertices->GetNumVertexPointers(); i++)
			{
				Vertex * pVertexI = adjacentVertices->GetVertexPtr(i);

				if(pVertexI->getStatus()==Vertex::UNKNOWN)
				{
					pVertexI->mark(status);
				}
			}
		}
	}
}
