#include "ConstColorGraphicsObject.h"

#include "CameraNodeMan.h"
#include "ConstColorShader.h"
#include "DirectXDeviceMan.h"
#include "Mesh.h"

Axiom::ConstColorGraphicsObject::ConstColorGraphicsObject(Mesh* mesh, Shader* shader, const Vec3& lightColor)
    : GraphicsObject(mesh, shader)
      , mLightColor(new Vec3(lightColor))
{
}

Axiom::ConstColorGraphicsObject::~ConstColorGraphicsObject()
{
    delete mLightColor;
}

void Axiom::ConstColorGraphicsObject::SetState()
{
    D3D11_RASTERIZER_DESC desc = {};

    desc.AntialiasedLineEnable = FALSE;
    desc.CullMode = D3D11_CULL_FRONT;
    desc.DepthBias = 0;
    desc.DepthBiasClamp = 0.0f;
    desc.DepthClipEnable = TRUE;
    desc.FillMode = D3D11_FILL_SOLID;
    desc.FrontCounterClockwise = FALSE;
    desc.MultisampleEnable = FALSE;
    desc.ScissorEnable = FALSE;
    desc.SlopeScaledDepthBias = 0.0f;

    ID3D11RasterizerState* rasterState;
    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&desc, &rasterState);
    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);

    DirectXDeviceMan::GetContext()->RSSetState(rasterState);

    SafeRelease(rasterState)
}

void Axiom::ConstColorGraphicsObject::SetDataGPU()
{
    mShaderObj->ActivateShader();
    mShaderObj->ActivateCBV();

    mShaderObj->TransferWorldViewProj(CameraNodeMan::GetActive(), mWorld);
    ((ConstColorShader*)mShaderObj)->TransferColor(mLightColor);

    mModel->ActivateMesh();
}

void Axiom::ConstColorGraphicsObject::Draw()
{
    mModel->RenderIndexBuffer();
}

void Axiom::ConstColorGraphicsObject::RestoreState()
{
    D3D11_RASTERIZER_DESC desc = {};

    desc.AntialiasedLineEnable = FALSE;
    desc.CullMode = D3D11_CULL_FRONT;
    desc.DepthBias = 0;
    desc.DepthBiasClamp = 0.0f;
    desc.DepthClipEnable = TRUE;
    desc.FillMode = D3D11_FILL_SOLID;
    desc.FrontCounterClockwise = FALSE;
    desc.MultisampleEnable = FALSE;
    desc.ScissorEnable = FALSE;
    desc.SlopeScaledDepthBias = 0.0f;

    ID3D11RasterizerState* pRasterState;
    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&desc, &pRasterState);
    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);

    DirectXDeviceMan::GetContext()->RSSetState(pRasterState);

    SafeRelease(pRasterState)
}
