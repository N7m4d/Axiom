#ifndef CONST_COLOR_SHADER_H
#define CONST_COLOR_SHADER_H

#include "Shader.h"

namespace Axiom
{
    class ConstColorShader : public Shader
    {
    public:
        ConstColorShader(const ConstColorShader&) = delete;
        ConstColorShader& operator =(const ConstColorShader&) = delete;
        ~ConstColorShader() override = default;

        ConstColorShader(Name name);

        void ActivateCBV() override;
        void TransferColor(const Vec3* color) const;

        ConstantBuffer mColorBuffer;
    };
}

#endif // !CONST_COLOR_SHADER_H
