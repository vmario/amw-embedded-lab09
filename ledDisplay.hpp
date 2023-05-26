#pragma once

#include <stdint.h>

/**
 * Bufor wyświetlacza. Przechowuje cyfry do wyświetlenia.
 */
struct LedDisplayBuffer {
	static const uint8_t SIZE{4}; ///< Rozmiar wyświetlacza.
	uint8_t digits[SIZE]; ///< Cyfry.
};

/**
 * Globalny obiekt bufora wyświetlacza.
 */
extern LedDisplayBuffer displayBuffer;

/**
 * Sterownik wyświetlacza.
 */
struct LedDisplay {
	/**
	 * Inicjalizacja GPIO.
	 */
	void init() const;
	
	/**
	 * Obsługuje multipleksowanie wyświetlacza.
	 */
	void refresh();
};

/**
 * Globalny obiekt sterownika wyświetlacza.
 */
extern LedDisplay display;