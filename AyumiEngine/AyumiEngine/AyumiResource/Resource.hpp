/**
 * File contains declaration of Resource class.
 * @file    Resource.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-15
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "ResourceType.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Class represents base class of all Resource which are supported by Engine. All Resource
		 * class must extend this class. It store basic data of all resources like name or path.
		 */
		class Resource
		{
		protected:
			ResourceType resourceType;
			const char* resourceName;
			const char* resourcePath;

		public:
			virtual ~Resource() {};

			ResourceType getResourceType();
			const char* getResourceName() const;
			const char* getResourcePath() const;		
		};
	}
}

#endif