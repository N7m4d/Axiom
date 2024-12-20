#include "ConstantBuffer.h"
#include "DirectXDeviceMan.h"

Axiom::ConstantBuffer::ConstantBuffer(const size_t structSize)
    : mStructSize(structSize)
      , mD3dBuffer(nullptr)
      , mCreate(false)
{
    assert(mCreate == false);
    mCreate = true;

    mStructSize = structSize;
    assert(structSize > 0);

    D3D11_BUFFER_DESC desc{};
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = mStructSize;
    desc.Usage = D3D11_USAGE_DEFAULT;

    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&desc, nullptr, &mD3dBuffer);
    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);
}

Axiom::ConstantBuffer::~ConstantBuffer()
{
    SafeRelease(mD3dBuffer)
}

void Axiom::ConstantBuffer::Transfer(const void* data) const
{
    assert(mCreate == true);
    assert(data);

    DirectXDeviceMan::GetContext()->UpdateSubresource(mD3dBuffer, 0, nullptr, data, 0, 0);
}

void Axiom::ConstantBuffer::SetActive(ConstantBufferSlot slot) const
{
    DirectXDeviceMan::GetContext()->VSSetConstantBuffers(static_cast<uint32_t>(slot), 1, &mD3dBuffer);
}
