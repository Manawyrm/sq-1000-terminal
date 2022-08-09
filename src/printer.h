#pragma once
#include <Arduino.h>

void strike_key(uint8_t scan_pin, uint8_t return_pin, uint8_t modifier_scan, uint8_t modifier_return);
void strike_key(uint8_t scan_pin, uint8_t return_pin);
void strike_key_shift(uint8_t scan_pin, uint8_t return_pin);
void strike_key_code(uint8_t scan_pin, uint8_t return_pin);
void print_char(char c);
