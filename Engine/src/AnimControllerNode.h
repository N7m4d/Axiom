#ifndef ANIM_CONTROLLER_NODE_H
#define ANIM_CONTROLLER_NODE_H

#include "DLink.h"
#include "AnimController.h"

namespace Axiom
{
	class AnimControllerNode : public DLink
	{
	public:
		AnimControllerNode();
		AnimControllerNode(const AnimControllerNode&) = delete;
		AnimControllerNode& operator = (const AnimControllerNode&) = delete;
		virtual ~AnimControllerNode();

		void Set(AnimController::Name name, AnimController* controller);
		AnimController* GetController() const;

		char* GetName() override;
		void Wash() override;
		bool Compare(DLink* targetNode) override;
		void Dump() override;

	private:
		void InternalClear();

		AnimController* mAnimController;
	};
}

#endif
