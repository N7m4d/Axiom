#include "MeshNodeMan.h"
#include "NullMesh.h"
#include "ManBase.h"
#include "DLinkMan.h"

Axiom::MeshNodeMan* Axiom::MeshNodeMan::mInstance = nullptr;

Axiom::MeshNodeMan::MeshNodeMan(const int reserveNum, const int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
      , mNodeCompare(new MeshNode())
{
    proFillReservedPool(reserveNum);

    Mesh* mesh = new NullMesh();
    assert(mesh);

    assert(mNodeCompare);
    mNodeCompare->Set(Mesh::Name::NullMesh, mesh);
}

Axiom::MeshNodeMan::~MeshNodeMan()
{
    delete mNodeCompare;
    mNodeCompare = nullptr;

    Iterator* it = baseGetActiveIterator();
    it->First();

    while (!it->IsDone())
    {
        MeshNode* node = (MeshNode*)it->Curr();
        it->Next();
        delete node;
    }

    it = baseGetReserveIterator();
    it->First();

    while (!it->IsDone())
    {
        MeshNode* node = (MeshNode*)it->Curr();
        it->Next();
        delete node;
    }
}

void Axiom::MeshNodeMan::Create(const int reserveNum, const int reserveGrow)
{
    assert(reserveNum >= 0);
    assert(reserveGrow > 0);

    assert(mInstance == nullptr);

    if (mInstance == nullptr)
    {
        mInstance = new MeshNodeMan(reserveNum, reserveGrow);
    }
}

void Axiom::MeshNodeMan::Destroy()
{
    MeshNodeMan* man = GetInstance();
    assert(man != nullptr);
    AZUL_UNUSED_VAR(man);

    delete mInstance;
    mInstance = nullptr;
}

Axiom::MeshNode* Axiom::MeshNodeMan::Add(Mesh::Name name, Mesh* pMesh)
{
    MeshNodeMan* man = GetInstance();

    assert(pMesh);

    MeshNode* node = (MeshNode*)man->baseAddToFront();
    assert(node != nullptr);

    node->Set(name, pMesh);
    return node;
}

Axiom::Mesh* Axiom::MeshNodeMan::Find(Mesh::Name name)
{
    MeshNodeMan* man = GetInstance();
    assert(man != nullptr);

    Mesh* mesh = man->mNodeCompare->GetMesh();
    assert(mesh);

    mesh->mName = name;

    MeshNode* node = (MeshNode*)man->baseFind(man->mNodeCompare);

    if (node)
    {
        mesh = node->GetMesh();
    }
    else
    {
        mesh = nullptr;
    }

    return mesh;
}

void Axiom::MeshNodeMan::Remove(MeshNode* node)
{
    assert(node != nullptr);

    MeshNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseRemove(node);
}

void Axiom::MeshNodeMan::Dump()
{
    MeshNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseDump();
}

Axiom::MeshNodeMan* Axiom::MeshNodeMan::GetInstance()
{
    assert(mInstance != nullptr);
    return mInstance;
}

DLink* Axiom::MeshNodeMan::derivedCreateNode()
{
    DLink* node = new MeshNode();
    assert(node != nullptr);

    return node;
}
