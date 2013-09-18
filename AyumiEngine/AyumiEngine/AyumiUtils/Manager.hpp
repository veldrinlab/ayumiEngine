/**
 * File contains declaration of templated Manager pattern interface class.
 * @file    Manager.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-13
 */

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <map>
#include <iostream>
#include <fstream>

#include "../Logger.hpp"

namespace AyumiEngine
{
	namespace AyumiUtils
	{
		/**
		 * Class represents Manager pattern implementaion which is adapter on map data structure.
		 * It is used by Resource Manager units - Shader, Texture, Mesh and Audio managers.
		 * Class is templated on resource id and resource class.
		 */
		template<class KeyClass, class ResourceClass>
		class Manager
		{
		protected:
			std::map<KeyClass,ResourceClass> resourceMap;

		public:
			/**
			 * Class default constructor. Nothing to do.
			 */
			Manager()
			{

			}

			/**
			 * Class destructor, free allocated memory. Nothing to delele.
			 */
			virtual ~Manager()
			{

			}

			/**
			 * Method is used to add resource to map.
			 * @param	resourceKey is resource id, for example name.
			 * @param	resourceObject is resource object, for example smart pointer to resource.
			 */
			void addResource(const KeyClass& resourceKey, const ResourceClass& resourceObject)
			{
				resourceMap.insert(std::map<KeyClass, ResourceClass>::value_type(resourceKey, resourceObject));
			}

			/**
			 * Method is used to release resource from map.
			 * @param	resourceName is resource id, for example name.
			 */
			void deleteResource(const KeyClass& resourceKey)
			{
				resourceMap.erase(resourceMap.find(resourceKey));
			}

			/**
			 * Method is used to clear resource map.
			 */
			void clearResourceMap()
			{
				resourceMap.clear();
			}

			/**
			 * Accessor to resource that is stored in resource map.
			 * @param	resourceKey is resource id, for example name.
			 * @return	resource connected with parameter key or error Log when resource doesn't exist.
			 */
			ResourceClass getResource(const KeyClass& resourceKey) const
			{
				std::map<KeyClass, ResourceClass>::const_iterator iterator = resourceMap.find(resourceKey);
				
				if(iterator != resourceMap.end())
					return iterator->second;
				else
				{
					Logger::getInstance()->saveLog(Log<string>("Can't load engine resource, return nullptr!!!"));
					return iterator->second;
				}
			}
		};
	}
}
#endif
