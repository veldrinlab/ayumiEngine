#ifndef SCENENODE_HPP
#define SCENENODE_HPP

namespace AyumiEngine
{
	namespace AyumiScene
	{
		struct SceneNode
		{
			SceneNode* parent;
			SceneNode* leftBrother;
			SceneNode* rightBrother;
			SceneNode* child;
		};
	}
}
#endif
