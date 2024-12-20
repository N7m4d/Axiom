#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <d3d11.h>

namespace Axiom
{
    class IndexBuffer
    {
    public:
        IndexBuffer() = default;
        IndexBuffer(const IndexBuffer& r) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(size_t numBytes, const void* initData);
        ~IndexBuffer();

        void Init(size_t numBytes, const void* initData);
        void SetActive() const;

        size_t mNumBytes;
        ID3D11Buffer* mD3dBuffer;
        bool mCreate;
    };
}

#endif
