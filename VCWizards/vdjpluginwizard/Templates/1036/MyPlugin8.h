#ifndef [!output PROJECT_NAME]_H
#define [!output PROJECT_NAME]_H

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
	HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info);
	ULONG   VDJ_API Release();
	HRESULT VDJ_API OnParameter(int id);
	HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize);
	HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface);
[!if PLUGIN_DSP]
        HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
	HRESULT VDJ_API OnProcessSamples(float *buffer, int nb);
[!endif]
[!if PLUGIN_VIDEOFX]
	HRESULT VDJ_API OnDeviceInit();
	HRESULT VDJ_API OnDeviceClose();
	HRESULT VDJ_API OnDraw();
	HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
[!endif]
[!if PLUGIN_VIDEOTRANS]
	HRESULT VDJ_API OnDeviceInit();
	HRESULT VDJ_API OnDeviceClose();
	HRESULT VDJ_API OnDraw(float crossfader)
[!endif]

private:
	// For example:
	float m_SliderValue1;
	float m_SliderValue2;
	float m_Param1;
	float m_Param2;

	typedef enum _ID_Interface
	{
		ID_INIT,
		ID_SLIDER_1,
		ID_SLIDER_2,
	} ID_Interface;

};

#endif
