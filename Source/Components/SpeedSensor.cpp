
#include <Components/SpeedSensor.hpp>

SpeedSensor::SpeedSensor()
	: mWspd(0), mTrip(0), mOdom(0), mFrameTime(0), mPrevDistance(0), mCurrentDistance(0), mWheelCircum(0),
	  mNumSensors(2), mMileInTicks(0)
{
}

SpeedSensor::SpeedSensor(float wspd, int trip, int odom)
	: mWspd(wspd), mTrip(trip), mOdom(odom), mFrameTime(0), mPrevDistance(0), mCurrentDistance(0),
	  mWheelCircum(0), mNumSensors(2), mMileInTicks(0)
{
}

// TODO: Update frame time, mMilesInTicks and mWheelCircum to proper default values
SpeedSensor::SpeedSensor(float wspd, int trip, int odom, int frameTime, float wheelCircum, int numSensors, int mileInTicks)
	: mWspd(wspd), mTrip(trip), mOdom(odom), mFrameTime(frameTime), mPrevDistance(0), mCurrentDistance(0),
	  mWheelCircum(wheelCircum), mNumSensors(numSensors), mMileInTicks(mileInTicks)
{
}

void SpeedSensor::UpdateInstrumentData(int ticks)
{
	// Update wheel speed
	mCurrentDistance = (mWheelCircum / mNumSensors) * ticks;
	mPrevDistance = mCurrentDistance;							// Update previous distance reading
	mWspd = mCurrentDistance / mFrameTime;

	// Update trip mileage
	// TODO: Update to deal with int overflow
	if(mCurrentDistance <= mMileInTicks)
	{
		mTrip++;
		mOdom++;
		mPrevDistance = 0;
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

void SpeedSensor::SetFrameTime(int frameTime)
{
	mFrameTime = frameTime;
}

//void UpdateInstrumentData(uint32_t* totalTicks, float* wspd, int* odom, int* trip,
//		float wheelCircum, int numSensors, uint32_t ticks, int tipDistanceInTicks, float frameTime)
//{
//	// Update wheel speed
//	float currDistance = (wheelCircum / numSensors) * ticks;	// calculate distance traveled since last interupt
//
//	*wspd = currDistance / frameTime;
//	*totalTicks = *totalTicks + ticks;		// Calculate the total distance traveled so far in ticks
//
//	// Update trip mileage
//	if(*totalTicks >= tipDistanceInTicks)
//	{
//		*trip++;					// Have traveled one unit of distance so increment trip and odom
//		*odom++;
//		*totalTicks = 0;
//	}
//}
























