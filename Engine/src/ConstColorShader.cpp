#include "ConstColorShader.h"
#include "Mesh.h"
#include "ConstColor.PS.h"
#include "ConstColor.VS.h"

D3D11_INPUT_ELEMENT_DESC ShaderObject_ConstColorDesc[] =
{
    {
        "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, static_cast<uint32_t>(Axiom::VertexSlot::Position),
        offsetof(Axiom::VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0
    }
};

Axiom::ConstColorShader::ConstColorShader(Name name)
    : Shader(
          name, sizeof(g_ConstColor_VS), (void*)g_ConstColor_VS, sizeof(g_ConstColor_PS),
          (void*)g_ConstColor_PS, ShaderObject_ConstColorDesc, sizeof(ShaderObject_ConstColorDesc)
      )
      , mColorBuffer{sizeof(Vec3)}
{
}

void Axiom::ConstColorShader::ActivateCBV()
{
    Shader::ActivateCBV();
    mColorBuffer.SetActive(ConstantBufferSlot::LightColor);
}

void Axiom::ConstColorShader::TransferColor(const Vec3* color) const
{
    mColorBuffer.Transfer(color);
}
