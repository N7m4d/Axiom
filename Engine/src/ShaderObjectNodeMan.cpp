#include "ShaderObjectNodeMan.h"
#include "ShaderObjectNull.h"
#include "ManBase.h"
#include "DLinkMan.h"

Axiom::ShaderObjectNodeMan* Axiom::ShaderObjectNodeMan::mInstance = nullptr;

Axiom::ShaderObjectNodeMan::ShaderObjectNodeMan(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
      , mNodeCompare(new ShaderObjectNode())
      , mCurrent(nullptr)
{
    proFillReservedPool(reserveNum);
    
    Shader* shader = new ShaderObjectNull(Shader::Name::NullShader);
    assert(shader);

    assert(mNodeCompare);

    mNodeCompare->Set(shader);
}

Axiom::ShaderObjectNodeMan::~ShaderObjectNodeMan()
{
    delete mNodeCompare;
    mNodeCompare = nullptr;
    
    Iterator* it = baseGetActiveIterator();
    it->First();
    
    while (!it->IsDone())
    {
        ShaderObjectNode* node = (ShaderObjectNode*)it->Curr();
        it->Next();
        delete node;
    }

    it = baseGetReserveIterator();
    it->First();
    
    while (!it->IsDone())
    {
        ShaderObjectNode* node = (ShaderObjectNode*)it->Curr();
        it->Next();
        delete node;
    }
}

void Axiom::ShaderObjectNodeMan::Create(int reserveNum, int reserveGrow)
{
    assert(reserveNum >= 0);
    assert(reserveGrow > 0);
    
    assert(mInstance == nullptr);
    
    if (mInstance == nullptr)
    {
        mInstance = new ShaderObjectNodeMan(reserveNum, reserveGrow);
    }
}

void Axiom::ShaderObjectNodeMan::Destroy()
{
    ShaderObjectNodeMan* man = GetInstance();
    assert(man != nullptr);
    AZUL_UNUSED_VAR(man);

    delete mInstance;
    mInstance = nullptr;
}

Axiom::ShaderObjectNode* Axiom::ShaderObjectNodeMan::Add(Shader* pMesh)
{
    ShaderObjectNodeMan* man = GetInstance();

    assert(pMesh);

    ShaderObjectNode* node = (ShaderObjectNode*)man->baseAddToFront();
    assert(node != nullptr);
    
    node->Set(pMesh);
    return node;
}

Axiom::Shader* Axiom::ShaderObjectNodeMan::Find(Shader::Name name)
{
    ShaderObjectNodeMan* man = GetInstance();
    assert(man != nullptr);
    
    Shader* shader = man->mNodeCompare->GetShaderObject();
    assert(shader);

    shader->mName = name;

    ShaderObjectNode* node = (ShaderObjectNode*)man->baseFind(man->mNodeCompare);
    return node->GetShaderObject();
}

void Axiom::ShaderObjectNodeMan::Remove(ShaderObjectNode* node)
{
    assert(node != nullptr);

    ShaderObjectNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseRemove(node);
}

void Axiom::ShaderObjectNodeMan::Dump()
{
    ShaderObjectNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseDump();
}

Axiom::ShaderObjectNode* Axiom::ShaderObjectNodeMan::GetNext()
{
    ShaderObjectNodeMan* man = GetInstance();
    assert(man != nullptr);

    if (!man->mCurrent || !man->mCurrent->pNext)
    {
        man->mCurrent = man->baseGetActiveIterator()->First();
    }
    else
    {
        man->mCurrent = man->mCurrent->pNext;
    }

    return (ShaderObjectNode*)man->mCurrent;
}

Axiom::ShaderObjectNodeMan* Axiom::ShaderObjectNodeMan::GetInstance()
{
    assert(mInstance != nullptr);
    return mInstance;
}

DLink* Axiom::ShaderObjectNodeMan::derivedCreateNode()
{
    DLink* node_base = new ShaderObjectNode();
    assert(node_base != nullptr);

    return node_base;
}
