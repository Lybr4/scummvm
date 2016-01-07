#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "winuwp-gesture.h"
#include "uwpsdl-events.h"
#include <windows.h>
#include <agile.h>
#include <..\um\debugapi.h>

using namespace Windows::Devices::Input;
using namespace Windows::UI::Core;

WinUWPGesture::WinUWPGesture()
{
	Init();
}

void WinUWPGesture::Init()
{
	_eventMan = g_system->getEventManager();


	
	_recognizer = ref new GestureRecognizer();
	
	_recognizer->GestureSettings = GestureSettings::RightTap | GestureSettings::ManipulationTranslateX | GestureSettings::ManipulationTranslateY | GestureSettings::ManipulationScale | GestureSettings::Tap | GestureSettings::DoubleTap;
	_recognizer->RightTapped += ref new TypedEventHandler<GestureRecognizer^, RightTappedEventArgs^>(this, &WinUWPGesture::OnRightTap);
	_recognizer->Tapped += ref new TypedEventHandler<GestureRecognizer^, TappedEventArgs^>(this, &WinUWPGesture::OnTap);

	_recognizer->ManipulationStarted += ref new TypedEventHandler<GestureRecognizer^, ManipulationStartedEventArgs^>(this, &WinUWPGesture::OnManipulationStarted);
	_recognizer->ManipulationUpdated += ref new TypedEventHandler<GestureRecognizer^, ManipulationUpdatedEventArgs^>(this, &WinUWPGesture::OnManipulationUpdated);
	_recognizer->ManipulationCompleted += ref new TypedEventHandler<GestureRecognizer^, ManipulationCompletedEventArgs^>(this, &WinUWPGesture::OnManipulationCompleted);


	_recognizer->ShowGestureFeedback = true;

	Platform::Agile<CoreWindow^> _agileWindow;
	_window = _agileWindow->GetForCurrentThread();

	_cursor = ref new CoreCursor(CoreCursorType::Custom, 101);
	
	_window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinUWPGesture::OnPointerPressed);
	_window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinUWPGesture::OnPointerReleased);
	_window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinUWPGesture::OnPointerMoved);
	_previous = _window->PointerPosition;

	SystemNavigationManager::GetForCurrentView()->BackRequested += ref new EventHandler<BackRequestedEventArgs^>(this, &WinUWPGesture::OnBackRequested);

}

void WinUWPGesture::OnManipulationStarted(GestureRecognizer^ sender, ManipulationStartedEventArgs^ e)
{
}

void WinUWPGesture::OnManipulationUpdated(GestureRecognizer^ sender, ManipulationUpdatedEventArgs^ e)
{
	

	
}

void WinUWPGesture::OnManipulationCompleted(GestureRecognizer^ sender, ManipulationCompletedEventArgs^ e)
{
	Common::Event event;

	if (e->Velocities.Linear.X >= 2.5) {
		event.kbd.keycode = Common::KEYCODE_ESCAPE;
		event.kbd.ascii = Common::ASCII_ESCAPE;
		event.type = Common::EVENT_KEYDOWN;
		_eventMan->pushEvent(event);
		event.type = Common::EVENT_KEYUP;
		_eventMan->pushEvent(event);
		return;
	}

	if (e->Velocities.Expansion < -0.5) {
		event.type = Common::EVENT_MAINMENU;
		_eventMan->pushEvent(event);
		return;
	}

	if (e->Velocities.Expansion > 0.5) {
		event.type = Common::EVENT_VIRTUAL_KEYBOARD;
		_eventMan->pushEvent(event);
		return;
	}
}

void WinUWPGesture::OnBackRequested(Object ^ sender, BackRequestedEventArgs ^ e)
{
	Common::Event event;
	event.mouse = _eventMan->getMousePos();
	event.type = Common::EVENT_RBUTTONDOWN;
	_eventMan->pushEvent(event);
	event.type = Common::EVENT_RBUTTONUP;
	_eventMan->pushEvent(event);
	e->Handled = true;
}

void WinUWPGesture::OnRightTap(GestureRecognizer^ sender, RightTappedEventArgs^ e)
{
	Common::Event event;
	event.mouse = _eventMan->getMousePos();
	event.type = Common::EVENT_RBUTTONDOWN;
	_eventMan->pushEvent(event);
	event.type = Common::EVENT_RBUTTONUP;
	_eventMan->pushEvent(event);
}

void WinUWPGesture::OnTap(GestureRecognizer ^ sender, TappedEventArgs ^ e)
{
	Common::Event event;
	event.mouse = _eventMan->getMousePos();
	event.type = Common::EVENT_LBUTTONDOWN;
	_eventMan->pushEvent(event);
	event.type = Common::EVENT_LBUTTONUP;
	_eventMan->pushEvent(event);
}


void WinUWPGesture::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ e)
{
	_recognizer->ProcessDownEvent(e->CurrentPoint);
}

void WinUWPGesture::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ e)
{
	_recognizer->ProcessUpEvent(e->CurrentPoint);
}

void WinUWPGesture::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ e)
{
	sender->PointerCursor = _cursor;
	_recognizer->ProcessMoveEvents(e->GetIntermediatePoints());
}