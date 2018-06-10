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
#define FOO3 7 // acknowledge bit: 1 ack ?
#define FOO2 6 //
#define FOO1 5 //
#define BUTTON 4 //
#define SIGNAL_LED 3 //
#define REAR_LIGHT 2 // expects 1 byte argument: off (0x00), on (0xff), PWM intensity (0x01 - 0xfe)
#define FRONT_LIGHT 1 // expects 1 byte argument: off (0x00), on (0xff), PWM intensity (0x01 - 0xfe)
#define BRAKE_LIGHT 0 // expects 1 byte argument: off (0x00), on (0xff), PWM intensity (0x01 - 0xfe)


#endif /* MJ8X8_H_ */