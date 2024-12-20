#include "TextureProto.h"
#include "meshData.h"
#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectXTex.h"
#include "DirectXDeviceMan.h"

Axiom::TextureProto::TextureProto(textureData& textureProtoData, Name name, D3D11_FILTER filter)
    : mTex(nullptr)
{
    SetName(name);

    assert(strcmp(textureProtoData.pVersion, "2.0.0") == 0);

    HRESULT hr;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = textureProtoData.width;
    desc.Height = textureProtoData.height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;

    mWidth = textureProtoData.width;;
    mHeight = textureProtoData.height;;

    if (textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA
        || textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA)
    {
        mAlphaEnabled = true;
    }
    else
    {
        mAlphaEnabled = false;
    }

    assert((textureProtoData.textType == textureData::TEXTURE_TYPE::PNG)
        || (textureProtoData.textType == textureData::TEXTURE_TYPE::TGA));


    desc.Format = DXGI_FORMAT_UNKNOWN;

    if (textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB
        || textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA)
    {
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    }


    if (textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR
        || textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA)
    {
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    }

    assert(desc.Format != DXGI_FORMAT_UNKNOWN);


    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = textureProtoData.poData;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;

    hr = DirectXDeviceMan::GetDevice()->CreateTexture2D(&desc, &subResource, &mTex);

    if (SUCCEEDED(hr) && mTex != nullptr)
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

        srvDesc.Format = DXGI_FORMAT_UNKNOWN;

        if (textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB
            || textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA)
        {
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        }


        if (textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR
            || textureProtoData.nComponent == textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA)
        {
            srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        }

        assert(srvDesc.Format != DXGI_FORMAT_UNKNOWN);

        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        hr = DirectXDeviceMan::GetDevice()->CreateShaderResourceView(mTex, &srvDesc, &mSrv);
        assert(SUCCEEDED(hr));
    }
    else
    {
        assert(false);
    }

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = filter;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = DirectXDeviceMan::GetDevice()->CreateSamplerState(&sampDesc, &mSamplerState);
    assert(SUCCEEDED(hr));
}

Axiom::TextureProto::~TextureProto()
{
    SafeRelease(mTex);
}
