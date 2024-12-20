#include "TextureNode.h"
#include "StringThis.h"

Axiom::TextureNode::TextureNode()
    : mTexture(nullptr)
{
    InternalClear();
}

Axiom::TextureNode::~TextureNode()
{
    InternalClear();
}

void Axiom::TextureNode::Set(Texture::Name name, Texture* texture)
{
    assert(texture);
    mTexture = texture;
    mTexture->SetName(name);
}

Axiom::Texture* Axiom::TextureNode::GetTexture() const
{
    return mTexture;
}

void Axiom::TextureNode::InternalClear()
{
    delete mTexture;
    mTexture = nullptr;
}

char* Axiom::TextureNode::GetName()
{
    char* name = nullptr;
    if (mTexture)
    {
        name = mTexture->GetName();
    }

    return name;
}

void Axiom::TextureNode::Wash()
{
    InternalClear();
}

bool Axiom::TextureNode::Compare(DLink* targetNode)
{
    assert(targetNode);

    TextureNode* node = (TextureNode*)targetNode;

    assert(node->mTexture);
    assert(mTexture);

    if (mTexture->mName == node->mTexture->mName)
    {
        return true;
    }

    return false;
}

void Axiom::TextureNode::Dump()
{
    Trace::out("      TextureNode(%p)\n", this);

    if (mTexture)
    {
        Trace::out("      Texture(%p) \n", mTexture);
        Trace::out("      Name: %s \n", StringMe(mTexture->mName));
    }
    else
    {
        Trace::out("      Name: %s \n", "null");
    }

    DLink::Dump();
}
