//////////////////////////////////////////////////////////////////////////
//
// VirtualDJ / Cue / VirtualVinyl / PCDJ VJ
// Plugin SDK for Windows
// (c)Atomix Productions 2006-2008
// File Version: 1.3
//
//////////////////////////////////////////////////////////////////////////
//
// This file defines the video plugins (both Fx and Transition).
// In addition to all the elements supported from the base IVdjPlugin class,
// it defines additional video-specific functions and variables:
//
//////////////////////////////////////////////////////////////////////////


#ifndef VdjVideo_H
#define VdjVideo_H

#include "VdjPlugin.h"

//////////////////////////////////////////////////////////////////////////
// DirectX data types

struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct TVertex
{
	struct {float x,y,z;} position;
	DWORD color;
	FLOAT tu,tv;
};

//////////////////////////////////////////////////////////////////////////
// VideoFx plugin class

class IVdjPluginVideoFx : public IVdjPlugin
{
public:
	// called when DirectX is initialized and closed
	// if you need to allocate private surfaces or textures,
	// this is the place to do it
	virtual HRESULT VDJ_API OnDXInit() {return 0;}
	virtual HRESULT VDJ_API OnDXClose() {return 0;}

	// called on start and stop of the plugin
	virtual HRESULT VDJ_API OnStart() {return 0;}
	virtual HRESULT VDJ_API OnStop() {return 0;}

	// use this function to render the D3D surface on the device, using any modification you want
	// return S_OK if you actually draw the texture on the device, or S_FALSE to let VirtualDJ do it
	virtual HRESULT VDJ_API OnDraw(IDirect3DTexture9 *texture,TVertex *vertices)=0;

	// variables you can use (once DX has been initialized)
	IDirect3DDevice9 *D3DDevice;
	int ImageWidth,ImageHeight;
};

//////////////////////////////////////////////////////////////////////////
// VideoTransition plugin class

class IVdjPluginVideoTransition : public IVdjPlugin
{
public:
	// called when DirectX is initialized and closed
	// if you need to allocate private surfaces or textures,
	// this is the place to do it
	virtual HRESULT VDJ_API OnDXInit() {return 0;}
	virtual HRESULT VDJ_API OnDXClose() {return 0;}

	// use this function to compose both surfaces on the device.
	// calling the RenderSurface[x] function will render the image on the actual render target,
	// using the vertices[x] given.
	virtual HRESULT VDJ_API Compose(int crossfader,HRESULT(VDJ_API *RenderSurface[2])(),TVertex *vertices[2])=0;

	// OnStart() and OnStop() are called if the user activate the auto-transition.
	// once activated, OnCrossfaderTimer() will be called every frame to let you change
	// the value of the video crossfader before rendering.
	// return S_FALSE will stop the auto-transition (OnStop() will not be called).
	// return E_NOTIMPL will use the default auto-transition.
	// NOTE: if crossfader is set to 0 or 4096, the Compose() function will not be called.
	virtual HRESULT VDJ_API OnStart(int chan) {return 0;}
	virtual HRESULT VDJ_API OnStop() {return 0;}
	virtual HRESULT VDJ_API OnCrossfaderTimer(int *crossfader) {return E_NOTIMPL;}

	// variables you can use (once DX has been initialized)
	IDirect3DDevice9 *D3DDevice;
	int ImageWidth,ImageHeight;
};

//////////////////////////////////////////////////////////////////////////
// GUID definitions

#ifndef VDJVIDEOGUID_DEFINED
#define VDJVIDEOGUID_DEFINED
	static const GUID IID_IVdjPluginVideoFx = { 0x9ad1e934, 0x31ce, 0x4be8, { 0xb3, 0xee, 0x1e, 0x1f, 0x1c, 0x94, 0x55, 0x10 } };
	static const GUID IID_IVdjPluginVideoTransition = { 0x119f6f6a, 0x1a37, 0x4fe5, { 0x96, 0x53, 0x31, 0x20, 0x3a, 0xc9, 0x4e, 0x28 } };
#else
	extern static const GUID IID_IVdjPluginVideoFx;
	extern static const GUID IID_IVdjPluginVideoTransition;
#endif

//////////////////////////////////////////////////////////////////////////
	
#endif  /* VdjVideo_H */
