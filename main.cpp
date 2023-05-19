/**
 * @file
 * @author Mariusz Chilmon <mariusz.chilmon@ctm.gdynia.pl>
 * @date 2023
 * 
 * Pętla główna.
 */

#include "lcd.hpp"
#include "encoder.hpp"
#include "timer.hpp"
#include "thermometer.hpp"
#include "thermostat.hpp"
#include "menu.hpp"
#include "settings.hpp"

#include <avr/interrupt.h>

#include <stdlib.h>
#include <stdio.h>

/**
 * Obsługa wyświetlacza, termometru i termostatu obsługiwana cyklicznie
 * w każdym ticku systemowym.
 *
 * @param thermostat Sterownik termostatu.
 * @param menu Menu na wyświetlaczu.
 */
void onSystemTick(Thermostat& thermostat, Menu& menu)
{
	static bool lastSwitch = false;

	if (lastSwitch != encoder.isSwitchPressed()) {
		lastSwitch = encoder.isSwitchPressed();
		if (lastSwitch) {
			menu.onEncoderPress();
		}
	}
	menu.onEncoderPulse(encoder.pop());
	menu.refresh();
	thermostat.onTemperature(Thermometer{}.temperature());
}

/**
 * Funkcja główna.
 */
int main()
{
	const SystemTick tick;
	const Lcd lcd;
	Settings settings = { 20, 0 };
	Thermostat thermostat{settings};
	Menu menu{lcd, thermostat, settings};

	lcd.init();
	encoder.init();
	tick.init();
	menu.init();
	sei();

	while (true) {
		if (tick.pop()) {
			onSystemTick(thermostat, menu);
		}
	}

	return EXIT_SUCCESS;
}