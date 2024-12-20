#ifndef SHADER_MAPPINGS_H
#define SHADER_MAPPINGS_H

namespace Axiom
{
    enum class VertexSlot : uint32_t
    {
        Position, // 0
        Color, // 1
        Norm, // 2
        TexCoord // 3
    };

    enum class ConstantBufferSlot : uint32_t
    {
        Projection, // 0
        View, // 1
        World, // 2
        LightColor, // 3
        LightPos
    };

    enum class ShaderResourceBufferSlot : uint32_t
    {
        TexA // slot 0  
    };

    enum class ShaderSamplerSlot : uint32_t
    {
        SampleA // slot 0
    };
}

#endif
