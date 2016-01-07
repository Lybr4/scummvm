#ifndef PLATFORM_SDL_WINUWP_H
#define PLATFORM_SDL_WINUWP_H

#include "backends/platform/sdl/sdl.h"
#include "backends/events/uwpsdl/winuwp-gesture.h"
#include "backends/events/uwpsdl/uwpsdl-events.h"
class OSystem_WinUWP : public OSystem_SDL {

private:
	bool _virtualKbd;
	WinUWPGesture ^_gesture;
	Windows::System::Display::DisplayRequest^ _displayRequest;

public:
	OSystem_WinUWP();
	UWP::UWPSdlEventObserver *_eventObserver;
	virtual ~OSystem_WinUWP() {};
	virtual void initBackend();
	virtual void engineInit();
	virtual void engineDone();

	virtual Common::String getDefaultConfigFileName();
	virtual Common::String getSystemLanguage() const;
};

#endif