#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include "DLink.h"
#include "Texture.h"

namespace Axiom
{
    class TextureNode : public DLink
    {
    public:
        TextureNode();
        TextureNode(const Texture&) = delete;
        TextureNode& operator =(const Texture&) = delete;
        virtual ~TextureNode();

        void Set(Texture::Name name, Texture* texture);
        Texture* GetTexture() const;

        char* GetName() override;
        void Wash() override;
        bool Compare(DLink* targetNode) override;
        void Dump() override;

    private:
        void InternalClear();

        Texture* mTexture;
    };
}

#endif
