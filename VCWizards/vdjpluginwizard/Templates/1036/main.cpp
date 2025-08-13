#include "MyPlugin8.h"

HRESULT VDJ_API DllGetClassObject(const GUID &rclsid,const GUID &riid,void** ppObject)
{
	// This is the standard DLL loader for COM object.
	if(memcmp(&rclsid,&CLSID_VdjPlugin8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;

[!if PLUGIN_BASIC8]
	if(memcmp(&riid,&IID_IVdjPluginBasic8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_STARTSTOP8]
	if(memcmp(&riid,&IID_IVdjPluginStartStop8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]	
[!if PLUGIN_DSP8]
	if(memcmp(&riid,&IID_IVdjPluginDsp8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_BUFFERDSP8]
	if(memcmp(&riid,&IID_IVdjPluginBuffer8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_POSITIONDSP8]
	if(memcmp(&riid,&IID_IVdjPluginPosition8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOFX8]
	if(memcmp(&riid,&IID_IVdjPluginVideoFx8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOTRANS8]
	if(memcmp(&riid,&IID_IVdjPluginVideoTransition8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOTRANSMULTIDECK8]
	if(memcmp(&riid,&IID_IVdjPluginVideoTransitionMultiDeck8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_ONLINESOURCE]
	if(memcmp(&riid,&IID_IVdjPluginOnlineSource,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
	
	*ppObject = new C[!output PROJECT_NAME]();  // we create our class
	
	return NO_ERROR;
}
