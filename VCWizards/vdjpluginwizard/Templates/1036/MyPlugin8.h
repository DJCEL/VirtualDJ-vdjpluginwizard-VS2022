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
