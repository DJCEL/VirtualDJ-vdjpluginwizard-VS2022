//////////////////////////////////////////////////////////////////////////
//
// VirtualDJ / Cue / VirtualVinyl / PCDJ VJ
// Plugin SDK for Windows / MAC OS
// (c)Atomix Productions 2007-2008
// File Version: 1.3
//
//////////////////////////////////////////////////////////////////////////
//
// This file defines the timecode custom engine plugins.
// In addition to all the elements supported from the base IVdjPlugin class,
// it defines additional timecode-specific functions and variables:
//
//////////////////////////////////////////////////////////////////////////


#ifndef VdjTimecode_H
#define VdjTimecode_H

#include "VdjPlugin.h"

//////////////////////////////////////////////////////////////////////////
// structs definitions

struct TVdjPluginTimecodeConfig
{
	int Speed,Gain,RIAA,Invert,Silence,AntiSkip;
	int Lead,RelMode,SmartCue,ClearSound,AutoBrowser;
	int EndPos,AutoBrowserPos;
	int ShiftRotation;
	int RefOne,RefZero;
	int PitchSensitivity;
};

//////////////////////////////////////////////////////////////////////////
// VdjTimecodeSignal plugin class
// This class let you define your own timecode signal management, in order
// to be compatible with other records than the default VDJ's ones

class IVdjPluginTimecodeSignal : public IVdjPlugin
{
public:
	// called when timecode is activated on that deck
	virtual HRESULT VDJ_API Init() {return 0;}

	// Implement your timecode analysis algorithm in this function.
	// buffer is a signed 32bits interleaved stereo buffer of nb stereo incoming samples
	// the gain, optional RIAA filter and stereo inversion are already applied on the incoming datas 
	virtual HRESULT VDJ_API Decode(int *buffer,int nb)=0;

	// Here are the variables that your Decode function should set:
	int LastSyncCode; // value of the last timecode read-out (in 1/44100s)
	int DeltaPosSinceSync; // movement registered on the disc since the last valid timecode
	int UnsyncedLength; // time elapsed since the last valid timecode was found
	int SilenceLength; // time elapsed since the last audible signal was picked
	int Direction; // direction of the disc (-1 or +1)

	// GetQuality should return the signal quality, from 0 to 256, or -1 for silent
	virtual HRESULT VDJ_API GetQuality(int *quality) {return 0;}
	// GetCustomDisplay is called from the timecode config page in advanced mode when the user select the
	// alternate display. Bits is a Width*Height DWORD buffer to receive the 32bit image
	virtual HRESULT VDJ_API GetCustomDisplay(DWORD *Bits,int Width,int Height) {return 0;}
	// AutoConfig is called if the user click on the auto button on the config page
	// The buffer is one second of signed 32bit interleaved stereo buffers (nb=44100)
	virtual HRESULT VDJ_API AutoConfig(int *buffer,int nb) {return 0;}

	// The config values are set by the user from the options, or can be changed
	// by your AutoConfig function.
	TVdjPluginTimecodeConfig *Config;
};

//////////////////////////////////////////////////////////////////////////
// VdjTimecodeEngine plugin class
// This class let you define your own timecode behavior

class IVdjPluginTimecodeEngine : public IVdjPlugin
{
public:
	// called when timecode is activated on that deck
	virtual HRESULT VDJ_API Init() {return 0;}

	// Implement your timecode behavior in this function.
	// The function is called when a buffer of nb samples of timecode data have been processed.
	// Return in speed the multiplier by which to accelerate/decelerate the output.
	// In absolute mode, you might want to call SendCommand to jump to new positions.
	// Also, you can change the Pitch value if you want the pitch to reflect in the skin.
	virtual HRESULT VDJ_API Process(int nb,float *speed)=0;

	// These values are returned by the timecode signal module
	int LastSyncCode; // value of the last timecode read-out (in 1/44100s)
	int DeltaPosSinceSync; // movement registered on the disc since the last valid timecode
	int UnsyncedLength; // time elapsed since the last valid timecode was found
	int SilenceLength; // time elapsed since the last audible signal was picked
	int Direction; // direction of the disc (-1 or +1)

	// useful informations you can use
	float Pitch; // Pitch multiplier (read/write variable)
	int SongPosition; // actual position of the song
	int SongLen; // length of the song in 1/44100s
	int SongStatus; // -1=no song, 0=paused, 1=playing

	// this function is called each time a new song is loaded
	virtual HRESULT VDJ_API OnNewSong() {return 0;}
	// this function is called each time the user calls a cuepoint by software
	virtual HRESULT VDJ_API OnCue() {return 0;}
	// this function is called in one-turntable mode when the user switch the deck
	virtual HRESULT VDJ_API SetChannel(int ch) {return 0;}
	// this function is called when the timecode is activated/deactivated
	virtual HRESULT VDJ_API OnActivate(bool a) {return 0;}

	TVdjPluginTimecodeConfig *Config;
};

//////////////////////////////////////////////////////////////////////////
// GUID definitions

#ifndef VDJTIMECODEGUID_DEFINED
#define VDJTIMECODEGUID_DEFINED
	static const GUID IID_IVdjPluginTimecodeEngine = { 0xcfca612a, 0xb5be, 0x40b6, { 0xa2, 0x18, 0xad, 0x24, 0x07, 0x12, 0x04, 0x90 } };
	static const GUID IID_IVdjPluginTimecodeSignal = { 0x6a208c33, 0x8415, 0x4afb, { 0xb9, 0x63, 0xdd, 0x76, 0xd6, 0x19, 0xbd, 0x1d } };
#else
	extern static const GUID IID_IVdjPluginTimecodeEngine;
	extern static const GUID IID_IVdjPluginTimecodeSignal;
#endif

//////////////////////////////////////////////////////////////////////////

#endif /* VdjTimecode_H */