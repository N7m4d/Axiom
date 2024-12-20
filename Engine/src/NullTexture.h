#ifndef NULL_TEXTURE_H
#define NULL_TEXTURE_H

#include "Texture.h"

namespace Axiom
{
    class NullTexture final : public Texture
    {
    public:
        NullTexture() = default;
        NullTexture(const NullTexture&) = delete;
        NullTexture& operator=(const NullTexture& other) = delete;
        ~NullTexture() override = default;
    };
}

#endif
