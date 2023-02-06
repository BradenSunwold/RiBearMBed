
#include <System/SystemTime.hpp>

using namespace sys::time;
using namespace types;


ReadExternalTimer32Bit_t SystemTime::mReadHwTimer = NULL;
ReadExternalTimer32Bit_t SystemTime::mReadSwTimer = NULL;

UnitOfTime SystemTime::mClockResolution = eMicroSecond;
unsigned long SystemTime::mClockFreqInHz = 0;
TimeCount SystemTime::mDeGlitchThreshold = 0;

// Public

/*
 * STATIC
 */
void SystemTime::Load(ReadExternalTimer32Bit_t readHwTimer, ReadExternalTimer32Bit_t readSwTimer,
					unsigned long clockFreqInHz)
{
	// Initialize interface to external timers
	mReadHwTimer = readHwTimer;
	mReadSwTimer = readSwTimer;

	// Set clock frequency and resolution
	mClockFreqInHz = clockFreqInHz;
	CalculateClockResolution();
}

/*
 * STATIC
 */
types::TimeCount SystemTime::GetTime()
{
	return GetAtomicTime();		// Call private helper functions
}

// Private

/*
 * STATIC
 */
types::TimeCount SystemTime::GetAtomicTime()
{
	// Read timers twice in order to verify a valid read
	uint32_t hwCount1 = (*mReadHwTimer)();
	uint32_t swCount1 = (*mReadSwTimer)();
	uint64_t count1 = (uint64_t)hwCount1 + ((uint64_t)swCount1 << 32);	// account for all timer overflows

	uint32_t hwCount2 = (*mReadHwTimer)();
	uint32_t swCount2 = (*mReadSwTimer)();
	uint64_t count2 = (uint64_t)hwCount2 + ((uint64_t)swCount2 << 32);	// account for all timer overflows

	return DeGlitchCounts(count1, count2);
}

/*
 * STATIC
 */
types::UnitOfTime SystemTime::GetClockResolution()
{
	return mClockResolution;
}

// Private

/*
 * STATIC
 */
void SystemTime::CalculateClockResolution()
{
	if(mClockFreqInHz >= 1000000000)
	{
		mClockResolution = eNanoSecond;
	}
	else if(mClockFreqInHz >= 1000000)
	{
		mClockResolution = eMicroSecond;
	}
	else if(mClockFreqInHz >= 1000)
	{
		mClockResolution = eMilliSecond;
	}
}

/*
 * STATIC
 */
types::TimeCount SystemTime::DeGlitchCounts(types::TimeCount count1, types::TimeCount count2)
{
	/*
	 * Have to atomically calculate the system time in case any timer interrupts were fired
	 * during the read of the sw timer.
	 *
	 * If interrupt is fired while reading sw timer then the effected count could return much
	 * larger than reality due to the hw timer being read at its max value and the sw timer
	 * being read after the interrupt causing it to count up 1 additional tick
	 */

	if(count1 > count2)
	{
		// Interrupt occurred during count1 reading
		return count2;
	}
	else if((count2 - count1) > mDeGlitchThreshold)
	{
		// If count2 is greater than count 1 by half an overflow interrupt occurred during count2 read
		return count1;
	}
	// both reads are ok but return most recent
	return count2;
}


