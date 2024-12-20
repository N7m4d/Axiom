#ifndef TEXTURE_PROTO_H
#define TEXTURE_PROTO_H

#include "Texture.h"
#include "textureData.h"

namespace Axiom
{
    class TextureProto : public Texture
    {
    public:
        TextureProto() = delete;
        TextureProto(const TextureProto&) = delete;
        TextureProto& operator =(const TextureProto&) = delete;
        virtual ~TextureProto();

        TextureProto(textureData& texture, Name name, D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

        ID3D11Texture2D* mTex;
    };
}

#endif
