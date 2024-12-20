#include "TextureNodeMan.h"
#include "NullTexture.h"
#include "ManBase.h"
#include "DLinkMan.h"

Axiom::TextureNodeMan* Axiom::TextureNodeMan::mInstance = nullptr;

Axiom::TextureNodeMan::TextureNodeMan(const int reserveNum, const int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	, mNodeCompare(new TextureNode())
	, mCurrent(nullptr)
{
	proFillReservedPool(reserveNum);
	
	Texture* texture = new NullTexture();
	assert(texture);

	assert(mNodeCompare);
	mNodeCompare->Set(Texture::Name::NullTexture, texture);
}

Axiom::TextureNodeMan::~TextureNodeMan()
{
	delete mNodeCompare;
	mNodeCompare = nullptr;
	
	Iterator* it = baseGetActiveIterator();
	it->First();
	
	while (!it->IsDone())
	{
		TextureNode* node = (TextureNode*)it->Curr();
		it->Next();
		delete node;
	}

	it = baseGetReserveIterator();
	it->First();
	
	while (!it->IsDone())
	{
		TextureNode* node = (TextureNode*)it->Curr();
		it->Next();
		delete node;
	}
}

void Axiom::TextureNodeMan::Create(const int reserveNum, const int reserveGrow)
{
	assert(reserveNum >= 0);
	assert(reserveGrow > 0);

	assert(mInstance == nullptr);
	
	if (mInstance == nullptr)
	{
		mInstance = new TextureNodeMan(reserveNum, reserveGrow);
	}
}

void Axiom::TextureNodeMan::Destroy()
{
	TextureNodeMan* man = GetInstance();
	assert(man != nullptr);
	AZUL_UNUSED_VAR(man);

	delete mInstance;
	mInstance = nullptr;
}

Axiom::TextureNode* Axiom::TextureNodeMan::Add(Texture::Name name, Texture* texture)
{
	TextureNodeMan* man = GetInstance();

	assert(texture);

	TextureNode* node = (TextureNode*)man->baseAddToFront();
	assert(node != nullptr);
	
	node->Set(name, texture);
	return node;
}

Axiom::Texture* Axiom::TextureNodeMan::Find(Texture::Name name)
{
	TextureNodeMan* man = GetInstance();
	assert(man != nullptr);
	
	Texture* texture = man->mNodeCompare->GetTexture();
	assert(texture);

	texture->mName = name;

	TextureNode* node = (TextureNode*)man->baseFind(man->mNodeCompare);
	return node->GetTexture();
}

Axiom::TextureNode* Axiom::TextureNodeMan::GetNext()
{
	TextureNodeMan* man = GetInstance();
	assert(man != nullptr);

	if (!man->mCurrent || !man->mCurrent->pNext)
	{
		man->mCurrent = man->baseGetActiveIterator()->First();
	}
	else
	{
		man->mCurrent = man->mCurrent->pNext;
	}

	return (TextureNode*)man->mCurrent;
}

void Axiom::TextureNodeMan::Remove(TextureNode* node)
{
	assert(node != nullptr);

	TextureNodeMan* man = GetInstance();
	assert(man != nullptr);

	man->baseRemove(node);
}

void Axiom::TextureNodeMan::Dump()
{
	TextureNodeMan* man = GetInstance();
	assert(man != nullptr);

	man->baseDump();
}

Axiom::TextureNodeMan* Axiom::TextureNodeMan::GetInstance()
{
	assert(mInstance != nullptr);
	return mInstance;
}

DLink* Axiom::TextureNodeMan::derivedCreateNode()
{
	DLink* nodeBase = new TextureNode();
	assert(nodeBase != nullptr);

	return nodeBase;
}
