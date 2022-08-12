#include <Arduino.h>
#include "terminal.h"
#include "printer.h"

bool escape_sequence = false;
uint8_t bytes_after_escape = 0;
enum escape_type {
    ESCAPE_CSI,
    ESCAPE_DCS,
    ESCAPE_OSC
} current_escape;

int flowcontrol_period = 200;
unsigned long last_time = 0;


void handle_serial()
{
    if (flowcontrol)
    {
        if (millis() - last_time > flowcontrol_period)
        {
            last_time = millis();
            flowcontrol--;
            //Serial.print("FC: ");
            //Serial.println(flowcontrol);
        }
    }
    
    if (Serial.available() && flowcontrol == 0)
	{
		char data = Serial.read();

        // Escape sequence
        if (data == '\x1B' /* ESC */)
        {
            escape_sequence = true;
            bytes_after_escape = 0;
        }

        if (!escape_sequence)
        {
            print_char(data);
        }
        else
        {
            bytes_after_escape++;

            // What type of escaped message?
            if (bytes_after_escape == 1)
            {
                if (data == '[') // CSI - Control Sequence Introducer
                {
                    current_escape = ESCAPE_CSI;
                }
                if (data == 'P') // DCS - Device Control String
                {
                    current_escape = ESCAPE_DCS;
                }
                if (data == ']') // OSC - Operating System Command
                {
                    current_escape = ESCAPE_OSC;
                }
            }
            else
            {
                if (current_escape == ESCAPE_CSI)
                {
                    if ((data >= 'A' && data <= 'Z') || (data >= 'a' && data <= 'z'))
                    {
                        escape_sequence = false;
                    }
                }
            }
        }
		//strike_key(data, data2);
	}
}
