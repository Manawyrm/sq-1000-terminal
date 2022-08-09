#include <Arduino.h>
#include "config.h"
#include "printer.h"

void setup()
{
	Serial.begin(BAUD_RATE);
	Serial.setTimeout(5000);

	for (uint8_t i = 2; i < 18; i++)
	{
		pinMode(i, INPUT);
	}
}

void loop()
{
	/*Serial.println();
	Serial.print("Scan Pin:");
	while (!Serial.available());
	int scan_pin = Serial.parseInt();
	Serial.println();
	Serial.print("Return Pin:");
	while (!Serial.available());
	int return_pin = Serial.parseInt();
	Serial.println();
	
	if (scan_pin >= 2 && scan_pin <= 9 && return_pin >= 10 && return_pin <= 17)
	{
		Serial.print("SP:");
		Serial.print(scan_pin);
		Serial.print(" RP: ");
		Serial.print(return_pin);
		Serial.println();
		strike_key(scan_pin, return_pin);
	}*/

	/*for (int i = 10; i < 17; i++)
	{
		strike_key(7, i);
		Serial.print("Printing on ");
		Serial.println(i);
		//delay(500);
	}

	delay ( 10000 );
	*/

	/*strike_key(7, 12);
	delay(500);
	*/ 

	if (Serial.available())
	{
		char data = Serial.read();
		print_char(data);
		//strike_key(data, data2);
	}

	//delay(10);
}