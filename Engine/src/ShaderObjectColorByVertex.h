#ifndef SHADER_OBJECT_COLOR_BY_VERTEX_H
#define SHADER_OBJECT_COLOR_BY_VERTEX_H

#include "Shader.h"

namespace Axiom
{
    class ShaderObjectColorByVertex : public Shader
    {
    public:
        ShaderObjectColorByVertex() = delete;
        ShaderObjectColorByVertex(const ShaderObjectColorByVertex&) = delete;
        ShaderObjectColorByVertex& operator =(const ShaderObjectColorByVertex&) = delete;
        ~ShaderObjectColorByVertex() override = default;

        ShaderObjectColorByVertex(Name name);
    };
}

#endif
