#include <Arduino.h>

void setup()
{
	Serial.begin(300);
	Serial.setTimeout(5000);

	for (uint8_t i = 2; i < 10; i++)
	{
		pinMode(i, INPUT);
	}
	for (uint8_t i = 10; i < 18; i++)
	{
		pinMode(i, INPUT);
	}
}

unsigned long curtime = 0;

void strike_key(uint8_t scan_pin, uint8_t return_pin)
{
	digitalWrite(scan_pin, HIGH);
	curtime = millis();
	while (millis() < curtime + 30)
	{
		if (digitalRead(scan_pin) == LOW)
		{
			pinMode(return_pin, OUTPUT);
			while (digitalRead(scan_pin) == LOW) {}
			pinMode(return_pin, INPUT);
		}
	}
	digitalWrite(scan_pin, LOW);
	delay(60);
}

void strike_key_shift(uint8_t scan_pin, uint8_t return_pin)
{
	digitalWrite(7, HIGH);
	digitalWrite(scan_pin, HIGH);
	curtime = millis();
	while (millis() < curtime + 30)
	{

		pinMode(return_pin, digitalRead(scan_pin) == LOW);

	}
	digitalWrite(scan_pin, LOW);
	digitalWrite(7, LOW);

	delay(60);
}



void print_char(char c)
{
	switch (c)
	{
		case 'A': strike_key_shift(7, 10); break;
		case 'B': strike_key_shift(8, 13); break;
		case 'C': strike_key_shift(8, 12); break;


		case 'a': strike_key(7, 10); break;
		case 'b': strike_key(8, 13); break;
		case 'c': strike_key(8, 12); break;
		case 'd': strike_key(6, 11); break;
		case 'e': strike_key(5, 11); break;
		case 'f': strike_key(7, 12); break;
		case 'g': strike_key(6, 12); break;
		case 'h': strike_key(7, 13); break;
		case 'i': strike_key(4, 14); break;
		case 'j': strike_key(6, 13); break;
		case 'k': strike_key(7, 14); break;
		case 'l': strike_key(6, 14); break;
		case 'm': strike_key(8, 14); break;
		case 'n': strike_key(9, 14); break;
		case 'o': strike_key(5, 14); break;
		case 'p': strike_key(4, 15); break;
		case 'q': strike_key(5, 10); break;
		case 'r': strike_key(4, 12); break;
		case 's': strike_key(7, 11); break;
		case 't': strike_key(5, 12); break;
		case 'u': strike_key(5, 13); break;
		case 'v': strike_key(9, 13); break;
		case 'w': strike_key(4, 11); break;
		case 'x': strike_key(8, 11); break;
		case 'y': strike_key(8, 10); break;
		case 'z': strike_key(4, 13); break;

		case '.': strike_key(8, 15); break;
		case '-': strike_key(8, 16); break;
		case ',': strike_key(9, 15); break;
		case ' ': strike_key(9, 16); break;
		case '+': strike_key(4, 16); break;

		case '0': strike_key(3, 15); break;
		case '1': strike_key(2, 10); break;
		case '2': strike_key(3, 11); break;
		case '3': strike_key(2, 11); break;
		case '4': strike_key(3, 12); break;
		case '5': strike_key(2, 12); break;
		case '6': strike_key(3, 13); break;
		case '7': strike_key(2, 13); break;
		case '8': strike_key(3, 14); break;
		case '9': strike_key(2, 14); break;

		case '\n': strike_key(7, 17); break;
		case '\b': strike_key(3, 17); break;

		default: break;
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