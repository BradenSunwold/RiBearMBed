
#include <Components/SpeedSensor.hpp>


SpeedSensor::SpeedSensor()
		:
		mWheelCircum(11),		// Default assumed values
		mNumSensors(1),			// Default to 1 sensor
		mDataInKm(true),		// Default to kph
		mSensorTicks(0),
		mTickOverflow(0),
		mTimerRateInHz(25),		// Default assumed 25Hz
		mLastDistance(0),
		mDataRdy(false),
		mWspd(0),
		mTrip(0),
		mOdom(0)
{
}

SpeedSensor::SpeedSensor(float wspd, uint32_t trip, uint32_t odom)
		:
		mWheelCircum(11),
		mNumSensors(1),
		mDataInKm(true),
		mSensorTicks(0),
		mTickOverflow(0),
		mTimerRateInHz(25),
		mLastDistance(0),
		mDataRdy(false),
		mWspd(wspd),
		mTrip(trip),
		mOdom(odom)
{
}

SpeedSensor::SpeedSensor(float wheelCircum, int numSensors,uint32_t totalTicks,
									bool dataInKm, uint32_t timerRateHz, float wspd,
															uint32_t trip, uint32_t odom)
		:
		mWheelCircum(wheelCircum),
		mNumSensors(numSensors),
		mDataInKm(dataInKm),
		mSensorTicks(0),
		mTickOverflow(0),
		mTimerRateInHz(timerRateHz),
		mLastDistance(0),
		mDataRdy(false),
		mWspd(wspd),
		mTrip(trip),
		mOdom(odom)
{
}

void SpeedSensor::UpdateInstrumentData()
{
	// Check if we have seen any new sensor ticks since last interrupt
	if(mSensorTicks == 0)
	{
		mTickOverflow++;
	}
	// Else there is new data so calculate parameters
	else
	{
		// calculate distance taking into account how many sensors there are
		float distance = (mSensorTicks * mWheelCircum) / mNumSensors;

		// Update wheel speed and take into account any overflows
		mWspd = distance / ((1 / mTimerRateInHz) * mTickOverflow);

		// Only update the trip and odometer if 1 unit of distance has passed (km or miles)
		float oneUnitOfDistance = mDataInKm ? CM_TO_KM : CM_TO_MILES;

		if(mLastDistance += distance > oneUnitOfDistance)
		{
			mTrip++;
			mOdom++;

			// Clear previous distance to start looking for 1 unit of distance again
			mLastDistance = mLastDistance + distance - oneUnitOfDistance;
		}
		else
		{
			mLastDistance += distance;		// Save new previous distance until 1 unit of distance reached
		}

		mTickOverflow = 1;		// Reset tick overflow to 1 since saw valid tick
		mSensorTicks = 0;		// Reset sensor ticks for next time period

		mDataRdy = true;
	}
}

void SpeedSensor::IncrementSpeedTicks()
{
	mSensorTicks++;
}

void SpeedSensor::ClearDataRdy()
{
	mDataRdy = false;
}

void SpeedSensor::SetWheelCircum(float newWheelCircum)
{
	mWheelCircum = newWheelCircum;
}

void SpeedSensor::SetSensorNum(uint16_t newSensorNum)
{
	mNumSensors = newSensorNum;
}

void SpeedSensor::SetDataInKm(bool dataInKm)
{
	mDataInKm = dataInKm;
}

bool SpeedSensor::GetDataRdy()
{
	return mDataRdy;
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

