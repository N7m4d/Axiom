#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <d3d11.h>

namespace Axiom
{
    class VertexShader
    {
    public:
        VertexShader() = delete;
        VertexShader(const VertexShader& r) = delete;
        VertexShader& operator=(const VertexShader&) = delete;
        ~VertexShader();

        VertexShader(size_t numBytes, const void* initData);

        void SetActive() const;

        size_t mCodeSize;
        ID3D11VertexShader* mD3dVertexShader;
        bool mCreate;
    };
}

#endif
