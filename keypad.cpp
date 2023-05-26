#include "keypad.hpp"

#include <avr/io.h>

#define KEYPAD_PORT PORTB ///< Rejestr PORT klawiatury.
#define KEYPAD_PIN PINB ///< Rejestr PIN klawiatury.
#define KEYPAD_START_BIT PB4 ///< Pin klawisza "Start".
#define KEYPAD_RESET_BIT PB5 ///< Pin klawisza "Reset".

Keypad keypad;

void Keypad::init() const
{
	KEYPAD_PORT |= _BV(KEYPAD_START_BIT) | _BV(KEYPAD_RESET_BIT);
}

KEY Keypad::key() const
{
	if (bit_is_clear(KEYPAD_PIN, KEYPAD_START_BIT)) {
		return KEY_START;
	} else if (bit_is_clear(KEYPAD_PIN, KEYPAD_RESET_BIT)) {
		return KEY_RESET;
	} else {
		return KEY_NONE;
	}
}