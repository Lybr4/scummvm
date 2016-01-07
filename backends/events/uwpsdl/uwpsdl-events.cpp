/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/scummsys.h"

#include "uwpsdl-events.h"
#include "common/translation.h"

using namespace Windows::UI::ViewManagement;

namespace UWP {

UWPSdlEventSource::UWPSdlEventSource() : SdlEventSource(), _touchpadMode(true) {

}

bool UWPSdlEventSource::handleMouseButtonDown(SDL_Event &ev, Common::Event &event) {

	if (ev.button.button == SDL_BUTTON_LEFT && _touchpadMode) {
		return false;
	}

	// Invoke parent implementation of this method
	return SdlEventSource::handleMouseButtonDown(ev, event);
}

bool UWPSdlEventSource::handleMouseButtonUp(SDL_Event &ev, Common::Event &event) {

	if (ev.button.button == SDL_BUTTON_LEFT && _touchpadMode) {
		return false;
	}

	// Invoke parent implementation of this method
	return SdlEventSource::handleMouseButtonUp(ev, event);
}

bool UWPSdlEventSource::toggleClickMode() {

	_touchpadMode = !_touchpadMode;
	return _touchpadMode;
}

UWPSdlEventObserver::UWPSdlEventObserver(UWP::UWPSdlEventSource *eventSource) {
	assert(eventSource);
	_eventSource = eventSource;
}

bool UWPSdlEventObserver::notifyEvent(const Common::Event &event) {
	
	return false;
}

} // namespace UWP

