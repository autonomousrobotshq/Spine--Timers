//
// Spine - Spine - MCU code for robotics.
// Copyright (C) 2019-2021 Codam Robotics
//
// This file is part of Spine.
//
// Spine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Spine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Spine.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Arduino.h>
#include "Timer.hpp"

Timer::Timer(const unsigned long _interval)
    : _previous_millis(millis())
    , _interval(_interval)
{
}

Timer::~Timer()
{
}

bool Timer::IsTimeToExecute()
{
    return (millis() - _previous_millis >= _interval);
}

unsigned long Timer::GetTimeSinceLastExecution()
{
    return (millis() - _previous_millis);
}

bool Timer::Unlock()
{
    if (IsTimeToExecute()) {
		UpCycle(1);
		return (true);
	}
	return (false);
}

void Timer::UpCycle(int count)
{
	_previous_millis += _interval * count;
}

void Timer::DownCycle(int count)
{
	_previous_millis -= _interval * count;
}

void Timer::Reset()
{
	_previous_millis = millis();
}
