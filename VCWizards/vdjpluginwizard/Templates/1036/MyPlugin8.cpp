#include "MyPlugin8.h"


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


