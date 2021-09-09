
#ifndef DISPLAYCOMMANDMESSAGE_HPP_
#define DISPLAYCOMMANDMESSAGE_HPP_

#include <Types/StdTypeDefs.hpp>

class DisplayCommandMessage
{
	// Define structure to hold wheel speed, trip and odometer values
	struct instrumentData {
		  float wspd;
		  uint32_t trip;
		  uint32_t odom;
	};

public:
	DisplayCommandMessage();
	DisplayCommandMessage(float wsp, uint32_t trip, uint32_t odom);

	void Serialize(char* buffer, types::endian_t endianType);
	void LoadMessageData(float wspd, uint32_t trip, uint32_t odom);

	// Setters
	void setWspd(float wsp);
	void setTrip(uint32_t trip);
	void setOdom(uint32_t odom);

	// Getter
	float getWspd();
	uint32_t getTrip();
	uint32_t getOdom();

private:
	instrumentData mInstrumentData;

};

#endif /* DISPLAYCOMMANDMESSAGE_HPP_ */
