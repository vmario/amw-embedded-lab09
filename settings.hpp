#pragma once

/**
 * Nastawy termostatu.
 */
struct Settings {
	float target; ///< Temperatura docelowa.
	float hysteresis; ///< Histereza.
};