#include "ShaderObjectNode.h"
#include "StringThis.h"

Axiom::ShaderObjectNode::ShaderObjectNode()
    : mShaderObject(nullptr)
{
    privClear();
}

Axiom::ShaderObjectNode::~ShaderObjectNode()
{
    privClear();
}

void Axiom::ShaderObjectNode::Set(Shader* shader)
{
    assert(shader);
    mShaderObject = shader;
    mShaderObject->SetName(mShaderObject->mName);
}

Axiom::Shader* Axiom::ShaderObjectNode::GetShaderObject() const
{
    return mShaderObject;
}

void Axiom::ShaderObjectNode::privClear()
{
    delete this->mShaderObject;
    mShaderObject = nullptr;
}

char* Axiom::ShaderObjectNode::GetName()
{
    char* name = nullptr;
    if (mShaderObject)
    {
        name = mShaderObject->GetName();
    }

    return name;
}

void Axiom::ShaderObjectNode::Wash()
{
    privClear();
}

bool Axiom::ShaderObjectNode::Compare(DLink* targetNode)
{
    assert(targetNode);

    ShaderObjectNode* node = (ShaderObjectNode*)targetNode;

    bool status = false;

    assert(node->mShaderObject);
    assert(mShaderObject);

    if (mShaderObject->mName == node->mShaderObject->mName)
    {
        status = true;
    }

    return status;
}

void Axiom::ShaderObjectNode::Dump()
{
    Trace::out("      ShaderObjectNode(%p)\n", this);

    if (mShaderObject)
    {
        Trace::out("      ShaderObject(%p) \n", mShaderObject);
        Trace::out("      Name: %s \n", StringMe(mShaderObject->mName));
    }
    else
    {
        Trace::out("      Name: %s \n", "null");
    }

    DLink::Dump();
}
