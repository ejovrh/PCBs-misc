#ifndef MJ8X8_H_
#define MJ8X8_H_


#define OCR_FRONT_LIGHT OCR1A // Output Compare Register for PWM of front light
#define GREEN_LED 0 // green led
#define RED_LED 1 // red led
#define FADE_DOWN 0 // fade direction down
#define FADE_UP 1 // fade direction up
#define BLINK_DELAY 125

#define CAN_IN can_msg_incoming
#define CAN_OUT can_msg_outgoing
#define COMMAND data[0]
#define ARGUMENT data[1]

// command byte structure
#define CMND_UTIL_LED 0x10 // command for utility LED operation (color, on, off, blink)
#define CMND_POS_LED 0x40 // command for positional LED operation (front, rear, brake light on/off, fade)
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


#endif /* MJ8X8_H_ */