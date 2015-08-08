#include "DX10Renderer.h"

// Creation and Deletion

CDX10Renderer::CDX10Renderer()
{
	// Window Variables
	m_hWnd = 0;
	m_fullScreen = false;

	// DX10 Variables
	m_pDX10Device = 0;
	m_pDX10SwapChain = 0;
	m_pRenderTargetView = 0;

}

CDX10Renderer::~CDX10Renderer()
{
}

bool CDX10Renderer::Initialise(int _windowWidth, int _windowHeight, HWND _hWND)
{
	// Save Windows Variables
	m_hWnd = _hWND;
	m_windowWidth = _windowWidth;
	m_windowHeight = _windowHeight;

	// Create the Device and Swap chain 
	VALIDATE(InitialiseDeviceAndSwapChain());

	// Set Clear Color
	m_clearColor = Color::MAGENTA;

	// Return the Succesful Initialization 
	return true;
}

void CDX10Renderer::ShutDown()
{
	ReleaseCOM(m_pRenderTargetView);
	ReleaseCOM(m_pDX10SwapChain);
	ReleaseCOM(m_pDX10Device);
}

// Renderer Functionality

bool CDX10Renderer::InitialiseDeviceAndSwapChain()
{
	// Set Driver Type to Hardware (HAL)
	m_DX10DriverType = D3D10_DRIVER_TYPE_HARDWARE;

	// Fill out the DXGI Swap Chain parameters
	DXGI_SWAP_CHAIN_DESC swapDesc;
	swapDesc.BufferDesc.Width = m_windowWidth; 
	swapDesc.BufferDesc.Height = m_windowHeight;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	swapDesc.SampleDesc.Count = 1;		// Set No multisampling per pixel ( 1 sample only)
	swapDesc.SampleDesc.Quality = 0;	// Set to low Quality
	
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = m_hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	// Add Debug Info to the flags when run in Debug mode
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	// Create the Device and Swap Chain and Validate it
	VALIDATE(SUCCEEDED(D3D10CreateDeviceAndSwapChain(	0,                 // Use default adapter
														m_DX10DriverType,
														0,                 // no software device
														createDeviceFlags,
														D3D10_SDK_VERSION,
														&swapDesc,
														&m_pDX10SwapChain,
														&m_pDX10Device)));
	

	// Run onResize For initail creation of window // TO DO
	onResize();

	// Return the Succesful Initialization 
	return true;
}

void CDX10Renderer::onResize()
{
	// Release the Render Target View  so it can be recreated 
	ReleaseCOM(m_pRenderTargetView);

	// Resize the buffers on the Swap Chain and create the new render target view
	m_pDX10SwapChain->ResizeBuffers(1, m_windowWidth, m_windowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	// Create a temporary Back buffer
	ID3D10Texture2D* pTempBackBuffer;

	// Retrieve the Temp Back Buffer of the Swap Chain and create a Render Target View using the Temp Back Buffer
	m_pDX10SwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pTempBackBuffer));
	m_pDX10Device->CreateRenderTargetView(pTempBackBuffer, 0, &m_pRenderTargetView);

	// Release the temporary Back Buffer
	ReleaseCOM(pTempBackBuffer);

	// Bind the Render Target View to the output-merger stage of the pipeline
	m_pDX10Device->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	// Set the View Port for the Device
	D3D10_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = m_windowWidth;
	viewPort.Height = m_windowHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	// Binds the View port to the Rasterizer stage of the pipeline
	m_pDX10Device->RSSetViewports(1, &viewPort);
}


void CDX10Renderer::RenderFrame()
{
	// Color the entire Back Buffer (the Render Target View) with the Renderers clear color
	m_pDX10Device->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);

	// Present the Back Buffer with no synchronization
	m_pDX10SwapChain->Present(0, 0);
}

void CDX10Renderer::ToggleFullscreen()
{
	m_fullScreen = !m_fullScreen;
	m_pDX10SwapChain->SetFullscreenState(m_fullScreen, NULL);
}
