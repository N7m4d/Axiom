#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include <d3d11.h>

namespace Axiom
{
    class PixelShader
    {
    public:
        PixelShader() = delete;
        PixelShader(const PixelShader& r) = delete;
        PixelShader& operator=(const PixelShader&) = delete;

        PixelShader(size_t numBytes, const void* initData);
        ~PixelShader();

        void SetActive() const;

        size_t mCodeSize;
        ID3D11PixelShader* mD3dPixelShader;
        bool mCreate;
    };
}

#endif
