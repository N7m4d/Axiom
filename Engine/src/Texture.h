#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>

namespace Axiom
{
    class Texture
    {
    public:
        enum class Name
        {
            NullTexture,
            Duckweed,
            BrownBrick,
            RedBrick,
            WhiteTile,
            Uninitialized,
            SpaceFrigate,
            R2D2,
            WatchTower,
            ChickenBot
        };

        Texture() = default;
        Texture(const Texture&) = delete;
        Texture& operator =(const Texture&) = delete;
        virtual ~Texture();

        Texture(LPCWSTR filepath, D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

        void ActivateTexture();

        bool HasAlpha() const;

        char* GetName();
        void SetName(Name name);

        int GetRefCount() const;
        void IncreaseRefCount();
        void DecreaseRefCount();

        Name mName;

        ID3D11ShaderResourceView* mSrv;
        ID3D11SamplerState* mSamplerState;

        int mRefCount;

        unsigned int mWidth;
        unsigned int mHeight;
        bool mAlphaEnabled;
    };
}

#endif
