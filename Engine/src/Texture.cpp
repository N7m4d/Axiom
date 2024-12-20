#include "Texture.h"
#include "DirectXTex.h"
#include "DirectXDeviceMan.h"
#include "ShaderMappings.h"

Axiom::Texture::Texture(LPCWSTR filepath, D3D11_FILTER filter)
    : mName(Name::Uninitialized)
      , mSrv(nullptr)
      , mSamplerState(nullptr)
      , mRefCount(0)
      , mWidth(0)
      , mHeight(0)
      , mAlphaEnabled(false)
{
    DirectX::ScratchImage testTexture;
    HRESULT hr = LoadFromTGAFile(filepath, nullptr, testTexture);
    assert(SUCCEEDED(hr));

    CreateShaderResourceView(DirectXDeviceMan::GetDevice(), testTexture.GetImage(0, 0, 0), testTexture.GetImageCount(),
                             testTexture.GetMetadata(), &mSrv);
    assert(mSrv);

    D3D11_SAMPLER_DESC desc{};
    desc.Filter = filter;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = DirectXDeviceMan::GetDevice()->CreateSamplerState(&desc, &mSamplerState);
    assert(SUCCEEDED(hr));
    assert(mSamplerState);
}

Axiom::Texture::~Texture()
{
    SafeRelease(mSrv);
    SafeRelease(mSamplerState);
}

void Axiom::Texture::ActivateTexture()
{
    DirectXDeviceMan::GetContext()->PSSetShaderResources(static_cast<uint32_t>(ShaderResourceBufferSlot::TexA), 1,
                                                         &mSrv);
    DirectXDeviceMan::GetContext()->
        PSSetSamplers(static_cast<uint32_t>(ShaderSamplerSlot::SampleA), 1, &mSamplerState);
}

bool Axiom::Texture::HasAlpha() const
{
    return this->mAlphaEnabled;
}

char* Axiom::Texture::GetName()
{
    return nullptr;
}

void Axiom::Texture::SetName(Name name)
{
    mName = name;
}

int Axiom::Texture::GetRefCount() const
{
    return mRefCount;
}

void Axiom::Texture::IncreaseRefCount()
{
    mRefCount++;
}

void Axiom::Texture::DecreaseRefCount()
{
    mRefCount--;

    if (mRefCount == 0)
    {
        delete this;
    }
}
