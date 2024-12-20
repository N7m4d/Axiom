#include "PixelShader.h"

#include "DirectXDeviceMan.h"
#include "Shader.h"

Axiom::PixelShader::PixelShader(const size_t numBytes, const void* initData)
    : mCodeSize(numBytes)
      , mD3dPixelShader(nullptr)
      , mCreate(false)
{
    assert(mCreate == false);
    mCreate = true;

    assert(initData);

    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreatePixelShader(initData, mCodeSize, nullptr, &mD3dPixelShader);
    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);

    assert(std::string("ps_5_0") == (Shader::GetLatestPixelShaderProfile()));
}

Axiom::PixelShader::~PixelShader()
{
    SafeRelease(mD3dPixelShader)
}

void Axiom::PixelShader::SetActive() const
{
    DirectXDeviceMan::GetContext()->PSSetShader(mD3dPixelShader, nullptr, 0);
}
