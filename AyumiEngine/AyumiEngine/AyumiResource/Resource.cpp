/**
 * File contains definition of Resource class.
 * @file    Resource.cpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-04-15
 */

#include "Resource.hpp"

namespace AyumiEngine
{
	namespace AyumiResource
	{
		/**
		 * Accessor to resource type private member.
		 * @return	resource type.
		 */
		ResourceType Resource::getResourceType()
		{
			return resourceType;
		}

		/**
		 * Accessor to resource name private member.
		 * @return	resource name.
		 */
		const char* Resource::getResourceName() const
		{
			return resourceName;
		}

		/**
		 * Accessor to resource path private member.
		 * @return	resource path.
		 */
		const char* Resource::getResourcePath() const
		{
			return resourcePath;
		}
	}
}
