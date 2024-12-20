#include <d3d11.h>

#include "Game.h"

extern unsigned int NumIndices;

void Axiom::Game::SetDefaultTargetMode()
{
	assert(g_d3dDevice);
	assert(g_d3dDeviceContext);
	//--------------------------------------------------------
	// Set (point to ) the Rasterizers functions to be used
	//--------------------------------------------------------
	g_d3dDeviceContext->RSSetState(g_d3dRasterizerState);

	//--------------------------------------------------------
	// Set (point to ) the Viewport to be used
	//--------------------------------------------------------
	g_d3dDeviceContext->RSSetViewports(1, &g_Viewport);

	//--------------------------------------------------------
	// Set (point to ) render target
	//      Only one Target, this maps to Pixel shader
	// --------------------------------------------------------
	g_d3dDeviceContext->OMSetRenderTargets(1, &g_d3dRenderTargetView, g_d3dDepthStencilView);

	//--------------------------------------------------------
	// Set (point to ) the Depth functions to be used
	//--------------------------------------------------------
	g_d3dDeviceContext->OMSetDepthStencilState(g_d3dDepthStencilState, 1);
}

float Axiom::Game::GetAspectRatio() const
{
	RECT clientRect;
	GetClientRect(g_WindowHandle, &clientRect);

	// Compute the exact client dimensions.
	// This is required for a correct projection matrix.
	float clientWidth = static_cast<float>(clientRect.right - clientRect.left);
	float clientHeight = static_cast<float>(clientRect.bottom - clientRect.top);

	float ratio = clientWidth / clientHeight;

	return ratio;
}
