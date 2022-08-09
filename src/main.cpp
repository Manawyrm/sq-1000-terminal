#include <Arduino.h>

#define BAUD_RATE 300
#define KEY_HOLD_MS 30
#define KEY_AFTER_DELAY_MS 90

#define SHIFT_MODIFIER_SCAN 9
#define SHIFT_MODIFIER_RETURN 10
#define CODE_MODIFIER_SCAN 9
#define CODE_MODIFIER_RETURN 12


void setup()
{
	Serial.begin(BAUD_RATE);
	Serial.setTimeout(5000);

	for (uint8_t i = 2; i < 18; i++)
	{
		pinMode(i, INPUT);
	}
}

unsigned long curtime = 0;

void strike_key(uint8_t scan_pin, uint8_t return_pin, uint8_t modifier_scan, uint8_t modifier_return)
{
	int pinState;

	if (modifier_scan)
	{
		digitalWrite(modifier_scan, HIGH);
	}
	digitalWrite(scan_pin, HIGH);

	if (modifier_scan)
	{
		curtime = millis();
		while (millis() < curtime + KEY_HOLD_MS)
		{
			pinMode(modifier_return, !digitalRead(modifier_scan));
		}
	}

	curtime = millis();
	bool key_fetched = false;
	while (millis() < curtime + KEY_HOLD_MS)
	{
		bool modifier_return_state;
		if (modifier_scan)
		{
			pinState = digitalRead(modifier_scan);
			modifier_return_state = !pinState;
		}

		// if both the modifier and the pin itself use the same return pin,
		// we need to logical-OR those together
		if (modifier_return == return_pin)
		{
			pinState = digitalRead(scan_pin);
			pinMode(return_pin, (!pinState) || modifier_return_state);
		}
		else
		{
			if (modifier_scan)
			{
				pinMode(modifier_return, !pinState);
			}
			pinState = digitalRead(scan_pin);
			pinMode(return_pin, !pinState);
		}

		
		if (!pinState)
		{
			key_fetched = true;
		}
	}
	
	if (modifier_scan)
	{
		pinMode(modifier_return, INPUT);
	}
	pinMode(return_pin, INPUT);
	digitalWrite(scan_pin, LOW);
	if (modifier_scan)
	{
		digitalWrite(modifier_scan, LOW);
	}

	delay(KEY_AFTER_DELAY_MS);
}

void strike_key(uint8_t scan_pin, uint8_t return_pin)
{
	strike_key(scan_pin, return_pin, 0, 0);
}

void strike_key_shift(uint8_t scan_pin, uint8_t return_pin)
{
	strike_key(scan_pin, return_pin, SHIFT_MODIFIER_SCAN, SHIFT_MODIFIER_RETURN);
}

void strike_key_code(uint8_t scan_pin, uint8_t return_pin)
{
	strike_key(scan_pin, return_pin, CODE_MODIFIER_SCAN, CODE_MODIFIER_RETURN);
}


void print_char(char c)
{
	switch (c)
	{
		// Upper case letters
		case 'A': strike_key_shift(7, 10); break;
		case 'B': strike_key_shift(8, 13); break;
		case 'C': strike_key_shift(8, 12); break;
		case 'D': strike_key_shift(6, 11); break;
		case 'E': strike_key_shift(5, 11); break;
		case 'F': strike_key_shift(7, 12); break;
		case 'G': strike_key_shift(6, 12); break;
		case 'H': strike_key_shift(7, 13); break;
		case 'I': strike_key_shift(4, 14); break;
		case 'J': strike_key_shift(6, 13); break;
		case 'K': strike_key_shift(7, 14); break;
		case 'L': strike_key_shift(6, 14); break;
		case 'M': strike_key_shift(8, 14); break;
		case 'N': strike_key_shift(9, 14); break;
		case 'O': strike_key_shift(5, 14); break;
		case 'P': strike_key_shift(4, 15); break;
		case 'Q': strike_key_shift(5, 10); break;
		case 'R': strike_key_shift(4, 12); break;
		case 'S': strike_key_shift(7, 11); break;
		case 'T': strike_key_shift(5, 12); break;
		case 'U': strike_key_shift(5, 13); break;
		case 'V': strike_key_shift(9, 13); break;
		case 'W': strike_key_shift(4, 11); break;
		case 'X': strike_key_shift(8, 11); break;
		case 'Y': strike_key_shift(8, 10); break;
		case 'Z': strike_key_shift(4, 13); break;

		// Lower case letters
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

		// Non-shift special characters
		case '.': strike_key(8, 15); break;
		case '-': strike_key(8, 16); break;
		case ',': strike_key(9, 15); break;
		case ' ': strike_key(9, 16); break;
		case '+': strike_key(4, 16); break;
		//case '´': strike_key(3, 16); break; // unicode char

		// Shifted special characters
		case '!': strike_key_shift(2, 10); break;
		case '"': strike_key_shift(3, 11); break;
		//case '§': strike_key_shift(2, 11); break; // unicode char
		case '$': strike_key_shift(3, 12); break;
		case '%': strike_key_shift(2, 12); break;
		case '&': strike_key_shift(3, 13); break;
		case '/': strike_key_shift(2, 13); break;
		case '(': strike_key_shift(3, 14); break;
		case ')': strike_key_shift(2, 14); break;
		case '=': strike_key_shift(3, 15); break;
		case '?': strike_key_shift(2, 15); break;
		case '*': strike_key_shift(4, 16); break;
		case '`': 
			// backticks don't advance the cursor on their own
			strike_key_shift(3, 16); 
			strike_key(9, 16);
			break;
		case ':': strike_key_shift(8, 15); break;
		case '_': strike_key_shift(8, 16); break;
		case ';': strike_key_shift(9, 15); break;

		// Code modified special characters
		case '|': strike_key_code(5, 14); break;
		//case '²':  break; // unicode char
		//case '³':  break; // unicode char
		//case '°':  break; // unicode char
		case '\'': strike_key_code(6, 15); break;
		case '#': strike_key_code(7, 15); break;
		case '>': strike_key_code(8, 15); break;
		case '<': strike_key_code(9, 15); break;
		//case 'µ': strike_key(8, 16); break;  // unicode char

		// Missing special characters / Workarounds
		case '[': 
			// enable underscored text
			strike_key_code(5, 13);
			// strike (
			strike_key_shift(3, 14);
			// disable underscored text
			strike_key_code(5, 13);
			break;
		case ']': 
			// enable underscored text
			strike_key_code(5, 13);
			// strike )
			strike_key_shift(2, 14);
			// disable underscored text
			strike_key_code(5, 13);
			break;

		case '{':
			// strike (
			strike_key_shift(3, 14);
			// go back
			strike_key(2, 16);
			// strike <
			strike_key_code(9, 15);
			break;

		case '}':
			// strike )
			strike_key_shift(2, 14);
			// go back
			strike_key(2, 16);
			// strike >
			strike_key_code(8, 15);
			break;

		// Digits
		case '1': strike_key(2, 10); break;
		case '2': strike_key(3, 11); break;
		case '3': strike_key(2, 11); break;
		case '4': strike_key(3, 12); break;
		case '5': strike_key(2, 12); break;
		case '6': strike_key(3, 13); break;
		case '7': strike_key(2, 13); break;
		case '8': strike_key(3, 14); break;
		case '9': strike_key(2, 14); break;
		case '0': strike_key(3, 15); break;

		// Hacks
		case '~': strike_key(5, 15); break;
		case '^': strike_key_code(2, 13); break;

		// Control characters
		case '\n': strike_key(7, 17); break;
		//case '\b': strike_key(3, 17); break; // backspace with correction fluid
		case '\b': strike_key(2, 16); break; // regular backspace

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