#include "thermostat.hpp"

#include <avr/io.h>

#define THERMOSTAT_HEATER_DDR DDRD ///< Rejestr kierunku elementu sterującego.
#define THERMOSTAT_HEATER_PORT PORTD ///< Rejestr wyjściowy elementu sterującego.
#define THERMOSTAT_HEATER_LED PD3 ///< Pin elementu sterującego.

Thermostat::Thermostat(const Settings& settings):
	settings{settings}
{
	THERMOSTAT_HEATER_DDR |= _BV(THERMOSTAT_HEATER_LED);
}

void Thermostat::onTemperature(double currentTemperature) const
{
	if (settings.target > currentTemperature) {
		THERMOSTAT_HEATER_PORT &= ~_BV(THERMOSTAT_HEATER_LED);
	} else {
		THERMOSTAT_HEATER_PORT |= _BV(THERMOSTAT_HEATER_LED);
	}
}