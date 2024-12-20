#include "VertexShader.h"

#include "DirectXDeviceMan.h"
#include "Shader.h"

Axiom::VertexShader::VertexShader(const size_t numBytes, const void* initData)
    : mCodeSize(numBytes)
      , mD3dVertexShader(nullptr)
      , mCreate(false)
{
    assert(mCreate == false);

    assert(initData);

    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateVertexShader(
        initData, mCodeSize, nullptr, &mD3dVertexShader);
    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);

    assert(std::string("vs_5_0") == Shader::GetLatestVertexShaderProfile());
}

void Axiom::VertexShader::SetActive() const
{
    DirectXDeviceMan::GetContext()->VSSetShader(mD3dVertexShader, nullptr, 0);
}

Axiom::VertexShader::~VertexShader()
{
    SafeRelease(mD3dVertexShader)
}
