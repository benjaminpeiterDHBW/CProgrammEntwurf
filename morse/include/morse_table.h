/**
 * @file morse_table.h
 * @brief Definition der Datenstruktur für Morsecode-Zuordnung.
 */
#ifndef MORSE_TABLE_H
#define MORSE_TABLE_H

/**
 * @brief Eintrag für Klartext zu Morse und umgekehrt.
 */
typedef struct
{
    char symbol;       ///< Klartextzeichen
    const char *morse; ///< Morsecode als C-String
} MorseEntry;

/**
 * @brief Statische Tabelle aller unterstützten Zeichen und ihrer Morse-Entsprechung.
 * Eintrag mit symbol '\0' markiert das Ende der Liste.
 */
extern const MorseEntry morse_table[];

#endif // MORSE_TABLE_H