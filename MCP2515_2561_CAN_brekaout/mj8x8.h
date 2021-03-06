#ifndef MJ8x8_H_
#define MJ8x8_H_

#include <stdint-gcc.h>

#include "mcp_can.h"

// what device to compile for?
#define MJ818_

// OCR defines
#define OCR_FRONT_LIGHT OCR1A // Output Compare Register for PWM of front light
#define OCR_REAR_LIGHT OCR0A // Output Compare Register for PWM of rear light
#define OCR_BRAKE_LIGHT OCR1A // Output Compare Register for PWM of brake light

	/* MJ818 - rear & brake light
		timer/counter 0 and timer/counter 1 both operate in 8bit mode
		hex val. - duty cycle - current backlight - current brake light
		0x00 - 0% (off)				-	20 mA -	20 mA
		0x10 - 6.26%					-	20 mA - 20 mA
		0x20 - 12.5%					-	20 mA -	30
		0x40 - 25.05%					-	30 mA -	50
		0x80 - 50.1%					-	50 mA -	90
		0xA0 - 62.6%					-	50 mA -	110
		0xC0 - 75.15%					-	60 mA -	130
		0xE0 - 87.84%					-	70 mA -	150
		0xF0 - 94.12%					- 70 mA -	160
		0xFF - 100% (max)			-	80 mA -	170

		0xFF OCR0A MAX. SAFE COUNT WITH REV2 BOARD
		0x80 OCR1A MAX. SAFE COUNT WITH REV2 BOARD

*/
	/* MJ808 - front light
		timer/counter 0 and timer/counter 1 both operate in 8bit mode
		hex val. - duty cycle - current front light
		0x00 - 0% (off)				-	20 mA
		0x10 - 6.26%					-	20 mA
		0x20 - 12.5%					-	30 mA
		0x40 - 25.05%					-	60 mA
		0x80 - 50.1%					-	100 mA
		0xA0 - 62.6%					-	120 mA
		0xC0 - 75.15%					-	150 mA
		0xE0 - 87.84%					-	170 mA
		0xF0 - 94.12%					-	180 mA
		0xFF - 100% (max)			-	200 mA

		0x80 MAX. SAFE COUNT WITH REV2 BOARD -- with this the FET is dangerously hot
		0x40 is less stressing
*/

// maximum safe values for light OCRs
#define OCR_MAX_FRONT_LIGHT 0x80 // max. OCR1A count limit for front light PWM
#define OCR_MAX_REAR_LIGHT 0xFF // max. OCR0A count limit for rear light PWM - the sky is the limit
#define OCR_MAX_BRAKE_LIGHT 0x80 // max. OCR1A count limit for brake light PWM

#define LED_OFF 0x00 // off value for any OCR
#define BLINK_DELAY 125

#define CAN_IN can_msg_incoming
#define CAN_OUT can_msg_outgoing
#define COMMAND data[0]
#define ARGUMENT data[1]

// command byte structure
#define CMND_ANNOUNCE 0x00 // command to register self on other devices (announce-like broadcast)
	#define DEV_0A 0 // main (1st) logic unit
		#define LU 0
	#define DEV_0B 1 //	2nd logic unit
	#define DEV_0C 2 //	3rd logic unit
	#define DEV_0D 3 //	4th logic unit
	#define DEV_1A 4 //	dynamo1
		#define DYN1 4
	#define DEV_1B 5 //	dynamo2
		#define DYN2 5
	#define DEV_1C 6 //	battery
		#define BATT 6
	#define DEV_1D 7 //	solar cell
	#define DEV_2A 8 //	mj808
		#define MJ808 8
	#define DEV_2B 9 //	mj818
		#define MJ818 9
	#define DEV_2C 10 //	??
	#define DEV_2D 11 //	??
	#define DEV_3A 12 //	cadence
	#define DEV_3B 13 //	radar
	#define DEV_3C 14 //	??
	#define DEV_3D 15 //	??
#define CMND_UTIL_LED 0x10 // command for utility LED operation (color, on, off, blink)
	#define GREEN 0x00
	#define RED 0x08
	#define UTIL_LED_GREEN_OFF 0x10 // utility LED - off
	#define UTIL_LED_GREEN_ON 0x17 // utility LED - on
	#define UTIL_LED_GREEN_BLINK_1X 0x11 // utility LED - blink
	#define UTIL_LED_GREEN_BLINK_2X 0x12 // utility LED - blink
	#define UTIL_LED_GREEN_BLINK_3X 0x13 // utility LED - blink
	#define UTIL_LED_GREEN_BLINK_4X 0x14 // utility LED - blink
	#define UTIL_LED_GREEN_BLINK_5X 0x15 // utility LED - blink
	#define UTIL_LED_GREEN_BLINK_6X 0x16 // utility LED - blink
	#define UTIL_LED_RED_OFF 0x18 // utility LED - off
	#define UTIL_LED_RED_ON 0x1F // utility LED - on
	#define UTIL_LED_RED_BLINK_1X 0x19 // utility LED - blink
	#define UTIL_LED_RED_BLINK_2X 0x1A // utility LED - blink
	#define UTIL_LED_RED_BLINK_3X 0x1B // utility LED - blink
	#define UTIL_LED_RED_BLINK_4X 0x1C // utility LED - blink
	#define UTIL_LED_RED_BLINK_5X 0x1D // utility LED - blink
	#define UTIL_LED_RED_BLINK_6X 0x1E // utility LED - blink
#define CMND_DEVICE 0x40 // command for device (00 - logic unit, 01 - power sources, 02 - lights, 03 sensors)
	#define DEV_LU 0x00 // logic unit device
	#define DEV_PWR_SRC 0x04 // power source device
	#define DEV_LIGHT 0x08 // positional light device
			#define FRONT_LIGHT 0x00 // front positional light (mj808) - low beam
			#define FRONT_LIGHT_HIGH 0x01 // front positional light (mj808) - high beam
			#define REAR_LIGHT 0x02 // rear positional light (mj818)
			#define BRAKE_LIGHT 0x03 // brake light (mj818)
	#define DEV_SENSOR 0x0C // sensor device
#define CMND_FW_FLASH 0x70 // command for flashing firmware
#define MSG_TIME_SYNC 0x80 // time synchronization message
#define MSG_BUTTON_EVENT 0x90 // message for button events
	#define BUTTON0_OFF 0x00 // button n off
	#define BUTTON0_ON 0x01 // button n on
	#define BUTTON1_OFF 0x02
	#define BUTTON1_ON 0x03
	#define BUTTON2_OFF 0x04
	#define BUTTON2_ON 0x05
	#define BUTTON3_OFF 0x06
	#define BUTTON3_ON 0x07
	#define BUTTON4_OFF 0x08
	#define BUTTON4_ON 0x09
	#define BUTTON5_OFF 0x0A
	#define BUTTON5_ON 0x0B
	#define BUTTON6_OFF 0x0C
	#define BUTTON6_ON 0x0D
	#define BUTTON7_OFF 0x0E
	#define BUTTON7_ON 0x0F
#define MSG_MEASUREMENT_DATA 0xD0 // message containing various measurements
#define MSG_BUS 0xF0 // CAN bus related control messages

#define LED_FRONT 0x00 // ID for front light
#define LED_REAR 0x02 // ID for rear light
#define LED_BREAK 0x03 // ID for brake light

//bit fields for command byte
//	B7:B5 are command nibbles and not broken down further
#define B3 3
#define B2 2
#define B1 1
#define B0 0

// SID defines, must be manually left shifted by 5 (MCP2515 datasheet, p.29 & 30)
// b7
#define PRIORITY_LOW 0x80 // default 0, used by the sender, leave zero on self, except with logic unit 0A (defaults to 1)
#define PRIORITY_HIGH 0x00
// b6
#define BROADCAST 0x40 // default 0, used by the sender
#define UNICAST 0x00
// b5:4
#define SENDER_DEV_CLASS_SENSOR 0x30 // sender device class, always populate on self
#define SENDER_DEV_CLASS_LIGHT 0x20
#define SENDER_DEV_CLASS_PWR_SRC 0x10
#define SENDER_DEV_CLASS_LU 0x00
#define SENDER_DEV_CLASS_BLANK 0x00
// b3:2
#define SENDER_DEV_D 0x0C // sender device ID, always populate on self
#define SENDER_DEV_C 0x08
#define SENDER_DEV_B 0x04
#define SENDER_DEV_A 0x00
#define SENDER_DEV_BLANK 0x00
// b1:0
#define RCPT_DEV_CLASS_SENSOR 0x03 // recipient device class, populate when sending, on self use RCPT_DEV_BLANK
#define RCPT_DEV_CLASS_LIGHT 0x02
#define RCPT_DEV_CLASS_PWR_SRC 0x01
#define RCPT_DEV_CLASS_LU 0x00
#define RCPT_DEV_CLASS_BLANK 0x00

// b7:6
#define RCPT_DEV_D 0xC0 // recipient device ID, populate when sending, on self use RCPT_DEV_BLANK
#define RCPT_DEV_C 0x80
#define RCPT_DEV_B 0x40
#define RCPT_DEV_A 0x00
#define RCPT_DEV_BLANK 0x00
// b5
#define BLANK 0x00

class SID
{
	public:
		SID();
		SID(uint8_t h, uint8_t l);
		uint16_t get(void);

	private:
		uint8_t h;
		uint8_t l;
};

class mj8x8
{
	public:
		virtual void shine(uint8_t ocr) = 0;

	//protected:
			//MCP_CAN can;
			//uint8_t sidh;
			//uint8_t sidl;
			//uint8_t dlc;
			//uint8_t data[8];
};

class mj808 : public mj8x8
{
	public:
		mj808();
		mj808(MCP_CAN in_can);

		void shine(uint8_t ocr) final;
		void high_beam(uint8_t ocr); // brightens up the front lamp - aka high beam light
		void util_led_blink(uint8_t color, uint8_t count); // lets util LED blink up to 6 times either red or green
		void util_led_off(uint8_t color); // turns either green or red util. LED off
		void util_led_on(uint8_t color); // turns either green or red util. LED on

	private:
			MCP_CAN _can;
			SID _sid;
			uint8_t _dlc;
			uint8_t _data[8];
			uint8_t _ocr_current;
			uint8_t _ocr_requested;
};



class mj818 : public mj8x8
{
	public:
		mj818();
		mj818(MCP_CAN in_can);

		void shine(uint8_t ocr) final;
		void brake_light(uint8_t ocr);

	private:
			MCP_CAN _can;
			SID _sid;
			uint8_t _dlc;
			uint8_t _data[8];
};

#endif /* MJ8x8_H_ */