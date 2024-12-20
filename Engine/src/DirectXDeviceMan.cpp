#include "DirectXDeviceMan.h"

namespace Axiom
{
    DirectXDeviceMan* DirectXDeviceMan::mInstance = nullptr;

    void DirectXDeviceMan::Create(ID3D11Device* device, ID3D11DeviceContext* context)
    {
        assert(device);
        assert(context);
        assert(mInstance == nullptr);

        if (mInstance == nullptr)
        {
            mInstance = new DirectXDeviceMan(device, context);
        }
    }

    ID3D11Device* DirectXDeviceMan::GetDevice()
    {
        DirectXDeviceMan* man = GetInstance();
        assert(man);

        return man->mDevice;
    }

    ID3D11DeviceContext* DirectXDeviceMan::GetContext()
    {
        DirectXDeviceMan* man = GetInstance();
        assert(man);

        return man->mContext;
    }

    void DirectXDeviceMan::Destroy()
    {
        delete mInstance;
    }

    DirectXDeviceMan::DirectXDeviceMan(ID3D11Device* device, ID3D11DeviceContext* context)
    {
        mDevice = device;
        mContext = context;
    }

    DirectXDeviceMan::~DirectXDeviceMan()
    {
    }

    DirectXDeviceMan* DirectXDeviceMan::GetInstance()
    {
        // Safety - this forces users to call Create() first before using class
        assert(mInstance != nullptr);
        return mInstance;
    }
}
