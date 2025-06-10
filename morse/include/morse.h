/**
 *
 * @file morse.h
 * @brief Header für das Morse_Code_Projekt.
 *
 * Enthält Funktionsprototypen für Hilfe, Metadaten, Encoding und Decoding.
 */
#ifndef MORSE_H
#define MORSE_H

#include <stdio.h> ///< für FILE*

/**
 * @brief Gibt einen Hilfetext mit allen Kommandozeilenoptionen aus.
 */
void print_help(void);

/**
 * @brief Gibt Programmiererinformationen im JSON-Format aus.
 *
 * Ausgabe enthält Vorname, Nachname, Studiengang und Kontakt.
 */
void print_programmer_info(void);

/**
 * @brief Sucht den Morsecode zu einem Klartext-Zeichen.
 *
 * @param input  ASCII-Zeichen (Buchstabe, Zahl, Satzzeichen)
 * @return       Zeiger auf das statische Morse-String oder NULL, wenn unbekannt.
 */
const char *lookup_morse(char input);

/**
 * @brief Sucht das Klartext-Zeichen zu einer Morse-Sequenz.
 *
 * @param morse_input  String mit Punkten und Strichen
 * @return             Großbuchstabe, Zahl oder Symbol, '*' bei unbekannter Sequenz.
 */
char lookup_char(const char *morse_input);

/**
 * @brief Encodiert Text aus einem Eingabestrom in Morsecode.
 *
 * Liest Zeichen, übersetzt sie in Morse und trennt Buchstaben mit einem Space.
 * Wörter werden durch drei Spaces oder durch " SP / SP" getrennt.
 *
 * @param in               Eingabestrom (stdin oder geöffnete Datei)
 * @param out              Ausgabestrom (stdout oder geöffnete Datei)
 * @param slash_wordspacer Wenn != 0: trenne Wörter mit " / ".
 */
void encode_text(FILE *in, FILE *out, int slash_wordspacer);

/**
 * @brief Decodiert Morsecode aus einem Eingabestrom in Klartext.
 *
 * Liest Punkte, Striche und Spaces, wandelt Sequenzen in Zeichen um und
 * gibt Großbuchstaben und Worttrennungen aus.
 *
 * @param in   Eingabestrom mit ".", "-" und Spaces als Trenner
 * @param out  Ausgabestrom für resultierenden Text
 */
void decode_text(FILE *in, FILE *out);

#endif // MORSE_H