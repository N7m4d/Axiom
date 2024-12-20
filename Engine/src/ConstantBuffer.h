#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include <d3d11.h>
#include "ShaderMappings.h"

namespace Axiom
{
    class ConstantBuffer
    {
    public:
        ConstantBuffer() = delete;
        ConstantBuffer(const ConstantBuffer& r) = delete;
        ConstantBuffer& operator=(const ConstantBuffer&) = delete;

        ConstantBuffer(size_t structSize);
        ~ConstantBuffer();

        void Transfer(const void* data) const;
        void SetActive(ConstantBufferSlot slot) const;

        size_t mStructSize;
        ID3D11Buffer* mD3dBuffer;
        bool mCreate;
    };
}

#endif
