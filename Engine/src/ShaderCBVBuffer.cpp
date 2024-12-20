#include "ShaderCBVBuffer.h"
#include "DirectXDeviceMan.h"

namespace Axiom
{
    ShaderCBVBuffer::ShaderCBVBuffer(size_t structSize)
        : mStructSize(structSize),
          mShaderCBVBuffer(nullptr),
          mCreate(false)
    {
        this->privCreate(structSize);
    }

    void ShaderCBVBuffer::privCreate(size_t structSize)
    {
        assert(mCreate == false);
        mCreate = true;

        mStructSize = structSize;
        assert(mStructSize > 0);

        D3D11_BUFFER_DESC desc;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.ByteWidth = mStructSize;
        desc.CPUAccessFlags = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&desc, nullptr, &mShaderCBVBuffer);
        AZUL_UNUSED_VAR(hr);
        assert(SUCCEEDED(hr));
        assert(this->mShaderCBVBuffer);
    }

    void ShaderCBVBuffer::Transfer(const void* buffer) const
    {
        assert(mCreate == true);
        assert(buffer);

        DirectXDeviceMan::GetContext()->UpdateSubresource(mShaderCBVBuffer, 0, nullptr, buffer, 0, 0);
    }

    void ShaderCBVBuffer::SetActive(ConstantBufferSlot slot)
    {
        DirectXDeviceMan::GetContext()->VSSetConstantBuffers(static_cast<uint32_t>(slot), 1, &mShaderCBVBuffer);
    }

    ShaderCBVBuffer::~ShaderCBVBuffer()
    {
        SafeRelease(this->mShaderCBVBuffer)
    }
}
