
#include <Components/SpeedSensor.hpp>


SpeedSensor::SpeedSensor()
		:
		mWheelCircum(85),
		mNumSensors(2),
		mPreviousTime(0),
		mTotalTicks(0),
		mDataInMiles(true),
		mWspd(0),
		mTrip(0),
		mOdom(0)
{
	CalculateDistanceInTicks();
}

SpeedSensor::SpeedSensor(float wspd, uint32_t trip, uint32_t odom)
		:
		mWheelCircum(85),
		mNumSensors(2),
		mPreviousTime(0),
		mTotalTicks(0),
		mDataInMiles(true),
		mWspd(wspd),
		mTrip(trip),
		mOdom(odom)
{
	CalculateDistanceInTicks();
}

SpeedSensor::SpeedSensor(float wheelCircum, int numSensors, types::TimeCount previousTime,
		 	 	 	 	uint32_t totalTicks, bool dataInMiles, float wspd, uint32_t trip,
						uint32_t odom)
		:
		mWheelCircum(wheelCircum),
		mNumSensors(numSensors),
		mPreviousTime(previousTime),
		mTotalTicks(totalTicks),
		mDataInMiles(dataInMiles),
		mWspd(wspd),
		mTrip(trip),
		mOdom(odom)
{
	CalculateDistanceInTicks();
}

void SpeedSensor::UpdateInstrumentData(types::TimeCount currentTime)
{
	// Update total ticks every time function is called from ISR
	mTotalTicks++;

	// Update wheel speed
	float distance = (mWheelCircum/mNumSensors);	// calculate distance between sensors in inches
	types::TimeCount period = currentTime - mPreviousTime;
	mWspd = distance / period;

	// Update previous time
	mPreviousTime = currentTime;

	if((mPreviousDistance + distance) >= mDistanceUnitInInches)
	{
		// Update all trip info since we traveled 1 unit of distance
		mTrip++;
		mOdom++;

		mPreviousDistance = 0;    // reset previousDistance to 0
	}
	else
	{
		// Add to previous distance
		mPreviousDistance =+ distance;
	}
}

float SpeedSensor::GetWspd()
{
	return mWspd;
}

int SpeedSensor::GetTrip()
{
	return mTrip;
}

int SpeedSensor::GetOdom()
{
	return mOdom;
}

void SpeedSensor::CalculateDistanceInTicks()
{
	// If data in miles then calculate how many inches / ticks = 1 mile
	if(mDataInMiles)
	{
		mDistanceUnitInInches = 63360;
	}
	else
	{
		// else measured in kilometers - calculate inches / ticks = 1 km
		mDistanceUnitInInches = 39370.1;
	}
	mDistanceUnitInTicks = mDistanceUnitInInches / (mWheelCircum / mNumSensors);
}


