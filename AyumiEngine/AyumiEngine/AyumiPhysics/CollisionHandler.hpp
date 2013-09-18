/**
 * File contains declaraion of CollisionHandler class.
 * @file    CollisionHandler.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2012-01-15
 */

#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include <PhysXAPI/PxPhysicsAPI.h>
#include <PhysXAPI/PxSimulationEventCallback.h>

#include <boost/function.hpp>
#include <string>
#include <map>

namespace AyumiEngine
{
	namespace AyumiPhysics
	{
		typedef std::map<std::pair<std::string,std::string>,boost::function<void()>> CollisionCallback;
		typedef std::pair<std::string,std::string> CollisionActors;

		/**
		 * Class represents scene collision handler which is used to call collision repsonse functions.
		 * It extedns PxSimulationEventCallback class. All callbacks are stored in function map. When
		 * some objects collide on scene, PhysiX call onContact method with actors names.
		 */
		class CollisionHandler : public PxSimulationEventCallback
		{
		private:
			CollisionCallback collisionCallbacks;
			CollisionActors currentActors;
		public:
			CollisionHandler();
			~CollisionHandler();

			virtual void onContact(PxContactPair& pair, PxU32 events);
			void addCollisionCallback(const std::string& name, const std::string& name2, boost::function<void()> method);
			CollisionActors getCurrentActors();
		};
	}
}
#endif
