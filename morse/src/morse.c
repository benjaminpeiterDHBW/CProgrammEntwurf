/**
 * @file morse.c
 * @brief Lookup-Funktionen für Morsecode.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "morse_table.h"
#include "morse.h"

void print_help(void)
{
    printf("Verwendung: morse [OPTION]... [DATEI]...\n");
    printf("  -h, --help               zeigt diesen Hilfetext\n");
    printf("  -e, --encode             Text in Morsecode umwandeln\n");
    printf("  -d, --decode             Morsecode in Text umwandeln\n");
    printf("  -o, --out=DATEI          Ausgabe in Datei umleiten\n");
    printf("      --programmer-info    zeigt Infos zum Entwickler\n");
    printf("      --slash-wordspacer   trennt Wörter mit SP / SP\n");
}

void print_programmer_info(void)
{
    printf("{\n");
    printf("  \"firstname\": \"Benjamin\",\n");
    printf("  \"surname\": \"Peiter\",\n");
    printf("  \"branch_of_study\": \"Informatik Künstliche Intelligenz\",\n");
    printf("  \"contact\": \"peiter.benjami-it24@it.dhbw-ravensburg.de\"\n");
    printf("}\n");
}

/**
 * @brief Wandelt ein ASCII-Zeichen in Morsecode um.
 *
 * Wandelt Buchstaben unabhängig von Groß-/Kleinschreibung um.
 *
 * @param input  Eingabezeichen (char)
 * @return       Zeiger auf statischen Morse-String oder NULL.
 */
const char *lookup_morse(char input)
{
    input = toupper((unsigned char)input);
    for (int i = 0; morse_table[i].morse != NULL; ++i)
    {
        if (morse_table[i].symbol == input)
        {
            return morse_table[i].morse;
        }
    }
    return NULL;
}

/**
 * @brief Wandelt eine Morse-Sequenz zurück in ein Zeichen.
 *
 * Vergleicht bitweise Strings; unbekannte Sequenzen ergeben '*'.
 *
 * @param morse_input  String mit '.' und '-'
 * @return             Entsprechendes Klartext-Zeichen oder '*'.
 */
char lookup_char(const char *morse_input)
{
    for (int i = 0; morse_table[i].morse != NULL; ++i)
    {
        if (strcmp(morse_table[i].morse, morse_input) == 0)
        {
            return morse_table[i].symbol;
        }
    }
    return '*';
}