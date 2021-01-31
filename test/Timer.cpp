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
#include <ArduinoUnitTests.h>

#include "Timer.hpp"

bool TestForInterval_UpCycle(unsigned long interval)
{
	Timer timer(interval);
	int error = 0;

	delay(interval - interval / 2);
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.IsTimeToExecute() == true);
	timer.UpCycle();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	// test if timer properly upcycles
	delay(interval - interval / 2);
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.IsTimeToExecute() == true);
	timer.UpCycle();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	// test if timer returns proper time since last execution
	timer.Reset();
	delay(42);
	error += timer.GetTimeSinceLastExecution() != 42; 
	return (error == 0);
}

bool TestForInterval_DownCycle(unsigned long interval)
{
	Timer timer(interval);
	int error = 0;

	delay(interval - interval / 2);
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.IsTimeToExecute() == true);
	timer.UpCycle();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	timer.Reset();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	// test if timer properly downcycles
	timer.DownCycle();
	error += !(timer.IsTimeToExecute() == true);
	timer.UpCycle();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	// test if timer returns proper time since last execution
	timer.Reset();
	delay(42);
	error += timer.GetTimeSinceLastExecution() != 42; 
	return (error == 0);
}

bool TestForInterval_Unlock(unsigned long interval)
{
	Timer timer(interval);
	int error = 0;

	delay(interval - interval / 2);
	error += !(timer.Unlock() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.Unlock() == true);
	error += !(timer.Unlock() == (interval > 0) ? false : true);

	// test if timer properly resets
	delay(interval - interval / 2);
	error += !(timer.Unlock() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.Unlock() == true);
	error += !(timer.Unlock() == (interval > 0) ? false : true);

	// test if timer returns proper time since last execution
	timer.Reset();
	delay(42);
	error += timer.GetTimeSinceLastExecution() != 42; 
	return (error == 0);
}

unittest(Timer)
{
	assertTrue(TestForInterval_UpCycle(0));
	assertTrue(TestForInterval_UpCycle(1 * 1000));
	assertTrue(TestForInterval_UpCycle(3 * 1000));
	assertTrue(TestForInterval_UpCycle(5 * 1000));
	assertTrue(TestForInterval_UpCycle(10 * 1000));
}

unittest(Timer_DownCycle)
{
	assertTrue(TestForInterval_DownCycle(0));
	assertTrue(TestForInterval_DownCycle(1 * 1000));
	assertTrue(TestForInterval_DownCycle(3 * 1000));
	assertTrue(TestForInterval_DownCycle(5 * 1000));
	assertTrue(TestForInterval_DownCycle(10 * 1000));
}

unittest(Timer_Unlock)
{
	assertTrue(TestForInterval_Unlock(0));
	assertTrue(TestForInterval_Unlock(1 * 1000));
	assertTrue(TestForInterval_Unlock(3 * 1000));
	assertTrue(TestForInterval_Unlock(5 * 1000));
	assertTrue(TestForInterval_Unlock(10 * 1000));
}

unittest_main()
