#include "Buffer.h"
#include "DirectXDeviceMan.h"

Axiom::Buffer::Buffer(const size_t numBytes, const size_t strideSize, const void* initData)
    : mNumBytes(numBytes)
      , mStrideSize(strideSize)
      , mOffset(0)
      , mD3dBuffer(nullptr)
      , mCreate(false)
{
    assert(mCreate == false);
    mCreate = true;

    assert(initData);

    // Create and initialize the vertex buffer.
    D3D11_BUFFER_DESC vertexBufferDesc{};
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.ByteWidth = mNumBytes;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    D3D11_SUBRESOURCE_DATA resourceData{};
    resourceData.pSysMem = initData;

    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&vertexBufferDesc, &resourceData, &mD3dBuffer);

    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);
}

Axiom::Buffer::~Buffer()
{
    SafeRelease(mD3dBuffer)
}

void Axiom::Buffer::SetActive(VertexSlot slot) const
{
    DirectXDeviceMan::GetContext()->IASetVertexBuffers(static_cast<uint32_t>(slot), 1, &mD3dBuffer, &mStrideSize,
                                                       &mOffset);
}
