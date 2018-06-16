#include <avr/sfr_defs.h>
#include <SPI.h>
#include "mcp_can.h"
#include "mj8x8.h"


const int KEY_CENTER = 7;
const int MCP2551_SLEEP_PIN = 9;
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

#define PID_ENGIN_PRM       0x0C
#define PID_VEHICLE_SPEED   0x0D
#define PID_COOLANT_TEMP    0x05

#define CAN_ID_PID          0x7DF

unsigned char PID_INPUT;
unsigned char getPid    = 0;

int key_center_pressed = 0;
unsigned char key_buf[8];


void set_mask_filt()
{
    CAN.init_Mask(0, 0, 0x00);
    CAN.init_Mask(1, 0, 0x00);

    CAN.init_Filt(0, 0, 0x00);
    CAN.init_Filt(1, 0, 0x00);

    CAN.init_Filt(2, 0, 0x00);
    CAN.init_Filt(3, 0, 0x00);
    CAN.init_Filt(4, 0, 0x00);
    CAN.init_Filt(5, 0, 0x00);
}

void sendPid(unsigned char __pid)
{
    unsigned char tmp[8] = {0x02, 0x01, __pid, 0, 0, 0, 0, 0};
    Serial.print("SEND PID: 0x");
    Serial.println(__pid, HEX);
    CAN.sendMsgBuf(CAN_ID_PID, 0, 8, tmp);
}

void setup()
{
    Serial.begin(9600);

		pinMode(MCP2551_SLEEP_PIN, OUTPUT);
		digitalWrite(MCP2551_SLEEP_PIN, LOW);

		pinMode(KEY_CENTER, INPUT);
		digitalWrite(KEY_CENTER, LOW);

		pinMode(11, OUTPUT);
		digitalWrite(11, LOW);

    while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))    // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
    set_mask_filt();
}


void loop()
{
    taskCanRecv();
    taskDbg();

    if(getPid)          // GET A PID
    {
        getPid = 0;
        sendPid(PID_INPUT);
        PID_INPUT = 0;
    }

		if (!digitalRead(KEY_CENTER) && !key_center_pressed)
		{
			Serial.println("center key press");
			key_center_pressed = 1;

			key_buf[0] = UTIL_LED_GREEN_BLINK_4X; // CMND_UTIL_LED
			CAN.sendMsgBuf( 0x02, 0, 1, key_buf, true); // blink test CAN message

			//key_buf[0] = 0x48; // CMND_DEVICE - DEV_LIGHT - front light
			//key_buf[1] = 0x90; // set intensity to 0x90 (0x10 past max - red will blink 2x)
			//CAN.sendMsgBuf( 0x02, 0, 2, key_buf, true); // device test command byte


		}

		if (digitalRead(KEY_CENTER) && key_center_pressed)
		{
			Serial.println("center key release");
			key_center_pressed = 0;

			//key_buf[0] = 0x48; // CMND_DEVICE - DEV_LIGHT - front light
			//key_buf[1] = 0x00; // set intensity to 0x00 (off)
			//CAN.sendMsgBuf( 0x02, 0, 2, key_buf, true); // device test command byte

		}
}

void taskCanRecv()
{
    unsigned char len = 0;
    unsigned char buf[8];
    unsigned char data[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())                   // check if get data
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        Serial.println("\r\n------------------------------------------------------------------");
        Serial.print("RAW start - Get Data From id: ");
        Serial.print(CAN.getCanId(), HEX);
				Serial.print(" - ");
        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print("0x");
            Serial.print(buf[i], HEX);
            Serial.print(" - ");
        }
        Serial.print(" - RAW end\n");

              //if (buf[0] & ( _BV(BUTTON) ) && buf[1] > 0x00 )
              //{
                //Serial.print("lamp on\n");
//
								//// FIXME: to both lamps the last hex argument gets passed; the one before (front light command) gets overridden
                //buf[0] = 0x00;
								//buf[0] = _BV(FRONT_LIGHT); // command
                //buf[1] = 0x20; // argument
								//Serial.print("cmd - \t");Serial.print(buf[0], HEX);Serial.print(" - arg - ");Serial.println(buf[1], HEX);
                //CAN.sendMsgBuf( 0x02, 0, 2, buf, true);
								//buf[1] = 0;
//
                //buf[0] = 0x00;
								//buf[0] = _BV(REAR_LIGHT); // command
                //buf[1] = 0xff; // argument
                //Serial.print("cmd - \t");Serial.print(buf[0], HEX);Serial.print(" - arg - ");Serial.println(buf[1], HEX);
                //CAN.sendMsgBuf( 0x02, 0, 2, buf, true);
								//buf[1] = 0;
//
//
              //}

							//if (buf[0] & ( _BV(BUTTON) ) && buf[1] == 0x00 )
							//{
                //Serial.print("lamp off\n");
//
//
//
								//// FIXME: to both lamps the last hex argument gets passed; the one before (front light command) gets overridden
                //buf[0] = 0x00;
								//buf[0] = _BV(REAR_LIGHT); // command
								//buf[1] = 0x10; // argument
								//Serial.print("cmd - \t");Serial.print(buf[0], HEX);Serial.print(" - arg - ");Serial.println(buf[1], HEX);
								//CAN.sendMsgBuf( 0x02, 0, 2, buf, true);
								//buf[1] = 0;
//
                //buf[0] = 0x00;
								//buf[0] = _BV(FRONT_LIGHT); // command
                //buf[1] = 0x3; // argument
								//Serial.print("cmd - \t");Serial.print(buf[0], HEX);Serial.print(" - arg - ");Serial.println(buf[1], HEX);
                //CAN.sendMsgBuf( 0x02, 0, 2, buf, true);
								//buf[1] = 0;
//
							//}

        Serial.println();
    }
}

void taskDbg()
{
    while(Serial.available())
    {
        char c = Serial.read();

        if(c>='0' && c<='9')
        {
            PID_INPUT *= 0x10;
            PID_INPUT += c-'0';

        }
        else if(c>='A' && c<='F')
        {
            PID_INPUT *= 0x10;
            PID_INPUT += 10+c-'A';
        }
        else if(c>='a' && c<='f')
        {
            PID_INPUT *= 0x10;
            PID_INPUT += 10+c-'a';
        }
        else if(c == '\n')      // END
        {
            getPid = 1;
        }
    }
}
// END FILE
