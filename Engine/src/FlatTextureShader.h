#ifndef FLAT_TEXTURE_SHADER_H
#define FLAT_TEXTURE_SHADER_H

#include "Shader.h"

namespace Axiom
{
    class FlatTextureShader : public Shader
    {
    public:
        FlatTextureShader(const FlatTextureShader&) = delete;
        FlatTextureShader& operator =(const FlatTextureShader&) = delete;
        ~FlatTextureShader() override = default;

        FlatTextureShader(Name name);
    };
}

#endif // !FLAT_TEXTURE_SHADER_H
