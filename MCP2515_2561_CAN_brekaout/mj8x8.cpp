#include "mj8x8.h"

mj818::mj818(void)
{
	;
}

 mj818::mj818(MCP_CAN in_can)
{
	this->_can = in_can;
}

void mj818::shine(uint8_t ocr)
{
	this->_dlc = 2; // known length
	this->_data[0] = (CMND_DEVICE | DEV_LIGHT | REAR_LIGHT); // prepare command

	if ( ocr >= OCR_MAX_REAR_LIGHT) // safeguard against too high a value
	this->_data[1] = OCR_MAX_REAR_LIGHT; // max. safe value with rev.2 board
	else
	this->_data[1] = ocr;

	this->_can.sendMsgBuf(0x02, 0, this->_dlc, this->_data, true);
}

void mj818::brake_light(uint8_t ocr)
{
	this->_dlc = 2; // known length
	this->_data[0] = (CMND_DEVICE | DEV_LIGHT | BRAKE_LIGHT); // prepare command

	if (ocr > OCR_MAX_BRAKE_LIGHT) // safeguard against too high a value
		this->_data[1] = OCR_MAX_BRAKE_LIGHT; // max. safe value with rev.2 board
	else
		this->_data[1] = ocr;

	this->_can.sendMsgBuf( 0x02, 0, this->_dlc, this->_data, true);
}

mj808::mj808(void)
{
	this->_ocr_current = 0x00; // initialize to 0
	this->_ocr_requested = 0x00; // initialize to 0
}

 mj808::mj808(MCP_CAN in_can)
{
	mj808(); // call default constructor
	this->_can = in_can;
}

void mj808::shine(uint8_t ocr)
{
	this->_dlc = 2; // known length
	this->_data[0] = (CMND_DEVICE | DEV_LIGHT | FRONT_LIGHT); // prepare command

	if ( ocr >= OCR_MAX_FRONT_LIGHT) // safeguard against too high a value
		this->_data[1] = OCR_MAX_FRONT_LIGHT; // max. safe value with rev.2 board
	else
		this->_data[1] = ocr;

	this->_can.sendMsgBuf(0x02, 0, this->_dlc, this->_data, true);
	this->_ocr_current = ocr; // class-wide setting of ocr
}

void mj808::high_beam(uint8_t ocr) // brightens up the front lamp - aka high beam light
{
	this->_dlc = 2; // known length
	this->_data[0] = (CMND_DEVICE | DEV_LIGHT | FRONT_LIGHT_HIGH); // prepare command

	if (ocr > _ocr_current) // get brighter
	{
		if ( ocr >= OCR_MAX_FRONT_LIGHT) // safeguard against too high a value
			this->_data[1] = OCR_MAX_FRONT_LIGHT; // max. safe value with rev.2 board
		else
			this->_data[1] = ocr;
	}

	if (ocr <= _ocr_current) // ocr == 0x00 is the special case - it is not neccesarily off
		this->_data[1] = _ocr_current; // get dimmer

	this->_can.sendMsgBuf( 0x02, 0, this->_dlc, this->_data, true);
}

// lets util LED blink up to 6 times either red or green
void mj808::util_led_blink(uint8_t color, uint8_t count)
{
	if (!count) // count is 0 - turn off command
	{
		this->util_led_off(color); // jump
		return; // && get out
	}

	if (count >= 7) // count is bigger than 7 - turn on command
	{
		this->util_led_on(color); // jump
		return; // && get out
	}

	// from here on we have the normal count to deal with

	this->_dlc = 1; // known length

	this->_data[0] = CMND_UTIL_LED; // utility LED command

	if (color == RED) // if the color is red
		this->_data[0] |= RED; // AND the #define'd red bit

	if (count > 6) // 6 is max....
		count = 6;

	this->_data[0] |= count; // AND the count

	this->_can.sendMsgBuf( 0x02, 0, this->_dlc, this->_data, true); // send the command
}

// turns either green or red util. LED off
void mj808::util_led_off(uint8_t color)
{
	this->_dlc = 1; // known length

	if (color == RED) // if the color is red
		this->_data[0] = UTIL_LED_RED_OFF; // set off command

	if (color == GREEN) // if the color is green
		this->_data[0] = UTIL_LED_GREEN_OFF; // set off command

	this->_can.sendMsgBuf(0x02, 0, this->_dlc, this->_data, true); // send the command
}

// turns either green or red util. LED on
void mj808::util_led_on(uint8_t color)
{
	this->_dlc = 1; // known length

	if (color == RED) // if the color is red
		this->_data[0] = UTIL_LED_RED_ON; // set on command

	if (color == GREEN) // if the color is green
		this->_data[0] = UTIL_LED_GREEN_ON; // set on command

	this->_can.sendMsgBuf(0x02, 0, this->_dlc, this->_data, true); // send the command
}