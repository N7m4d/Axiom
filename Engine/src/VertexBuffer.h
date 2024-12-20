#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <d3d11.h>

#include "ShaderMappings.h"

namespace Axiom
{
    class VertexBuffer
    {
    public:
        VertexBuffer() = default;
        VertexBuffer(const VertexBuffer& r) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(size_t numBytes, size_t strideSize, const void* initData);
        ~VertexBuffer();

        void Init(size_t numBytes, size_t strideSize, const void* initData);
        void SetActive(VertexSlot slot) const;

        size_t mNumBytes{0};
        size_t mStrideSize{0};
        ID3D11Buffer* mD3dBuffer{nullptr};
        bool mCreate{false};
    };
}

#endif
