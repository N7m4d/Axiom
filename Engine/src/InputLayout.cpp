#include "InputLayout.h"
#include "DirectXDeviceMan.h"

Axiom::InputLayout::InputLayout(const size_t numBytes, const void* initData, D3D11_INPUT_ELEMENT_DESC* desc,
                                const unsigned int descSize)
    : mCodeSize(numBytes)
      , mD3dInputLayout(nullptr)
      , mDesc(desc)
      , mDescSize(descSize)
      , mCreate(false)
{
    assert(mCreate == false);
    mCreate = true;

    assert(initData);
    assert(desc);

    const HRESULT hr = DirectXDeviceMan::GetDevice()->CreateInputLayout(mDesc,
                                                                        mDescSize / sizeof(D3D11_INPUT_ELEMENT_DESC),
                                                                        initData,
                                                                        mCodeSize,
                                                                        &mD3dInputLayout);

    assert(SUCCEEDED(hr));

    AZUL_UNUSED_VAR(hr);
}

Axiom::InputLayout::~InputLayout()
{
    SafeRelease(mD3dInputLayout)
}

void Axiom::InputLayout::SetActive() const
{
    DirectXDeviceMan::GetContext()->IASetInputLayout(mD3dInputLayout);
}
