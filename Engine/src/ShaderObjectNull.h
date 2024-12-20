#ifndef SHADER_OBJECT_NULL_H
#define SHADER_OBJECT_NULL_H

#include "Shader.h"

namespace Axiom
{
    class ShaderObjectNull : public Shader
    {
    public:
        ShaderObjectNull() = delete;
        ShaderObjectNull(const ShaderObjectNull&) = delete;
        ShaderObjectNull& operator =(const ShaderObjectNull&) = delete;
        ~ShaderObjectNull() override = default;

        ShaderObjectNull(Name name);

        void ActivateShader() override;
    };
}

#endif
