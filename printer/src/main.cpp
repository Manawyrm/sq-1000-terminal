#include <Arduino.h>
#include "config.h"
#include "printer.h"
#include "terminal.h"

void setup()
{
	Serial.begin(BAUD_RATE);
	Serial.setTimeout(5000);

	
	printer_setup();

	delay(10000);

	function_key_code(2, 13); // Set typewriter to Pitch 12
	//function_key_code(3, 14); // Set typewriter to Pitch 15
	function_key_code(8, 17); // Carriage return

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

	handle_serial();
	

	//delay(10);
}