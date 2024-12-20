#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include <d3d11.h>

namespace Axiom
{
    class InputLayout
    {
    public:
        InputLayout() = default;
        InputLayout(const InputLayout& r) = delete;
        InputLayout& operator=(const InputLayout&) = delete;
        ~InputLayout();

        InputLayout(size_t numBytes, const void* initData, D3D11_INPUT_ELEMENT_DESC* desc, unsigned int descSize);

        void SetActive() const;

        size_t mCodeSize;
        ID3D11InputLayout* mD3dInputLayout;
        D3D11_INPUT_ELEMENT_DESC* mDesc;
        unsigned int mDescSize;
        bool mCreate;
    };
}

#endif
