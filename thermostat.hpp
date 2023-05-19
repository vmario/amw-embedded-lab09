#pragma once

#include "settings.hpp"

/**
 * Sterownik termostatu.
 */
struct Thermostat {
	/**
	 * Konstruktor.
	 */
	Thermostat(const Settings& settings);

	/**
	 * Zdarzenie odczytu temperatury.
	 * 
	 * W reakcji na zmianę tempeatury grzałka jest włączana lub wyłączana.
	 */
	void onTemperature(double currentTemperature) const;

private:
	const Settings& settings; ///< Nastawy.
};