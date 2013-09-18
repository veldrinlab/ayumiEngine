/**
 * File contains definition of CollisionHandler class.
 * @file    CollisionHandler.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#include "CollisionHandler.hpp"

using namespace std;

namespace AyumiEngine
{
	namespace AyumiPhysics
	{
		/**
		 * Class default constructor. Nothing to do.
		 */
		CollisionHandler::CollisionHandler()
		{

		}

		/**
		 * Class destructor, free allocated memory. Nothing to delete.
		 */
		CollisionHandler::~CollisionHandler()
		{
			collisionCallbacks.clear();
		}

		/**
		 * Method is used to call collision response function/method. It is called by PhysiX scene.
		 * @param	pair store data of actors.
		 * @param	events store data of contact event.
		 */
		void CollisionHandler::onContact(PxContactPair& pair, PxU32 events)
		{
			CollisionCallback::const_iterator it = collisionCallbacks.begin();

			for(; it != collisionCallbacks.end(); ++it)
				if((*it).first.first == string(pair.actors[0]->getName()) && (*it).first.second == string(pair.actors[1]->getName()))
					break;	
			if(it != collisionCallbacks.end())
			{
				currentActors.first = string(pair.actors[0]->getName());
				currentActors.second = string(pair.actors[1]->getName());
				(*it).second();
			}
		}

		/**
		 * Method is used to add collision callback funtion to collision handler map.
		 * @param	name is first actor name.
		 * @param	name2 is second actor name.
		 * @param	method is callback function object.
		 */
		void CollisionHandler::addCollisionCallback(const string& name, const string& name2, boost::function<void()> method)
		{
			collisionCallbacks.insert(make_pair(make_pair(name,name2),method));
		}

		/**
		 * Accessor to private current collision actors name.
		 * @return	pair of current collision actors.
		 */
		CollisionActors CollisionHandler::getCurrentActors()
		{
			return currentActors;
		}
	}
}
