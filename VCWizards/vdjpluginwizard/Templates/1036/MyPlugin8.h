#ifndef [!output PROJECT_NAME]_H
#define [!output PROJECT_NAME]_H

[!if PLUGIN_BASIC8]
#include "vdjPlugin8.h"
[!endif]
[!if PLUGIN_DSP8]
#include "vdjDsp8.h"
[!endif]
[!if PLUGIN_BUFFERDSP8]
#include "vdjDsp8.h"
[!endif]
[!if PLUGIN_POSITIONDSP8]
#include "vdjDsp8.h"
[!endif]
[!if PLUGIN_VIDEOFX8]
#include "vdjVideo8.h"
[!endif]
[!if PLUGIN_VIDEOTRANS8]
#include "vdjVideo8.h"
[!endif]
[!if PLUGIN_VIDEOTRANSMULTIDECK8]
#include "vdjVideo8.h"
[!endif]
[!if PLUGIN_ONLINESOURCE]
#include "VdjOnlineSource.h"
[!endif]

#include <stdio.h>
	
//////////////////////////////////////////////////////////////////////////
// Class definition
//////////////////////////////////////////////////////////////////////////
[!if PLUGIN_BASIC8]
class C[!output PROJECT_NAME] : public IVdjPlugin8
[!endif]
[!if PLUGIN_DSP8]
class C[!output PROJECT_NAME] : public IVdjPluginDsp8
[!endif]
[!if PLUGIN_BUFFERDSP8]
class C[!output PROJECT_NAME] : public IVdjPluginBufferDsp8
[!endif]
[!if PLUGIN_POSITIONDSP8]
class C[!output PROJECT_NAME] : public IVdjPluginPositionDsp8
[!endif]
[!if PLUGIN_VIDEOFX8]
class C[!output PROJECT_NAME] : public IVdjPluginVideoFx8
[!endif]
[!if PLUGIN_VIDEOTRANS8]
class C[!output PROJECT_NAME] : public IVdjPluginVideoTransition8
[!endif]
[!if PLUGIN_VIDEOTRANSMULTIDECK8]
class C[!output PROJECT_NAME] : public IVdjPluginVideoTransitionMultiDeck8
[!endif]
[!if PLUGIN_ONLINESOURCE]
class C[!output PROJECT_NAME] : public IVdjPluginOnlineSource
[!endif]
{
public:
	HRESULT VDJ_API OnLoad();
	HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info);
	ULONG   VDJ_API Release();
	HRESULT VDJ_API OnParameter(int id);
	HRESULT VDJ_API OnGetParameterString(int id, char *outParam, int outParamSize);
	HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8 *pluginInterface);
[!if PLUGIN_DSP8]
        HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
	HRESULT VDJ_API OnProcessSamples(float *buffer, int nb);
[!endif]
[!if PLUGIN_BUFFERDSP8]
	HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
	short * VDJ_API OnGetSongBuffer(int songPos, int nb);
[!endif]
[!if PLUGIN_POSITIONDSP8]
	HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
	HRESULT VDJ_API OnTransformPosition(double *songPos, double *videoPos)
[!endif]
[!if PLUGIN_VIDEOFX8]
	HRESULT VDJ_API OnDeviceInit();
	HRESULT VDJ_API OnDeviceClose();
	HRESULT VDJ_API OnDraw();
	HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
	HRESULT VDJ_API OnAudioSamples(float *buffer, int nb);
[!endif]
[!if PLUGIN_VIDEOTRANS8]
	HRESULT VDJ_API OnDeviceInit();
	HRESULT VDJ_API OnDeviceClose();
	HRESULT VDJ_API OnDraw(float crossfader)
[!endif]
[!if PLUGIN_ONLINESOURCE]
	HRESULT VDJ_API IsLogged();
	HRESULT VDJ_API OnLogin();
	HRESULT VDJ_API OnLogout();
	HRESULT VDJ_API OnOAuth(const char* access_token, size_t access_token_expire, const char* refresh_token, const char* code, const char* errorMessage);
	HRESULT VDJ_API OnSearch(const char* search, IVdjTracksList* tracksList);
	HRESULT VDJ_API OnSearchCancel();
	HRESULT VDJ_API GetStreamUrl(const char* uniqueId, IVdjString& url, IVdjString& errorMessage);	
	HRESULT VDJ_API GetFolderList(IVdjSubfoldersList* subfoldersList);
	HRESULT VDJ_API GetFolder(const char* folderUniqueId, IVdjTracksList* tracksList);
	HRESULT VDJ_API GetFolderContextMenu(const char* folderUniqueId, IVdjContextMenu* contextMenu);
	HRESULT VDJ_API OnFolderContextMenu(const char* folderUniqueId, size_t menuIndex);
	HRESULT VDJ_API GetContextMenu(const char* uniqueId, IVdjContextMenu* contextMenu);
	HRESULT VDJ_API OnContextMenu(const char* uniqueId, size_t menuIndex);
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
