#include "Shader.h"
#include "Engine.h"
#include "StringThis.h"
#include "DirectXDeviceMan.h"

Axiom::Shader::Shader(Name name, const size_t vsSize, const void* vsBytecode, const size_t psSize,
                      const void* psBytecode,
                      D3D11_INPUT_ELEMENT_DESC* inputElemsDesc, const size_t inputElemsDescSize)
    : mName(name)
      , mProjection(sizeof(Mat4))
      , mWorld(sizeof(Mat4))
      , mView(sizeof(Mat4))
      , mVertexShader(vsSize, vsBytecode)
      , mPixelShader(psSize, psBytecode)
      , mInputLayout(vsSize, vsBytecode, inputElemsDesc, inputElemsDescSize)
{
}

void Axiom::Shader::ActivateShader()
{
    mVertexShader.SetActive();
    mInputLayout.SetActive();
    mPixelShader.SetActive();
}

void Axiom::Shader::ActivateCBV()
{
    mWorld.SetActive(ConstantBufferSlot::World);
    mView.SetActive(ConstantBufferSlot::View);
    mProjection.SetActive(ConstantBufferSlot::Projection);
}

void Axiom::Shader::TransferWorldViewProj(Camera* camera, Mat4* worldMatrix)
{
    mWorld.Transfer(worldMatrix);
    mView.Transfer(&camera->GetViewMatrix());
    mProjection.Transfer(&camera->GetProjMatrix());
}

void Axiom::Shader::SetName(Name _name)
{
    this->mName = _name;
}

Axiom::Shader::Name Axiom::Shader::GetType() const
{
    return mName;
}

char* Axiom::Shader::GetName() const
{
    static char pTmp[128];
    strcpy_s(pTmp, 128, StringMe(this->mName));
    return pTmp;
}

const char* Axiom::Shader::GetLatestVertexShaderProfile()
{
    D3D_FEATURE_LEVEL featureLevel = DirectXDeviceMan::GetDevice()->GetFeatureLevel();

    switch (featureLevel)
    {
    case D3D_FEATURE_LEVEL_11_1:
    case D3D_FEATURE_LEVEL_11_0:
        {
            return "vs_5_0";
        }

    case D3D_FEATURE_LEVEL_10_1:
        {
            return "vs_4_1";
        }

    case D3D_FEATURE_LEVEL_10_0:
        {
            return "vs_4_0";
        }

    case D3D_FEATURE_LEVEL_9_3:
        {
            return "vs_4_0_level_9_3";
        }

    case D3D_FEATURE_LEVEL_9_2:
    case D3D_FEATURE_LEVEL_9_1:
        {
            return "vs_4_0_level_9_1";
        }

    default:
        assert(false);
    }

    return "";
}

const char* Axiom::Shader::GetLatestPixelShaderProfile()
{
    D3D_FEATURE_LEVEL featureLevel = DirectXDeviceMan::GetDevice()->GetFeatureLevel();
    switch (featureLevel)
    {
    case D3D_FEATURE_LEVEL_11_1:
    case D3D_FEATURE_LEVEL_11_0:
        {
            return "ps_5_0";
        }
    case D3D_FEATURE_LEVEL_10_1:
        {
            return "ps_4_1";
        }
    case D3D_FEATURE_LEVEL_10_0:
        {
            return "ps_4_0";
        }
    case D3D_FEATURE_LEVEL_9_3:
        {
            return "ps_4_0_level_9_3";
        }
    case D3D_FEATURE_LEVEL_9_2:
    case D3D_FEATURE_LEVEL_9_1:
        {
            return "ps_4_0_level_9_1";
        }
    default: ;
    }
    return "";
}
