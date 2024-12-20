#include "AnimControllerNode.h"
#include "StringThis.h"

Axiom::AnimControllerNode::AnimControllerNode()
	: mAnimController(nullptr)
{
	InternalClear();
}

Axiom::AnimControllerNode::~AnimControllerNode()
{
	InternalClear();
}

void Axiom::AnimControllerNode::Set(AnimController::Name name, AnimController* controller)
{
	assert(controller);
	mAnimController = controller;
	mAnimController->SetName(name);
}

Axiom::AnimController* Axiom::AnimControllerNode::GetController() const
{
	return mAnimController;
}

void Axiom::AnimControllerNode::InternalClear()
{
	delete mAnimController;
	mAnimController = nullptr;
}

char* Axiom::AnimControllerNode::GetName()
{
	char* name = nullptr;
	if (mAnimController)
	{
		name = mAnimController->GetName();
	}

	return name;
}

void Axiom::AnimControllerNode::Wash()
{
	InternalClear();
}

bool Axiom::AnimControllerNode::Compare(DLink* targetNode)
{
	assert(targetNode);

	const AnimControllerNode* targetController = (AnimControllerNode*)targetNode;

	bool status = false;

	assert(targetController->mAnimController);
	assert(mAnimController);

	if (mAnimController->mName == targetController->mAnimController->mName)
	{
		status = true;
	}

	return status;
}

void Axiom::AnimControllerNode::Dump()
{
	Trace::out("      AnimNode(%p)\n", this);
	
	if (mAnimController)
	{
		Trace::out("      AnimController(%p) \n", mAnimController);
		Trace::out("      Name: %s \n", StringMe(mAnimController->mName));
	}
	else
	{
		Trace::out("      Name: %s \n", "null");
	}

	DLink::Dump();
}
