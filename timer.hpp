#pragma once

/**
 * Zegar systemowy.
 * 
 * Generuje taktowanie 1Hz.
 */
struct SystemTick {
	/**
	 * Inicjalizuje Timer/Counter0 w trybie podstawowym i włącza przerwanie.
	 */
	void init() const;

	/**
	 * Sprawdza, czy została ustawiona flaga ticku systemowego.
	 * 
	 * Jeżeli flaga została ustawiona, jest czyszczona.
	 */
	bool pop() const;
};
