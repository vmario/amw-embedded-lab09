#include "timer.hpp"

#include "ledDisplay.hpp"
#include "keypad.hpp"

#include <avr/interrupt.h>

/**
 * Konfiguracja Timer/Counter0 w trybie Clear Timer on Compare Match.
 */
static constexpr uint8_t TIMER0_CTC = _BV(WGM01);

/**
 * Taktowanie Timer/Counter0 zegarem podzielonym przez 1024.
 */
static constexpr uint8_t TIMER0_PRESCALER_1024 = _BV(CS02) | _BV(CS00);

/**
 * Rejestr komparatora Timer/Counter0 dający tick 31,25Hz.
 */
static constexpr uint8_t TIMER0_OCR_TICK = 250;

/**
 * Obsługa przerwania TIMER0_COMPA.
 */
ISR(TIMER0_COMPA_vect)
{
	display.refresh();
}

void SystemTick::init() const
{
	TCCR0A = TIMER0_CTC;
	TCCR0B = TIMER0_PRESCALER_1024;
	OCR0A = TIMER0_OCR_TICK;
	TIMSK0 = _BV(OCIE0A);
	sei();
}
