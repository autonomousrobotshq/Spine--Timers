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

#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
    Timer(const unsigned long _interval);
    ~Timer();
    unsigned long GetTimeSinceLastExecution();
    bool IsTimeToExecute();
	bool Unlock();
	void UpCycle(int count = 1);
	void DownCycle(int count = 1);
	void Reset();

private:
    unsigned long _previous_millis;
    const unsigned long _interval;
};

#endif
