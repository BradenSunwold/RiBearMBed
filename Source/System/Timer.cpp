
#include <System/Timer.hpp>

using namespace sys::time;

Timer::Timer()
	:
	mIsPeriodic(false),
	mPeriod(0),
	mNextTimeout(0)
{
	mClockResolution = SystemTime::GetClockResolution();
}

// Public

/*
 * STATIC
 */
Timer Timer::CreatePeriodicTimer(int period, types::UnitOfTime resolution)
{
	Timer newTimer;		// Create new timer instance to link to

	// Calculate what period is needed based on system clock resolution
	int timerPeriod = newTimer.CalculatePeriod(period, resolution);

	newTimer.mIsPeriodic = true;
	newTimer.mPeriod = timerPeriod;
	newTimer.mNextTimeout = SystemTime::GetTime() + newTimer.mPeriod;

	return newTimer;
}

Timer Timer::CreateOneShotTimer(int period, types::UnitOfTime resolution)
{
	Timer newTimer;		// Create new timer instance to link to

	// Calculate what period is needed based on system clock resolution
	int timerPeriod = newTimer.CalculatePeriod(period, resolution);

	newTimer.mIsPeriodic = false;
	newTimer.mPeriod = timerPeriod;
	newTimer.mNextTimeout = SystemTime::GetTime() + newTimer.mPeriod;

	return newTimer;
}

bool Timer::TimedOut()
{
	types::TimeCount currentTime = SystemTime::GetTime();
	if(currentTime >= mNextTimeout)
	{
		if(mIsPeriodic)
		{
			mNextTimeout = currentTime + mPeriod;
		}
		return true;
	}
	return false;
}


// Private

int Timer::CalculatePeriod(int period, types::UnitOfTime resolution)
{
	int truePeriod = 0;

	if(resolution == mClockResolution)
	{
		// Same resolution passed in as system clock
		truePeriod = period;
	}
	else
	{
		// Have to scale to account for different clock resolutions
		switch(mClockResolution)
		{
		case types::eMilliSecond :
			switch(resolution)
			{
			case types::eMicroSecond :
				// micro vs milli
				truePeriod = period / 1000;
				break;
			case types::eNanoSecond :
				// nano vs milli
				truePeriod = period / 1000000;
				break;
			default :
				break;
			}
			break;
		case types::eMicroSecond :
			switch(resolution)
			{
			case types::eMilliSecond :
				// milli vs micro
				truePeriod = period * 1000;
				break;
			case types::eNanoSecond :
				// nano vs micro
				truePeriod = period / 1000;
				break;
			default :
				break;
			}
			break;
		case types::eNanoSecond :
			switch(resolution)
			{
			case types::eMilliSecond :
				// milli vs nano
				truePeriod = period * 1000000;
				break;
			case types::eMicroSecond :
				// micro vs nano
				truePeriod = period * 1000;
				break;
			default :
				break;
			}
			break;
		default :
			break;
		}
	}
	return truePeriod;
}

