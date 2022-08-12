#include <Arduino.h>

#define SEND_PIN_OFFSET 2
#define RETURN_PIN_OFFSET 10

uint8_t keystate[8][8];


void setup()
{
	Serial.begin(300);
	for (uint8_t i = 0; i < 8; i++)
	{
		pinMode(SEND_PIN_OFFSET + i, INPUT);
	}

	for (uint8_t i = 0; i < 8; i++)
	{
		pinMode(RETURN_PIN_OFFSET + i, INPUT_PULLUP);
	}
}

bool lshift = false;
bool rshift = false;
bool code = false;

inline void send_key(unsigned char c)
{
	Serial.write(c);
}

void key_event(uint8_t sendpin, uint8_t returnpin, uint8_t event)
{
	// Corrections for Pinout:
	sendpin = sendpin;
	returnpin = 7 - returnpin;

	// Key Up
	if (event == 0)
	{
		if (sendpin == 7 && returnpin == 0) lshift = false;
		if (sendpin == 5 && returnpin == 6) rshift = false;
		if (sendpin == 7 && returnpin == 2)	code = false;
	}

	// Key Down
	if (event == 1)
	{
		if (sendpin == 7 && returnpin == 0) lshift = true;
		if (sendpin == 5 && returnpin == 6) rshift = true;
		if (sendpin == 7 && returnpin == 2)	code = true;

		if (code)
		{
			if (sendpin == 0 && returnpin == 5) send_key('\\');
			if (sendpin == 2 && returnpin == 6) send_key('~');

			if (sendpin == 6 && returnpin == 5) send_key('>');
			if (sendpin == 7 && returnpin == 5) send_key('<');
			if (sendpin == 6 && returnpin == 6) { send_key(0xC2); send_key(0xB5); } // µ
			if (sendpin == 3 && returnpin == 4) send_key('|');

			if (sendpin == 5 && returnpin == 5) send_key('#');
			if (sendpin == 4 && returnpin == 5) send_key('\'');
			if (sendpin == 2 && returnpin == 5) { send_key(0xC2); send_key(0xB2); } // ²
			if (sendpin == 3 && returnpin == 5) { send_key(0xC2); send_key(0xB3); } // ³

			if (sendpin == 0 && returnpin == 3) send_key('{');
			if (sendpin == 1 && returnpin == 4) send_key('[');
			if (sendpin == 0 && returnpin == 4) send_key(']');
			if (sendpin == 1 && returnpin == 5) send_key('}');
		}
		else
		{
			if (lshift || rshift)
			{
				if (sendpin == 5 && returnpin == 0) send_key('A');
				if (sendpin == 6 && returnpin == 3) send_key('B');
				if (sendpin == 6 && returnpin == 2) send_key('C');
				if (sendpin == 4 && returnpin == 1) send_key('D');
				if (sendpin == 3 && returnpin == 1) send_key('E');
				if (sendpin == 5 && returnpin == 2) send_key('F');
				if (sendpin == 4 && returnpin == 2) send_key('G');
				if (sendpin == 5 && returnpin == 3) send_key('H');
				if (sendpin == 2 && returnpin == 4) send_key('I');
				if (sendpin == 4 && returnpin == 3) send_key('J');
				if (sendpin == 5 && returnpin == 4) send_key('K');
				if (sendpin == 4 && returnpin == 4) send_key('L');
				if (sendpin == 6 && returnpin == 4) send_key('M');
				if (sendpin == 7 && returnpin == 4) send_key('N');
				if (sendpin == 3 && returnpin == 4) send_key('O');
				if (sendpin == 2 && returnpin == 5) send_key('P');
				if (sendpin == 3 && returnpin == 0) send_key('Q');
				if (sendpin == 2 && returnpin == 2) send_key('R');
				if (sendpin == 5 && returnpin == 1) send_key('S');
				if (sendpin == 3 && returnpin == 2) send_key('T');
				if (sendpin == 3 && returnpin == 3) send_key('U');
				if (sendpin == 7 && returnpin == 3) send_key('V');
				if (sendpin == 2 && returnpin == 1) send_key('W');
				if (sendpin == 6 && returnpin == 1) send_key('X');
				if (sendpin == 6 && returnpin == 0) send_key('Y');
				if (sendpin == 2 && returnpin == 3) send_key('Z');

				if (sendpin == 0 && returnpin == 0) send_key('!');
				if (sendpin == 1 && returnpin == 1) send_key('"');
				if (sendpin == 0 && returnpin == 1) { send_key(0xC2); send_key(0xA7); } // §
				if (sendpin == 1 && returnpin == 2) send_key('$');
				if (sendpin == 0 && returnpin == 2) send_key('%');
				if (sendpin == 1 && returnpin == 3) send_key('&');
				if (sendpin == 0 && returnpin == 3) send_key('/');
				if (sendpin == 1 && returnpin == 4) send_key('(');
				if (sendpin == 0 && returnpin == 4) send_key(')');
				if (sendpin == 1 && returnpin == 5) send_key('=');
				if (sendpin == 0 && returnpin == 5) send_key('?');

				if (sendpin == 2 && returnpin == 6) send_key('*');
				if (sendpin == 1 && returnpin == 6) send_key('`');
				if (sendpin == 6 && returnpin == 5) send_key(':');
				if (sendpin == 7 && returnpin == 5) send_key(';');
				if (sendpin == 6 && returnpin == 6) send_key('_');

				if (sendpin == 5 && returnpin == 5) { send_key(0xC3); send_key(0x96); } // ö
				if (sendpin == 4 && returnpin == 5) { send_key(0xC3); send_key(0x84); } // ä
				if (sendpin == 3 && returnpin == 5) { send_key(0xC3); send_key(0x9C); } // ü
			}
			
			if (!(lshift || rshift))
			{
				if (sendpin == 5 && returnpin == 0) send_key('a');
				if (sendpin == 6 && returnpin == 3) send_key('b');
				if (sendpin == 6 && returnpin == 2) send_key('c');
				if (sendpin == 4 && returnpin == 1) send_key('d');
				if (sendpin == 3 && returnpin == 1) send_key('e');
				if (sendpin == 5 && returnpin == 2) send_key('f');
				if (sendpin == 4 && returnpin == 2) send_key('g');
				if (sendpin == 5 && returnpin == 3) send_key('h');
				if (sendpin == 2 && returnpin == 4) send_key('i');
				if (sendpin == 4 && returnpin == 3) send_key('j');
				if (sendpin == 5 && returnpin == 4) send_key('k');
				if (sendpin == 4 && returnpin == 4) send_key('l');
				if (sendpin == 6 && returnpin == 4) send_key('m');
				if (sendpin == 7 && returnpin == 4) send_key('n');
				if (sendpin == 3 && returnpin == 4) send_key('o');
				if (sendpin == 2 && returnpin == 5) send_key('p');
				if (sendpin == 3 && returnpin == 0) send_key('q');
				if (sendpin == 2 && returnpin == 2) send_key('r');
				if (sendpin == 5 && returnpin == 1) send_key('s');
				if (sendpin == 3 && returnpin == 2) send_key('t');
				if (sendpin == 3 && returnpin == 3) send_key('u');
				if (sendpin == 7 && returnpin == 3) send_key('v');
				if (sendpin == 2 && returnpin == 1) send_key('w');
				if (sendpin == 6 && returnpin == 1) send_key('x');
				if (sendpin == 6 && returnpin == 0) send_key('y');
				if (sendpin == 2 && returnpin == 3) send_key('z');

				if (sendpin == 0 && returnpin == 0) send_key('1');
				if (sendpin == 1 && returnpin == 1) send_key('2');
				if (sendpin == 0 && returnpin == 1) send_key('3');
				if (sendpin == 1 && returnpin == 2) send_key('4');
				if (sendpin == 0 && returnpin == 2) send_key('5');
				if (sendpin == 1 && returnpin == 3) send_key('6');
				if (sendpin == 0 && returnpin == 3) send_key('7');
				if (sendpin == 1 && returnpin == 4) send_key('8');
				if (sendpin == 0 && returnpin == 4) send_key('9');
				if (sendpin == 1 && returnpin == 5) send_key('0');

				if (sendpin == 0 && returnpin == 5) { send_key(0xC3); send_key(0x9F); } // ß
				if (sendpin == 1 && returnpin == 6) { send_key(0xC2); send_key(0xB4); } // ´

				if (sendpin == 2 && returnpin == 6) send_key('+');
				if (sendpin == 6 && returnpin == 5) send_key('.');
				if (sendpin == 7 && returnpin == 5) send_key(',');
				if (sendpin == 6 && returnpin == 6) send_key('-');

				if (sendpin == 5 && returnpin == 5) { send_key(0xC3); send_key(0xB6); } // ö
				if (sendpin == 4 && returnpin == 5) { send_key(0xC3); send_key(0xA4); } // ä
				if (sendpin == 3 && returnpin == 5) { send_key(0xC3); send_key(0xBC); } // ü
			}
		}

		if (sendpin == 5 && returnpin == 7) {
			send_key('\r');
			//send_key('\n');
		}
		if (sendpin == 1 && returnpin == 7) send_key('\b');
		if (sendpin == 7 && returnpin == 6) send_key(' ');
		if (sendpin == 2 && returnpin == 0) send_key('\t');

	}
}

void scan_matrix()
{
	for (uint8_t sendpin = 0; sendpin < 8; sendpin++)
	{
		pinMode(SEND_PIN_OFFSET + sendpin, OUTPUT);
		digitalWrite(SEND_PIN_OFFSET + sendpin, LOW);
		for (uint8_t returnpin = 0; returnpin < 8; returnpin++)
		{
			bool new_keystate = !digitalRead(RETURN_PIN_OFFSET + returnpin);

			if (keystate[sendpin][returnpin] != new_keystate)
			{
				keystate[sendpin][returnpin] = new_keystate;
				key_event(sendpin, returnpin, new_keystate);
			}
			
		}

		pinMode(SEND_PIN_OFFSET + sendpin, INPUT);
	}
}

void loop()
{
	scan_matrix();
	delay(10);
}
