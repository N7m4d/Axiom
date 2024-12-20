#include "VertexBuffer.h"

#include "DirectXDeviceMan.h"

Axiom::VertexBuffer::VertexBuffer(const size_t numBytes, const size_t strideSize, const void* initData)
{
    Init(numBytes, strideSize, initData);
}

Axiom::VertexBuffer::~VertexBuffer()
{
    SafeRelease(mD3dBuffer)
}

void Axiom::VertexBuffer::Init(const size_t numBytes, const size_t strideSize, const void* initData)
{
    assert(mCreate == false);
    mCreate = true;

    mNumBytes = numBytes;
    mStrideSize = strideSize;

    assert(initData);

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

void Axiom::VertexBuffer::SetActive(const VertexSlot slot) const
{
    constexpr unsigned int offset = 0;
    DirectXDeviceMan::GetContext()->IASetVertexBuffers(static_cast<uint32_t>(slot), 1, &mD3dBuffer, &mStrideSize,
                                                       &offset);
}
