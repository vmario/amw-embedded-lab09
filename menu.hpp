#pragma once

#include "lcd.hpp"
#include "thermostat.hpp"
#include "settings.hpp"

/**
 * Stan menu.
 */
enum STATE {
	STATE_NORMAL, ///< Wyświetlanie bieżącego stanu.
	STATE_EDIT_TARGET, ///< Edycja temperatury docelowej.
	STATE_END, ///< Znacznik końca enumeratora.
};

/**
 * Pomiar temperatury.
 */
struct Measurement {
	/**
	 * Konstruktor.
	 *
	 * @param label Wyświetlana etykieta.
	 * @param lcd Sterownik wyświetlacza.
	 * @param line Numer linii.
	 * @param column Numer kolumny.
	 */
	Measurement(const char* label, const Lcd& lcd, uint8_t line, uint8_t column):
		label{label}, lcd{lcd}, line{line}, column{column}
	{}

	/**
	 * Wyświetla stałe elementy obiektu.
	 */
	void init() const;

	/**
	 * Odświeża stan ekranu.
	 */
	void refresh(float value) const;
	
private:
	const char* label; ///< Wyświetlana etykieta.
	const Lcd& lcd; ///< Sterownik wyświetlacza.
	const uint8_t line; ///< Numer linii.
	const uint8_t column; ///< Numer kolumny.
};

/**
 * Nastawa, którą można edytować.
 */
struct Parameter {
	/**
	 * Konstruktor.
	 *
	 * @param label Wyświetlana etykieta.
	 * @param lcd Sterownik wyświetlacza.
	 * @param line Numer linii.
	 * @param column Numer kolumny.
	 * @param value Zmienna z wartością nastawy.
	 */
	Parameter(const char* label, const Lcd& lcd, uint8_t line, uint8_t column,
			float& value):
		label{label}, lcd{lcd}, line{line}, column{column}, value{value}
	{}

	/**
	 * Wyświetla stałe elementy obiektu.
	 */
	void init() const;

	/**
	 * Odświeża stan ekranu.
	 */
	void refresh() const;

	/**
	 * Wyświetla znak zachęty.
	 */
	void select() const;

	/**
	 * Chowa znak zachęty.
	 */
	void deselect() const;

private:
	const char* label; ///< Wyświetlana etykieta.
	const Lcd& lcd; ///< Sterownik wyświetlacza.
	const uint8_t line; ///< Numer linii.
	const uint8_t column; ///< Numer kolumny.
	float& value; ///< Zmienna z wartością nastawy.
};

/**
 * Menu na wyświetlaczu.
 */
struct Menu {
	/**
	 * Konstruktor.
	 *
	 * @param lcd Sterownik wyświetlacza.
	 * @param thermostat Termostat.
	 * @param settings Obiekt nastaw.
	 */
	Menu(const Lcd& lcd, const Thermostat& thermostat, Settings& settings):
		lcd{lcd}, thermostat{thermostat}, settings{settings},
		currentTemperature{"Tcurrent", lcd, 0, 0},
		target{"Tt", lcd, 1, 0, settings.target},
		state{}
	{}

	/**
	 * Wyświetla stałe elementy menu.
	 */
	void init() const;

	/**
	 * Odświeża stan ekranu.
	 */
	void refresh() const;

	/**
	 * Obsługuje zdarzenie z pokrętłą impulsatora.
	 *
	 * @param pulses Liczba impulsów zliczonych z impulsatora.
	 */
	void onEncoderPulse(int pulses) const;

	/**
	 * Obsługuje zdarzenie wciśnięcia przycisku impulsatora.
	 */
	void onEncoderPress();

private:
	const Lcd& lcd; ///< Sterownik wyświetlacza.
	const Thermostat& thermostat; ///< Termostat.
	Settings& settings; ///< Obiekt nastaw.
	const Measurement currentTemperature; ///< Bieżąca temperatura na wyświetlaczu.
	const Parameter target; ///< Nastawa temperatury docelowej.
	enum STATE state; ///< Bieżący stan menu.
};