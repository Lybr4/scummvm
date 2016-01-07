#pragma once
#include "common/events.h"
#include "common/scummsys.h"
#include "common/system.h"
#include "uwpsdl-events.h"

using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;

ref class WinUWPGesture sealed
{
public:
	WinUWPGesture();

private:
	GestureRecognizer^ _recognizer;
	CoreCursor^ _cursor;
	CoreWindow^ _window;
	Windows::Foundation::Point _previous;

	Common::EventManager* _eventMan;

	void Init();

	void OnRightTap(GestureRecognizer^ sender, RightTappedEventArgs^ e);
	void OnTap(GestureRecognizer^ sender, TappedEventArgs^ e);
	void OnManipulationStarted(GestureRecognizer^ sender, ManipulationStartedEventArgs^ e);
	void OnManipulationUpdated(GestureRecognizer^ sender, ManipulationUpdatedEventArgs^ e);
	void OnManipulationCompleted(GestureRecognizer^ sender, ManipulationCompletedEventArgs^ e);

	void OnBackRequested(Object^ sender, BackRequestedEventArgs^ e);
	
	void OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ e);
	void OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ e);
	void OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ e);
};
