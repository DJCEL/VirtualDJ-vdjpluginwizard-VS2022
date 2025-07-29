//////////////////////////////////////////////////////////////////////////
//
// VirtualDJ / Cue / VirtualVinyl / PCDJ VJ
// Plugin SDK for Windows
// (c)Atomix Productions 2006-2008
// File Version: 1.3
//
//////////////////////////////////////////////////////////////////////////
//
// This file defines the external-device custom mapper plugins.
// In addition to all the elements supported from the base IVdjPlugin class,
// it defines additional device-specific functions and variables:
//
//////////////////////////////////////////////////////////////////////////


#ifndef VdjDevice_H
#define VdjDevice_H

#include "VdjPlugin.h"

//////////////////////////////////////////////////////////////////////////
// Structures declarations

struct TVdjDeckInfo
{
	int StructSize; // =72 in current version. Might be expanded in the future
	int Position; // position in number of samples since begining
	int Length; // total number of samples in song (1 sample = 1/44100 second)
	int Status;
	int Playing;
	int Bpm;
	int Pitch;
	int PitchReset;
	int PitchMin,PitchMax;
	int Loop;
	int LoopLength;
	int CuePos,CuePos2,CuePos3;
	int BeatLed;
	int BeatLocked;
	int AutoMix;
	int MixNow;
	int Selected;
	int BassKill,MediumKill,HighKill;
};

//////////////////////////////////////////////////////////////////////////
// Common defines

#define  LEFT_CHAN  0
#define RIGHT_CHAN  1

//////////////////////////////////////////////////////////////////////////
// Device defines

#define PLUGINDEVICE_XP10			1     // xp10.dll
#define PLUGINDEVICE_DJCONSOLE		2     // djc.dll , rmx.dll
#define PLUGINDEVICE_DMC1			3
#define PLUGINDEVICE_DVINYL			4
#define PLUGINDEVICE_DAC3			5     // dac3.dll
#define PLUGINDEVICE_BCD2000		6     // bcd2000.dll
#define PLUGINDEVICE_ICDX			7     // icdx.dll
#define PLUGINDEVICE_DMC2			8     // dmc2.dll
#define PLUGINDEVICE_TOTALCONTROL	9     
#define PLUGINDEVICE_ICUE			10
#define PLUGINDEVICE_XPONENT		11    // xponent.dll
#define PLUGINDEVICE_DNHC4500		12    // hc4500.dll
#define PLUGINDEVICE_VCI100			13

//////////////////////////////////////////////////////////////////////////
// VdjDevice plugin class

class IVdjPluginDevice : public IVdjPlugin
{
public:
	// You must implement this function and return the device type for which this
	// plugin has been written.
	virtual HRESULT VDJ_API GetDeviceType(int *type)=0;

	// called when device is initialized
	virtual HRESULT VDJ_API OnReset() {return 0;}

	// This function is called each time a button is pressed or depressed
	// (return E_NOTIMPL if you want VirtualDJ to use the default mapper)
	virtual HRESULT VDJ_API OnButton(int chan,int button,int down) {return 0;}
	// This function is called each time a knob or slider is moved.
	// absvalue is the absolute position of the slider between 0 and 4096 included.
	// relvalue is the relative movement of this slider, on the same scale.
	virtual HRESULT VDJ_API OnSlider(int chan,int slider,int absvalue,int relvalue) {return 0;}
	// This function is called on devices that are compatible with low-latency scratch.
	// return S_OK and VirtualDJ will apply a low-latency scratch automatically.
	// return S_FALSE and OnSlider() will be called the regular way.
	virtual HRESULT VDJ_API OnScratch(int chan,int *value) {return 0;}

	// This function is called once every 100ms, letting you update the LEDs on the device
	virtual HRESULT VDJ_API OnTimer() {return 0;} // 100 ms
	// Call these functions to update the LEDs and display on the device.
	HRESULT (VDJ_API *SetLed)(int chan,int n,int value);
	HRESULT (VDJ_API *SetDigit)(int chan,int n,int value);
	HRESULT (VDJ_API *SetText)(int chan,int n,char *value);
	// This structure gives you direct access to common information useful for LED status.
	// You can call GetInfo() if you need other less common datas.
	TVdjDeckInfo *DeckInfo[2];
	// Leds and Digits sends are buffered. If you need to flush the buffer, use this:
	HRESULT (VDJ_API *CommitSends)();

	// An alternative to SendCommand, that lets you specify up and down status (for compat. with previous SDK)
	HRESULT (VDJ_API *SendAction)(char *action,char *chan,char *param,int down);

	// extension function and variable for specific-device needs
	void *DeviceSpecificVar;
	HRESULT (VDJ_API *DeviceSpecificCall)(int cmd,int param1,void *param2);
};

//////////////////////////////////////////////////////////////////////////
// GUID definitions

#ifndef VDJDEVICEGUID_DEFINED
#define VDJDEVICEGUID_DEFINED
	static const GUID IID_IVdjPluginDevice = { 0xc17ed55e, 0x76b2, 0x4fb7, { 0x99, 0x34, 0xbb, 0xb1, 0xaf, 0xcd, 0x8c, 0x7b } };
#else
	extern static const GUID IID_IVdjPluginDevice;
#endif

//////////////////////////////////////////////////////////////////////////

#endif /* VdjDevice_H */