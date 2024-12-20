#include "CameraNodeMan.h"
#include "ManBase.h"
#include "DLinkMan.h"
#include "CameraNull.h"

Axiom::CameraNodeMan* Axiom::CameraNodeMan::mInstance = nullptr;

Axiom::CameraNodeMan::CameraNodeMan(const int reserveNum, const int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
      , mNodeCompare(new CameraNode())
      , mActiveCamera(nullptr)
{
    // Preload the reserve
    proFillReservedPool(reserveNum);

    Camera* camera = new CameraNull();
    assert(camera);

    assert(mNodeCompare);
    mNodeCompare->Set(Camera::Name::NullCamera, camera);
}

Axiom::CameraNodeMan::~CameraNodeMan()
{
    delete mNodeCompare;
    mNodeCompare = nullptr;

    Iterator* it = baseGetActiveIterator();
    it->First();

    while (!it->IsDone())
    {
        const CameraNode* node = (CameraNode*)it->Curr();
        it->Next();
        delete node;
    }

    it = baseGetReserveIterator();
    it->First();

    while (!it->IsDone())
    {
        const CameraNode* node = (CameraNode*)it->Curr();
        it->Next();
        delete node;
    }
}

DLink* Axiom::CameraNodeMan::derivedCreateNode()
{
    DLink* nodeBase = new CameraNode();
    assert(nodeBase != nullptr);

    return nodeBase;
}

void Axiom::CameraNodeMan::Create(const int reserveNum, const int reserveGrow)
{
    assert(reserveNum >= 0);
    assert(reserveGrow > 0);
    assert(mInstance == nullptr);

    if (mInstance == nullptr)
    {
        mInstance = new CameraNodeMan(reserveNum, reserveGrow);
    }
}

void Axiom::CameraNodeMan::Destroy()
{
    const CameraNodeMan* man = GetInstance();
    assert(man != nullptr);
    AZUL_UNUSED_VAR(man);

    delete mInstance;
    mInstance = nullptr;
}

Axiom::CameraNode* Axiom::CameraNodeMan::Add(const Camera::Name name, Camera* camera)
{
    CameraNodeMan* man = GetInstance();

    assert(camera);

    CameraNode* node = (CameraNode*)man->baseAddToFront();
    assert(node != nullptr);

    node->Set(name, camera);

    return node;
}

Axiom::CameraNode* Axiom::CameraNodeMan::Find(const Camera::Name name)
{
    CameraNodeMan* man = GetInstance();
    assert(man != nullptr);

    Camera* camera = man->mNodeCompare->GetCamera();
    assert(camera);

    camera->mName = name;

    return (CameraNode*)man->baseFind(man->mNodeCompare);
}

void Axiom::CameraNodeMan::Update(const float deltaTime)
{
    const CameraNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->mActiveCamera->UpdateCamera();
}

void Axiom::CameraNodeMan::SetActive(const Camera::Name name)
{
    CameraNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->mActiveCamera = Find(name)->GetCamera();
}

Axiom::Camera* Axiom::CameraNodeMan::GetActive()
{
    const CameraNodeMan* man = GetInstance();
    assert(man != nullptr);

    return man->mActiveCamera;
}

void Axiom::CameraNodeMan::Remove(CameraNode* node)
{
    assert(node != nullptr);

    CameraNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseRemove(node);
}

void Axiom::CameraNodeMan::Dump()
{
    CameraNodeMan* man = GetInstance();
    assert(man != nullptr);

    man->baseDump();
}

Axiom::CameraNodeMan* Axiom::CameraNodeMan::GetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(mInstance != nullptr);
    return mInstance;
}
