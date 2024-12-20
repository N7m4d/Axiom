#include <d3d11.h>
#include <d3dcompiler.h>

#include "Engine.h"
#include "AnimTimer.h"
#include "DirectXDeviceMan.h"

LPCSTR g_WindowClassName = "EngineWindowClass";

using namespace Axiom;

#if _DEBUG
#define createDeviceFlags_define  D3D11_CREATE_DEVICE_DEBUG

#else
#define createDeviceFlags_define  0
#endif

Engine::Engine(const char *_pName, int width, int height)
	: g_Viewport{0}, mName(_pName), mWindowWidth(width), mWindowHeight(height)
{
	g_WindowHandle = 0;
	// Direct3D device and swap chain.
	g_d3dDevice = nullptr;
	g_d3dDeviceContext = nullptr;
	g_d3dSwapChain = nullptr;

	// Render target view for the back buffer of the swap chain.
	g_d3dRenderTargetView = nullptr;
	// Depth/stencil view for use as a depth buffer.
	g_d3dDepthStencilView = nullptr;
	// A texture to associate to the depth stencil view.
	g_d3dDepthStencilBuffer = nullptr;

	// Define the functionality of the depth/stencil stages.
	g_d3dDepthStencilState = nullptr;
	// Define the functionality of the rasterizer stage.
	g_d3dRasterizerState = nullptr;
	g_Viewport = {0};

}
// --------------------------------------------------------------
//  Standard windows magic to setup the application window
// --------------------------------------------------------------
int Engine::InitApplication(HINSTANCE hInstance, int cmdShow)
{
	WNDCLASSEX wndClass = {0};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = this->WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = nullptr;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = g_WindowClassName;
	wndClass.hIconSm = nullptr;

	if(!RegisterClassEx(&wndClass))
	{
		return -1;
	}

	RECT windowRect = {0, 0, this->mWindowWidth, this->mWindowHeight};
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	g_WindowHandle = CreateWindowA(g_WindowClassName, this->mName,
								   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
								   windowRect.right - windowRect.left,
								   windowRect.bottom - windowRect.top,
								   nullptr, nullptr, hInstance, nullptr);

	assert(g_WindowHandle);

	ShowWindow(g_WindowHandle, cmdShow);
	UpdateWindow(g_WindowHandle);

	return 0;
}

// ------------------------------------------------------------
//  Initialize the Direct Device with Swap Chain
// ------------------------------------------------------------

int Engine::InitDirectX(HINSTANCE hInstance, BOOL vSync)
{
	AZUL_UNUSED_VAR(hInstance);
	// A window handle must have been created already.
	assert(g_WindowHandle != nullptr);

	RECT clientRect;
	GetClientRect(g_WindowHandle, &clientRect);

	// Compute the exact client dimensions. This will be used
	// to initialize the render targets for our swap chain.
	unsigned int clientWidth = clientRect.right - clientRect.left;
	unsigned int clientHeight = clientRect.bottom - clientRect.top;

	DXGI_SWAP_CHAIN_DESC swapChainDesc{0};

	// two buffers (front + back)
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = clientWidth;
	swapChainDesc.BufferDesc.Height = clientHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// gets the refresh rate of the monitor (60Hz unless you have a crazy fast monitor)
	swapChainDesc.BufferDesc.RefreshRate = QueryRefreshRate(clientWidth, clientHeight, vSync);
	// Use the surface or resource as an output render target.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// output window (in window mode its the front buffer)
	swapChainDesc.OutputWindow = g_WindowHandle;
	// multisample setup
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	// get drop the backbuffer after flip
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	// sub window of screen
	swapChainDesc.Windowed = TRUE;

	UINT createDeviceFlags = createDeviceFlags_define;

	// These are the feature levels that we will accept.
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// This will be the feature level that 
	// is used to create our device and swap chain.
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,
											   D3D_DRIVER_TYPE_HARDWARE,
											   nullptr,
											   createDeviceFlags,
											   featureLevels,
											   _countof(featureLevels),
											   D3D11_SDK_VERSION,
											   &swapChainDesc,
											   &g_d3dSwapChain,
											   &g_d3dDevice,
											   &featureLevel,
											   &g_d3dDeviceContext);

	assert(SUCCEEDED(hr));

	DirectXDeviceMan::Create(g_d3dDevice, g_d3dDeviceContext);

	// The Direct3D device and swap chain were successfully created.
	// Now we need to initialize the buffers of the swap chain.
	// Next initialize the back buffer of the swap chain and associate it to a 
	// render target view.
	ID3D11Texture2D *backBuffer = nullptr;
	hr = g_d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBuffer);
	assert(SUCCEEDED(hr));

	hr = g_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &g_d3dRenderTargetView);
	assert(SUCCEEDED(hr));

	SafeRelease(backBuffer);

	// Create the depth buffer for use with the depth/stencil view.
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc{0};

	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0; // No CPU access required.
	// 24-bit depth/8-bit stencil --> future make it 32 bit depth
	depthStencilBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilBufferDesc.Width = clientWidth;
	depthStencilBufferDesc.Height = clientHeight;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	hr = g_d3dDevice->CreateTexture2D(&depthStencilBufferDesc, nullptr, &g_d3dDepthStencilBuffer);
	assert(SUCCEEDED(hr));

	hr = g_d3dDevice->CreateDepthStencilView(g_d3dDepthStencilBuffer, nullptr, &g_d3dDepthStencilView);
	assert(SUCCEEDED(hr));

	// Setup depth/stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc{0};

	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	// not using any stencil... its disabled
	depthStencilStateDesc.StencilEnable = FALSE;

	hr = g_d3dDevice->CreateDepthStencilState(&depthStencilStateDesc, &g_d3dDepthStencilState);

	// Setup rasterizer state.
	D3D11_RASTERIZER_DESC rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.AntialiasedLineEnable = FALSE;
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;

	// To Do add scissor rectangle... its faster
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state object.
	hr = g_d3dDevice->CreateRasterizerState(&rasterizerDesc, &g_d3dRasterizerState);
	assert(SUCCEEDED(hr));

	// Initialize the viewport to occupy the entire client area.
	g_Viewport.Width = static_cast<float>(clientWidth);
	g_Viewport.Height = static_cast<float>(clientHeight);
	g_Viewport.TopLeftX = 0.0f;
	g_Viewport.TopLeftY = 0.0f;
	g_Viewport.MinDepth = 0.0f;
	g_Viewport.MaxDepth = 1.0f;

	return 0;
}

// ------------------------------------
// win main()
// ------------------------------------
int WINAPI Engine::wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	AZUL_UNUSED_VAR(prevInstance);
	AZUL_UNUSED_VAR(cmdLine);

	if(InitApplication(hInstance, cmdShow) != 0)
	{
		MessageBox(nullptr, TEXT("Failed to create applicaiton window."), TEXT("Error"), MB_OK);
		return -1;
	}

	if(InitDirectX(hInstance, g_EnableVSync) != 0)
	{
		MessageBox(nullptr, TEXT("Failed to create DirectX device and swap chain."), TEXT("Error"), MB_OK);
		return -1;
	}

	int returnCode = Run();

	return returnCode;
}

// ------------------------------------
// windows process - messages
// ------------------------------------
LRESULT CALLBACK Engine::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch(message)
	{
	case WM_PAINT:
	{
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
	}
	break;

	case WM_CHAR:
	{
		if(wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

// ------------------------------------------------------
// Find Refresh rate:
// http://www.rastertek.com/dx11tut03.html
// ------------------------------------------------------
DXGI_RATIONAL Engine::QueryRefreshRate(UINT screenWidth, UINT screenHeight, BOOL vsync)
{
	DXGI_RATIONAL refreshRate = {0, 1};
	if(vsync)
	{
		IDXGIFactory *factory = nullptr;
		IDXGIAdapter *adapter;
		IDXGIOutput *adapterOutput;
		DXGI_MODE_DESC *displayModeList;

		// Create a DirectX graphics interface factory.
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&factory);
		if(FAILED(hr))
		{
			MessageBox(0,
					   TEXT("Could not create DXGIFactory instance."),
					   TEXT("Query Refresh Rate"),
					   MB_OK);

			throw new std::exception("Failed to create DXGIFactory.");
		}

		hr = factory->EnumAdapters(0, &adapter);
		if(FAILED(hr))
		{
			MessageBox(0,
					   TEXT("Failed to enumerate adapters."),
					   TEXT("Query Refresh Rate"),
					   MB_OK);

			throw new std::exception("Failed to enumerate adapters.");
		}

		hr = adapter->EnumOutputs(0, &adapterOutput);
		if(FAILED(hr))
		{
			MessageBox(0,
					   TEXT("Failed to enumerate adapter outputs."),
					   TEXT("Query Refresh Rate"),
					   MB_OK);

			throw new std::exception("Failed to enumerate adapter outputs.");
		}

		UINT numDisplayModes;
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numDisplayModes, nullptr);
		if(FAILED(hr))
		{
			MessageBox(0,
					   TEXT("Failed to query display mode list."),
					   TEXT("Query Refresh Rate"),
					   MB_OK);

			throw new std::exception("Failed to query display mode list.");
		}

		displayModeList = new DXGI_MODE_DESC[numDisplayModes];
		assert(displayModeList);

		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numDisplayModes, displayModeList);
		if(FAILED(hr))
		{
			MessageBox(0,
					   TEXT("Failed to query display mode list."),
					   TEXT("Query Refresh Rate"),
					   MB_OK);

			throw new std::exception("Failed to query display mode list.");
		}

		// Now store the refresh rate of the monitor that matches the width and height of the requested screen.
		for(UINT i = 0; i < numDisplayModes; ++i)
		{
			if(displayModeList[i].Width == screenWidth && displayModeList[i].Height == screenHeight)
			{
				refreshRate = displayModeList[i].RefreshRate;
			}
		}

		delete[] displayModeList;
		SafeRelease(adapterOutput)
		SafeRelease(adapter)
		SafeRelease(factory)
	}

	return refreshRate;
}

// ------------------------------------
// Run - main loop
// ------------------------------------
int Engine::Run()
{
	MSG msg = {0};

	static DWORD previousTime = timeGetTime();
	static const float targetFramerate = 30.0f;
	static const float maxTimeStep = 1.0f / targetFramerate;

	AnimTimer EngineTime;

	if(!LoadContent())
	{
		MessageBox(nullptr, TEXT("Failed to load content."), TEXT("Error"), MB_OK);
		return -1;
	}

	while(msg.message != WM_QUIT)
	{
		EngineTime.Tic();

		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD currentTime = timeGetTime();
			float deltaTime = (currentTime - previousTime) / 1000.0f;
			previousTime = currentTime;

			// Cap the delta time to the max time step (useful if your 
			// debugging and you don't want the deltaTime value to explode.
			deltaTime = std::min<float>(deltaTime, maxTimeStep);

			Update(deltaTime);
			ClearDepthStencilBuffer();
			Render();

			//--------------------------------
			// Fast monitor sync
			//--------------------------------
			{
				AnimTime EngineLoopTime = EngineTime.Toc();

				// Current number of Frames... snap to the next 60Hz frame as target
				int NumFrames_60Hz = AnimTime::Quotient(EngineLoopTime, AnimTime(AnimTime::Duration::NTSC_FRAME));
				int TargetNumFrames_60Hz = NumFrames_60Hz + 1;
				AnimTime Target_60Hz = TargetNumFrames_60Hz * AnimTime(AnimTime::Duration::NTSC_FRAME);

				// we are before the flip... give a little cushion 
				AnimTime Overhead_Time = 500 * AnimTime(AnimTime::Duration::ONE_MICROSECOND);
				AnimTime EndTime = Target_60Hz - Overhead_Time;

				// Sit and spin.
				while(EngineLoopTime < EndTime)
				{
					EngineLoopTime = EngineTime.Toc();
				}
			}

			//--------------------------------------------------------
			// Wait for Vsync - flip front/back buffers
			//--------------------------------------------------------
			Present(g_EnableVSync);
		}
	}

	UnloadContent();
	Cleanup();

	return static_cast<int>(msg.wParam);
}

// ------------------------------------
// present - flip
// ------------------------------------
void Engine::Present(bool vSync)
{
	if(vSync)
	{
		g_d3dSwapChain->Present(1, 0);
	}
	else
	{
		g_d3dSwapChain->Present(0, 0);
	}
}

// ------------------------------------
// Cleanup()
// ------------------------------------
void Engine::Cleanup()
{
	SafeRelease(g_d3dDepthStencilView)
	SafeRelease(g_d3dRenderTargetView)
	SafeRelease(g_d3dDepthStencilBuffer)
	SafeRelease(g_d3dDepthStencilState)
	SafeRelease(g_d3dRasterizerState)
	SafeRelease(g_d3dSwapChain)
	SafeRelease(g_d3dDeviceContext)

#ifdef _DEBUG

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug *debugDev = nullptr;
	HRESULT hr = g_d3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	AZUL_UNUSED_VAR(hr);

	//debugDev->ReportLiveDeviceObjects(D3D11_RLDO_IGNORE_INTERNAL);
	//debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	//debugDev->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
	SafeRelease(debugDev)
	
#endif

	SafeRelease(g_d3dDevice)
}
