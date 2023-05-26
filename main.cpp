#include "ledDisplay.hpp"
#include "keypad.hpp"
#include "timer.hpp"

#include <stdlib.h>

/**
 * Funkcja główna.
 */
int main()
{
	const SystemTick tick;

	display.init();
	keypad.init();
	tick.init();

	while (true) {
	}

	return EXIT_SUCCESS;
}