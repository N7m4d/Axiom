#ifndef ENGINE_H
#define ENGINE_H

#include <d3d11.h>

#define SafeRelease(x) { if(x){ x->Release(); x = 0; } }

namespace Axiom
{
    class Engine
    {
    public:
        static const BOOL g_EnableVSync = true;

        Engine(const char* name, int width, int height);

        Engine() = delete;
        Engine(const Engine&) = delete;
        Engine& operator =(const Engine&) = delete;
        virtual ~Engine() = default;


        virtual bool LoadContent() = 0;
        virtual void UnloadContent() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;
        virtual void ClearDepthStencilBuffer() = 0;

        void Cleanup();

        int InitApplication(HINSTANCE hInstance, int cmdShow);
        int InitDirectX(HINSTANCE hInstance, BOOL vSync);
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow);

        void Present(bool vSync);
        DXGI_RATIONAL QueryRefreshRate(UINT screenWidth, UINT screenHeight, BOOL vsync);
        int Run();

        HWND g_WindowHandle;

        // Direct3D device and swap chain.
        ID3D11Device* g_d3dDevice;
        ID3D11DeviceContext* g_d3dDeviceContext;
        IDXGISwapChain* g_d3dSwapChain;

        // Render target view for the back buffer of the swap chain.
        ID3D11RenderTargetView* g_d3dRenderTargetView;
        // Depth/stencil view for use as a depth buffer.
        ID3D11DepthStencilView* g_d3dDepthStencilView;
        // A texture to associate to the depth stencil view.
        ID3D11Texture2D* g_d3dDepthStencilBuffer;

        // Define the functionality of the depth/stencil stages.
        ID3D11DepthStencilState* g_d3dDepthStencilState;
        // Define the functionality of the rasterizer stage.
        ID3D11RasterizerState* g_d3dRasterizerState;
        D3D11_VIEWPORT g_Viewport;

        const char* mName;
        const int mWindowWidth;
        const int mWindowHeight;
    };
}


#endif
