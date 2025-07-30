#include "MyPlugin8.h"

//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnLoad()
{
	HRESULT hr = S_FALSE;
	
	// For example:
	hr = DeclareParameterSlider(&m_SliderValue1, ID_SLIDER_1, "Param1", "P1", 0.0f);
	hr = DeclareParameterSlider(&m_SliderValue2, ID_SLIDER_2, "Param2", "P2", 0.5f);

	hr = OnParameter(ID_SLIDER_1);
	hr = OnParameter(ID_SLIDER_2);
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnGetPluginInfo(TVdjPluginInfo8 *infos)
{
	info->Author = "Put your name here";
	info->PluginName = "[!output PROJECT_NAME]";
	info->Description = "Description of your plugin";
	info->Flags = 0x00;
	info->Version = "1.0 (64-bit)";
	
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
		case ID_SLIDER_1: 
			m_Param1 = m_SliderValue1 * 10.0f;
			break;
		
		case ID_SLIDER_2:
			m_Param2 = 10.0f + m_SliderValue2 * (50.0f - 10.0f);
			break;
	}
	
	return S_OK;
}
//-------------------------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnGetParameterString(int id, char *outParam, int outParamSize)
{
	switch (id)
	{
		case ID_SLIDER_1:
			sprintf_s(outParam, outParamSize, "%.2f", m_Param1);
			break;
		
		case ID_SLIDER_2:
			sprintf_s(outParam, outParamSize, "%.2f", m_Param2);
			break;
	}
			
	return S_OK; // return E_NOTIMPL; if you have nothing to display
}
//-------------------------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnGetUserInterface(TVdjPluginInterface8 *pluginInterface)
{
	return E_NOTIMPL;
}
[!if PLUGIN_STARTSTOP8]
//------------------------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStart()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStop()
{
	return S_OK;
}	
[!endif]
[!if PLUGIN_DSP8]
//////////////////////////////////////////////////////////////////////////
// Sound processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStart()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStop()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnProcessSamples(float *buffer, int nb)
{
	// Example 1:
	float left,right;
	int i;
	
	for(i=0;i<nb;i++)
	{
		left = buffer[2*i];
		right = buffer[2*i+1];
		
		// do whatever you want here (modify left and/or right)
		
		buffer[2*i] = left;
		buffer[2*i+1] = right;
	}
	return S_OK;
}
[!endif]
[!if PLUGIN_BUFFERDSP8]
//////////////////////////////////////////////////////////////////////////
// Sound processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStart()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStop()
{
	return S_OK;
}
//------------------------------------------------------------------------
// TODO	
[!endif]
[!if PLUGIN_POSITIONDSP8]
//////////////////////////////////////////////////////////////////////////
// Sound processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStart()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStop()
{
	return S_OK;
}
//------------------------------------------------------------------------
// TODO
[!endif]	
[!if PLUGIN_VIDEOFX8]
//////////////////////////////////////////////////////////////////////////
// Video processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDeviceInit()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDeviceClose()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStart()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnStop()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDraw()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API OnAudioSamples(float *buffer, int nb)
{
	return E_NOTIMPL;
}
[!endif]
[!if PLUGIN_VIDEOTRANS8]
//////////////////////////////////////////////////////////////////////////
// Video processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDeviceInit()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDeviceClose()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDraw(float crossfader)
{
	return S_OK;
}
[!endif]
[!if PLUGIN_VIDEOTRANSMULTIDECK8]
//////////////////////////////////////////////////////////////////////////
// Video processing
//////////////////////////////////////////////////////////////////////////
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDeviceInit()
{
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDeviceClose()
{
	return S_OK;
}
//------------------------------------------------------------------------	
HRESULT VDJ_API C[!output PROJECT_NAME]::OnDrawMultiDeck(int nbVideoDecks, int *videoDecks)
{
	return S_OK;
}
[!endif]
[!if PLUGIN_ONLINESOURCE]
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::IsLogged() 
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnLogin()
{ 
	return E_NOTIMPL;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnLogout() 
{ 
	return E_NOTIMPL;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnOAuth(const char* access_token, size_t access_token_expire, const char* refresh_token, const char* code, const char* errorMessage) 
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnSearch(const char* search, IVdjTracksList* tracksList)
{
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnSearchCancel() 
{ 
	return E_NOTIMPL;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::GetStreamUrl(const char* uniqueId, IVdjString& url, IVdjString& errorMessage)
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::GetFolderList(IVdjSubfoldersList* subfoldersList) 
{ 
	return E_NOTIMPL;
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::GetFolder(const char* folderUniqueId, IVdjTracksList* tracksList)
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::GetFolderContextMenu(const char* folderUniqueId, IVdjContextMenu* contextMenu) 
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnFolderContextMenu(const char* folderUniqueId, size_t menuIndex) 
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::GetContextMenu(const char* uniqueId, IVdjContextMenu* contextMenu) 
{ 
	return E_NOTIMPL; 
}
//------------------------------------------------------------------------
HRESULT VDJ_API C[!output PROJECT_NAME]::OnContextMenu(const char* uniqueId, size_t menuIndex) 
{ 
	return E_NOTIMPL; 
}
[!endif]


