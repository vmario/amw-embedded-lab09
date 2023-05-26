#include "ledDisplay.hpp"

#include <avr/io.h>

#define LED_DISPLAY_SEGMENT_PORT PORTA ///< Rejestr PORT segmentów wyświetlacza.
#define LED_DISPLAY_SEGMENT_DDR DDRA ///< Rejestr DDR segmentów wyświetlacza.
#define LED_DISPLAY_SEGMENT_MASK 0xff ///< Maska pinów obsługujących segmenty wyświetlacza.
#define LED_DISPLAY_DIGIT_PORT PORTB ///< Rejestr PORT cyfr wyświetlacza.
#define LED_DISPLAY_DIGIT_DDR DDRB ///< Rejestr DDR cyfr wyświetlacza.
#define LED_DISPLAY_DIGIT_MASK 0x0f ///< Maska pinów obsługujących cyfry wyświetlacza.

LedDisplayBuffer displayBuffer{{0, 0, 0, 0}};
LedDisplay display;

/**
 * Wzorce cyfr na wyświetlaczu siedmiosegmentowym.
 */
const uint8_t DIGITS[] = {
	0b11000000, // '0'
};

void LedDisplay::init() const
{
	LED_DISPLAY_SEGMENT_DDR |= LED_DISPLAY_SEGMENT_MASK;
	LED_DISPLAY_DIGIT_DDR |= LED_DISPLAY_DIGIT_MASK;
	LED_DISPLAY_DIGIT_PORT |= LED_DISPLAY_DIGIT_MASK;
}

void LedDisplay::refresh()
{
	LED_DISPLAY_DIGIT_PORT = (~(1 << 3)) & (LED_DISPLAY_DIGIT_PORT | LED_DISPLAY_DIGIT_MASK);
	LED_DISPLAY_SEGMENT_PORT = DIGITS[0];
}
