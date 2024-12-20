#include "CameraNode.h"
#include "StringThis.h"

Axiom::CameraNode::CameraNode()
    : mCamera(nullptr)
{
    InternalClear();
}

Axiom::CameraNode::~CameraNode()
{
    InternalClear();
}

void Axiom::CameraNode::Set(Camera::Name name, Camera* camera)
{
    assert(camera);
    mCamera = camera;
    mCamera->SetName(name);
}

Axiom::Camera* Axiom::CameraNode::GetCamera() const
{
    return mCamera;
}

char* Axiom::CameraNode::GetName()
{
    return mCamera->GetName();
}

void Axiom::CameraNode::Wash()
{
}

bool Axiom::CameraNode::Compare(DLink* targetNode)
{
    assert(targetNode);

    CameraNode* node = (CameraNode*)targetNode;

    bool status = false;

    assert(node->mCamera);
    assert(mCamera);

    if (mCamera->mName == node->mCamera->mName)
    {
        status = true;
    }

    return status;
}

void Axiom::CameraNode::Dump()
{
    Trace::out("      CameraNode(%p)\n", this);

    if (mCamera)
    {
        Trace::out("      Camera(%p) \n", mCamera);
        Trace::out("      Name: %s \n", StringMe(mCamera->mName));
    }
    else
    {
        Trace::out("      Name: %s \n", "null");
    }

    DLink::Dump();
}

void Axiom::CameraNode::InternalClear()
{
    delete mCamera;
    mCamera = nullptr;
}
