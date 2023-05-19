#include "encoder.hpp"
#include "encoderDebouncer.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define ENCODER_PIN PIND ///< Rejestr wejściowy impulsatora.
#define ENCODER_PORT PORTD ///< Rejestr wyjściowy impulsatora.
#define ENCODER_PIN_B PD1 ///< Pin B impulsatora.
#define ENCODER_PIN_SW PD4 ///< Pin przycisku impulsatora.

Encoder encoder;

/**
 * Obsługa przerwania INT0.
 */
ISR(INT0_vect)
{
	if (bit_is_set(ENCODER_PIN, ENCODER_PIN_B)) {
		encoder.onClockwise();
	} else {
		encoder.onCounterClockwise();
	}
#if 1
	EncoderDebouncer{}.debounce();
#endif
}

void Encoder::init() const
{
	ENCODER_PORT |= _BV(ENCODER_PIN_SW);
	EICRA |= _BV(ISC01);
	EIMSK |= _BV(INT0);
}

void Encoder::onClockwise()
{
	pulses++;
}

void Encoder::onCounterClockwise()
{
	pulses--;
}

int8_t Encoder::pop()
{
	int8_t value;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		value = pulses;
		pulses = 0;
	}

	return value;
}

bool Encoder::isSwitchPressed() const
{
	return bit_is_clear(ENCODER_PIN, ENCODER_PIN_SW);
}