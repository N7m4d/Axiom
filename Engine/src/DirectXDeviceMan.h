#ifndef DIRECT_X_DEVICE_MAN_H
#define DIRECT_X_DEVICE_MAN_H

#include <d3d11.h>

#define SafeRelease(x) { if(x){ x->Release(); x = 0; } }

namespace Axiom
{
    class DirectXDeviceMan
    {
    public:
        static void Create(ID3D11Device* device, ID3D11DeviceContext* context);
        static void Destroy();

        static ID3D11Device* GetDevice();
        static ID3D11DeviceContext* GetContext();

        ~DirectXDeviceMan();

    private:
        static DirectXDeviceMan* GetInstance();

        DirectXDeviceMan() = delete;
        DirectXDeviceMan(const DirectXDeviceMan&) = delete;
        DirectXDeviceMan& operator =(const DirectXDeviceMan&) = delete;

        DirectXDeviceMan(ID3D11Device* device, ID3D11DeviceContext* context);

        static DirectXDeviceMan* mInstance;
        ID3D11Device* mDevice;
        ID3D11DeviceContext* mContext;
    };
}

#endif
