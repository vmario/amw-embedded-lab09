#include "menu.hpp"

#include "thermometer.hpp"

#include <string.h>
#include <stdio.h>

void Measurement::init() const
{
	lcd.goTo(line, column);
	lcd.write(label);
	lcd.write("=");
}

void Measurement::refresh(float value) const
{
	lcd.goTo(line, column + strlen(label) + 1);

	char buffer[17];
	snprintf(buffer, sizeof(buffer), "%5.2f", static_cast<double>(value));
	lcd.write(buffer);
}

void Parameter::init() const
{
	lcd.goTo(line, column);
	lcd.write(label);
	lcd.write(":");

	char buffer[17];
	snprintf(buffer, sizeof(buffer), "%4.1f", static_cast<double>(value));
	lcd.write(buffer);
}

void Parameter::refresh() const
{
	lcd.goTo(line, column + strlen(label) + 1);

	char buffer[17];
	snprintf(buffer, sizeof(buffer), "%4.1f", static_cast<double>(value));
	lcd.write(buffer);
}

void Parameter::select() const
{
	lcd.goTo(line, column + strlen(label));
	lcd.write(">");
}

void Parameter::deselect() const
{
	lcd.goTo(line, column + strlen(label));
	lcd.write(":");
}

void Menu::init() const
{
	currentTemperature.init();
	target.init();
}

void Menu::refresh() const
{
	currentTemperature.refresh(Thermometer{}.temperature());
	target.refresh();
}

void Menu::onEncoderPress()
{
	switch (state) {
	case STATE_NORMAL:
		state = STATE_EDIT_TARGET;
		break;
	case STATE_EDIT_TARGET:
		state = STATE_NORMAL;
		break;
	default:
		break;
	}

	switch (state) {
	case STATE_NORMAL:
		target.deselect();
		break;
	case STATE_EDIT_TARGET:
		target.select();
		break;
	default:
		break;
	}
}

void Menu::onEncoderPulse(int pulses) const
{
	switch (state) {
	case STATE_EDIT_TARGET:
		settings.target += 1.0 * pulses / 10;
		break;
	default:
		break;
	}
}