[!if PLUGIN_DSP]
#include "vdjDsp8.h"
[!endif]
[!if PLUGIN_VIDEOFX]
#include "vdjVideo8.h"
[!endif]
[!if PLUGIN_VIDEOTRANS]
#include "vdjVideo8.h"
[!endif]
[!if PLUGIN_EMPTY]
#include "vdjPlugin8.h"
[!endif]

// Plugin Interface ID
#define ID_SLIDER_1  0
#define ID_SLIDER_2  1
#define ID_STRING_1  3


//////////////////////////////////////////////////////////////////////////
// Class definition
//////////////////////////////////////////////////////////////////////////
[!if PLUGIN_DSP]
class C[!output PROJECT_NAME] : public IVdjPluginDsp8
[!endif]
[!if PLUGIN_VIDEOFX]
class C[!output PROJECT_NAME] : public IVdjPluginVideoFx8
[!endif]
[!if PLUGIN_VIDEOTRANS]
class C[!output PROJECT_NAME] : public IVdjPluginVideoTransition8
[!endif]
[!if PLUGIN_EMPTY]
class C[!output PROJECT_NAME] : public IVdjPlugin8
[!endif]
{
public:
	HRESULT VDJ_API OnLoad();
	HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo *infos);
	ULONG   VDJ_API Release();
	HRESULT VDJ_API OnParameter(int id);
[!if PLUGIN_DSP]
        HRESULT VDJ_API OnStart(int pos,int deck);
	HRESULT VDJ_API OnStop();
	HRESULT VDJ_API OnProcessSamples(short *buffer,int nb,int pos);
[!endif]
[!if PLUGIN_VIDEOFX]
	HRESULT VDJ_API OnDraw(IDirect3DTexture9 *texture,TVertex *vertices);
[!endif]
[!if PLUGIN_VIDEOTRANS]
	HRESULT VDJ_API Compose(int crossfader,HRESULT(VDJ_API *RenderSurface[2])(),TVertex *vertices[2]);
	HRESULT VDJ_API OnCrossfaderTimer(int *crossfader);
[!endif]

private:
	// For example:
	int slider1;
	int slider2;
	char string1[128];
};
//////////////////////////////////////////////////////////////////////////
// Initialization
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API DllGetClassObject(const GUID &rclsid,const GUID &riid,void** ppObject)
{
	// This is the standard DLL loader for COM object.
	// You don't need to change anything in this function.
	if(memcmp(&rclsid,&CLSID_VdjPlugin8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!if PLUGIN_DSP]
	if(memcmp(&riid,&IID_IVdjPluginDsp8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOFX]
	if(memcmp(&riid,&IID_IVdjPluginVideoFx8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOTRANS]
	if(memcmp(&riid,&IID_IVdjPluginVideoTransition8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
	*ppObject=new C[!output PROJECT_NAME]();
	return NO_ERROR;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnLoad()
{
	// For example:
	DeclareParameter(&slider1,VDJPARAM_SLIDER,ID_SLIDER_1,"My first slider",2048);
	DeclareParameter(&slider2,VDJPARAM_SLIDER,ID_SLIDER_2,"My second slider",2048);
	DeclareParameter(string1,VDJPARAM_STRING,ID_STRING_1,"Text1",sizeof(string1));

	OnParameter(ID_SLIDER_1);
	OnParameter(ID_SLIDER_2);
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnGetPluginInfo(TVdjPluginInfo *infos)
{
	infos->Author="Put your name here";
	infos->PluginName="[!output PROJECT_NAME]";
	infos->Description="Description of your plugin";
	infos->Bitmap=PLUGIN_BITMAP;
	infos->Flag=0x00;
	return S_OK;
}
//------------------------------------------------------------------------
ULONG VDJ_API C[!output PROJECT_NAME]::Release() 
{
	delete this;
	return 0;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnParameter(int id)
{
	switch(id)
	{
		// For example:
		case ID_SLIDER_1: break;
		case ID_SLIDER_2: break;
	}
	
	SendCommand("effect_redraw", PLUGIN_DECK);
	return S_OK;
}
[!if PLUGIN_DSP]
//////////////////////////////////////////////////////////////////////////
// Sound processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStart(int pos,int deck)
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStop()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnProcessSamples(short *buffer,int nb,int pos)
{
	// Example 1:
	short left,right;
	int i;
	
	for(i=0;i<nb;i++)
	{
		left = buffer[2*i];
		right = buffer[2*i+1];
		// do whatever you want here
		samples[2*i] = left;
		samples[2*i+1] = right;
	}


    /*
	// Example 2:
    DWORD *samples = (DWORD*) buffer;
	short left,right;
	int i;
	
	for(i=0;i<nb;i++)
	{
		left = LEFTCHAN(samples[i]);
		right = RIGHTCHAN(samples[i]);
		// do whatever you want here
		samples[i] = MAKECHAN(left,right);	
	}
    */
	return S_OK;
}
[!endif]
[!if PLUGIN_VIDEOFX]
//////////////////////////////////////////////////////////////////////////
// Video processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDraw(IDirect3DTexture9 *texture,TVertex *vertices)
{
	// modify the texture or vertices
	return S_FALSE;
}
[!endif]
[!if PLUGIN_VIDEOTRANS]
//////////////////////////////////////////////////////////////////////////
// Auto-transition
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnCrossfaderTimer(int *crossfader)
{
	return GetInfo("AutoVideoCrossfader",crossfader);
}
//////////////////////////////////////////////////////////////////////////
// Video processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::Compose(int crossfader,HRESULT(__stdcall *RenderSurface[2])(),TVertex *vertices[2])
{
	// change the vertices according to crossfader
	RenderSurface[0];
	RenderSurface[1];
	return S_OK;
}
[!endif]


