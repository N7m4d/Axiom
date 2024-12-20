#include "IndexBuffer.h"

#include "DirectXDeviceMan.h"

Axiom::IndexBuffer::IndexBuffer(const size_t numBytes, const void* initData)
    : mD3dBuffer(nullptr)
      , mCreate(false)
{
    Init(numBytes, initData);
}

Axiom::IndexBuffer::~IndexBuffer()
{
    SafeRelease(mD3dBuffer)
}

void Axiom::IndexBuffer::Init(const size_t numBytes, const void* initData)
{
    assert(mCreate == false);
    mCreate = true;

    mNumBytes = numBytes;

    assert(initData);

    D3D11_BUFFER_DESC desc = {};
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.ByteWidth = mNumBytes;
    desc.CPUAccessFlags = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;

    D3D11_SUBRESOURCE_DATA resourceData{};
    resourceData.pSysMem = initData;

    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&desc,
                                                                   &resourceData,
                                                                   &mD3dBuffer);

    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);
}

void Axiom::IndexBuffer::SetActive() const
{
    DirectXDeviceMan::GetContext()->IASetIndexBuffer(mD3dBuffer, DXGI_FORMAT_R32_UINT, 0);
}
