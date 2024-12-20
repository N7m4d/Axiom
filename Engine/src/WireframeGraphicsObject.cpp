#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "WireframeGraphicsObject.h"
#include "Shader.h"
#include "CameraNodeMan.h"
#include "DirectXDeviceMan.h"

Axiom::WireframeGraphicsObject::WireframeGraphicsObject(Mesh* mesh, Shader* shader)
    : GraphicsObject(mesh, shader)
{
    assert(mModel);
    assert(mShaderObj);
    assert(mWorld);
}

void Axiom::WireframeGraphicsObject::SetState()
{
    D3D11_RASTERIZER_DESC rasterizerDesc = {};

    rasterizerDesc.AntialiasedLineEnable = FALSE;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.ScissorEnable = FALSE;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;

    ID3D11RasterizerState* rasterizerState;
    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);

    DirectXDeviceMan::GetContext()->RSSetState(rasterizerState);

    SafeRelease(rasterizerState)
}

void Axiom::WireframeGraphicsObject::SetDataGPU()
{
    mShaderObj->ActivateShader();
    mShaderObj->ActivateCBV();
    mShaderObj->TransferWorldViewProj(CameraNodeMan::GetActive(), mWorld);
    mModel->ActivateMesh();
}

void Axiom::WireframeGraphicsObject::Draw()
{
    mModel->RenderIndexBuffer();
}

void Axiom::WireframeGraphicsObject::RestoreState()
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

    ID3D11RasterizerState* rasterizerState;
    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateRasterizerState(&desc, &rasterizerState);

    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);

    DirectXDeviceMan::GetContext()->RSSetState(rasterizerState);

    SafeRelease(rasterizerState)
}
