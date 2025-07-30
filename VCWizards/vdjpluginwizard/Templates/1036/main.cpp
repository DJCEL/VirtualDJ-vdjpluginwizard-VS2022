#include "MyPlugin8.h"

HRESULT VDJ_API DllGetClassObject(const GUID &rclsid,const GUID &riid,void** ppObject)
{
	// This is the standard DLL loader for COM object.
	if(memcmp(&rclsid,&CLSID_VdjPlugin8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;

[!if PLUGIN_BASIC8]
	if(memcmp(&riid,&IID_IVdjPluginBasic8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]	
[!if PLUGIN_DSP8]
	if(memcmp(&riid,&IID_IVdjPluginDsp8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOFX8]
	if(memcmp(&riid,&IID_IVdjPluginVideoFx8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
[!if PLUGIN_VIDEOTRANS8]
	if(memcmp(&riid,&IID_IVdjPluginVideoTransition8,sizeof(GUID))!=0) return CLASS_E_CLASSNOTAVAILABLE;
[!endif]
	
	*ppObject = new C[!output PROJECT_NAME]();  // we create our CMyPlugin8 class
	
	return NO_ERROR;
}
