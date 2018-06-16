#ifndef MJ808_H_
#define MJ808_H_

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

#define BLINK_DELAY 125

#define CAN_IN can_msg_incoming
#define CAN_OUT can_msg_outgoing
#define COMMAND data[0]
#define ARGUMENT data[1]

// command byte structure
#define CMND_UTIL_LED 0x10 // command for utility LED operation (color, on, off, blink)
#define CMND_DEVICE 0x40 // command for device (00 - logic unit, 01 - power sources, 02 - lights, 03 sensors)
	#define DEV_LU 0x00 // logic unit device
	#define DEV_PWR_SRC 0x04 // power source device
	#define DEV_LIGHT 0x08 // positional light device
			#define FRONT_LIGHT 0x00 // front positional light (mj808)
			#define TO_BE_DEFINED_LIGHT 0x01 // to be defined
			#define REAR_LIGHT 0x02 // rear positional light (mj818)
			#define BRAKE_LIGHT 0x03 // brake light (mj818)
	#define DEV_SENSOR 0x0C // sensor device
#define CMND_FW_FLASH 0x70 // command for flashing firmware
#define MSG_TIME_SYNC 0x80 // time synchronization message
#define MSG_BUTTON_EVENT 0x90 // message for button events
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

// defines for utility LED operation
#define UTIL_LED_GREEN_OFF 0x00
#define UTIL_LED_GREEN_ON 0x17
#define UTIL_LED_GREEN_BLINK_1X 0x11
#define UTIL_LED_GREEN_BLINK_2X 0x12
#define UTIL_LED_GREEN_BLINK_3X 0x13
#define UTIL_LED_GREEN_BLINK_4X 0x14
#define UTIL_LED_GREEN_BLINK_5X 0x15
#define UTIL_LED_GREEN_BLINK_6X 0x16
#define UTIL_LED_RED_OFF 0x18
#define UTIL_LED_RED_ON 0x1F
#define UTIL_LED_RED_BLINK_1X 0x19
#define UTIL_LED_RED_BLINK_2X 0x1A
#define UTIL_LED_RED_BLINK_3X 0x1B
#define UTIL_LED_RED_BLINK_4X 0x1C
#define UTIL_LED_RED_BLINK_5X 0x1D
#define UTIL_LED_RED_BLINK_6X 0x1E


#endif /* MJ808_H_ */