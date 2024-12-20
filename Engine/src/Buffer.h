#ifndef BUFFER_H
#define BUFFER_H

#include <d3d11.h>
#include "ShaderMappings.h"

namespace Axiom
{
    class Buffer
    {
    public:
        Buffer(const Buffer& r) = delete;
        Buffer& operator=(const Buffer&) = delete;

        Buffer(size_t numBytes, size_t strideSize, const void* initData);
        virtual ~Buffer();

        void SetActive(VertexSlot slot) const;

        size_t mNumBytes;
        size_t mStrideSize;
        size_t mOffset;
        ID3D11Buffer* mD3dBuffer;
        bool mCreate;
    };
}

#endif
