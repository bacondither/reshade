#pragma once

#include "d3d9.hpp"

struct Direct3DSwapChain9 : IDirect3DSwapChain9Ex
{
	Direct3DSwapChain9(Direct3DDevice9 *device, IDirect3DSwapChain9   *original, const std::shared_ptr<reshade::d3d9_runtime> &runtime) : _ref(1), _orig(original), _interface_version(0), _device(device), _runtime(runtime) { }
	Direct3DSwapChain9(Direct3DDevice9 *device, IDirect3DSwapChain9Ex *original, const std::shared_ptr<reshade::d3d9_runtime> &runtime) : _ref(1), _orig(original), _interface_version(1), _device(device), _runtime(runtime) { }

	#pragma region IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObj) override;
	virtual ULONG STDMETHODCALLTYPE AddRef() override;
	virtual ULONG STDMETHODCALLTYPE Release() override;
	#pragma endregion
	#pragma region IDirect3DSwapChain9
	virtual HRESULT STDMETHODCALLTYPE Present(CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion, DWORD dwFlags) override;
	virtual HRESULT STDMETHODCALLTYPE GetFrontBufferData(IDirect3DSurface9 *pDestSurface) override;
	virtual HRESULT STDMETHODCALLTYPE GetBackBuffer(UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 **ppBackBuffer) override;
	virtual HRESULT STDMETHODCALLTYPE GetRasterStatus(D3DRASTER_STATUS *pRasterStatus) override;
	virtual HRESULT STDMETHODCALLTYPE GetDisplayMode(D3DDISPLAYMODE *pMode) override;
	virtual HRESULT STDMETHODCALLTYPE GetDevice(IDirect3DDevice9 **ppDevice) override;
	virtual HRESULT STDMETHODCALLTYPE GetPresentParameters(D3DPRESENT_PARAMETERS *pPresentationParameters) override;
	#pragma endregion
	#pragma region IDirect3DSwapChain9Ex
	virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(UINT *pLastPresentCount) override;
	virtual HRESULT STDMETHODCALLTYPE GetPresentStats(D3DPRESENTSTATS *pPresentationStatistics) override;
	virtual HRESULT STDMETHODCALLTYPE GetDisplayModeEx(D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation) override;
	#pragma endregion

	LONG _ref;
	IDirect3DSwapChain9 *_orig;
	unsigned int _interface_version;
	Direct3DDevice9 *const _device;
	std::shared_ptr<reshade::d3d9_runtime> _runtime;

private:
	Direct3DSwapChain9(const Direct3DSwapChain9 &) = delete;
	Direct3DSwapChain9 &operator=(const Direct3DSwapChain9 &) = delete;
};
