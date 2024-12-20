#include "MeshNode.h"
#include "StringThis.h"

Axiom::MeshNode::MeshNode()
    : mMesh(nullptr)
{
    InternalClear();
}

Axiom::MeshNode::~MeshNode()
{
    InternalClear();
}

void Axiom::MeshNode::Set(Mesh::Name name, Mesh* mesh)
{
    assert(mesh);
    mMesh = mesh;
    mMesh->SetName(name);
}

Axiom::Mesh* Axiom::MeshNode::GetMesh() const
{
    return mMesh;
}

void Axiom::MeshNode::InternalClear()
{
    delete mMesh;
    mMesh = nullptr;
}

char* Axiom::MeshNode::GetName()
{
    char* name = nullptr;
    if (mMesh)
    {
        name = mMesh->GetName();
    }

    return name;
}

void Axiom::MeshNode::Wash()
{
    InternalClear();
}

bool Axiom::MeshNode::Compare(DLink* targetNode)
{
    assert(targetNode);

    MeshNode* node = (MeshNode*)targetNode;

    bool status = false;

    assert(node->mMesh);
    assert(mMesh);

    if (mMesh->mName == node->mMesh->mName)
    {
        status = true;
    }

    return status;
}

void Axiom::MeshNode::Dump()
{
    Trace::out("      MeshNode(%p)\n", this);

    if (mMesh)
    {
        Trace::out("      Mesh(%p) \n", mMesh);
        Trace::out("      Name: %s \n", StringMe(mMesh->mName));
    }
    else
    {
        Trace::out("      Name: %s \n", "null");
    }

    DLink::Dump();
}
