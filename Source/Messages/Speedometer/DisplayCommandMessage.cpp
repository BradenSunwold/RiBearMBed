
#include <Messages/Speedometer/DisplayCommandMessage.hpp>

using namespace types;

DisplayCommandMessage::DisplayCommandMessage()
{
	mInstrumentData.wspd = 0;
	mInstrumentData.trip = 0;
	mInstrumentData.odom = 0;
}

DisplayCommandMessage::DisplayCommandMessage(float wsp, uint32_t trip, uint32_t odom)
{
	mInstrumentData.wspd = wsp;
	mInstrumentData.trip = trip;
	mInstrumentData.odom= odom;
}

void DisplayCommandMessage::Serialize(char* buffer, types::endian_t endianType)
{
	// Serialize data - float to byte works for uint32_t since both 4 bytes
	FloatToBytes(mInstrumentData.wspd, endianType, buffer, 0);
	FloatToBytes(mInstrumentData.trip, endianType, buffer, 4);
	FloatToBytes(mInstrumentData.odom, endianType, buffer, 8);
}

void DisplayCommandMessage::LoadMessageData(float wspd, uint32_t trip, uint32_t odom)
{
	mInstrumentData.wspd = wspd;
	mInstrumentData.trip = trip;
	mInstrumentData.odom = odom;
}

void DisplayCommandMessage::setWspd(float wsp)
{
	mInstrumentData.wspd= wsp;
}

void DisplayCommandMessage::setTrip(uint32_t trip)
{
	mInstrumentData.trip = trip;
}

void DisplayCommandMessage::setOdom(uint32_t odom)
{
	mInstrumentData.odom = odom;
}

float DisplayCommandMessage::getWspd()
{
	return mInstrumentData.wspd;
}

uint32_t DisplayCommandMessage::getTrip()
{
	return mInstrumentData.trip;
}

uint32_t DisplayCommandMessage::getOdom()
{
	return mInstrumentData.odom;
}

