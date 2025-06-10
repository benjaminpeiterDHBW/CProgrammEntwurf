/**
 * @file decode.c
 * @brief Implementierung der Decodierfunktion für Morsecode.
 */

#include <stdio.h>
#include <string.h>
#include "morse.h"
#include "morse_table.h"

/**
 * @brief Decodiert Morsecode zu Klartext. Unbekannte Sequenzen bleiben '*'.
 */
void decode_text(FILE *in, FILE *out)
{
    int c;
    char buf[10];
    int bi = 0, space_count = 0;

    while ((c = fgetc(in)) != EOF)
    {
        if (c == '*')
        {
            bi = space_count = 0;
            fputc('*', out);
            continue;
        }
        if (c == ' ')
        {
            space_count++;
            if (bi > 0)
            {
                buf[bi] = '\0';
                fputc(lookup_char(buf), out);
                bi = 0;
            }
            continue;
        }
        if (space_count >= 3)
        {
            fputc(' ', out);
        }
        space_count = 0;
        if (c == '.' || c == '-')
        {
            if (bi < (int)sizeof(buf) - 1)
                buf[bi++] = (char)c;
        }
    }
    if (bi > 0)
    {
        buf[bi] = '\0';
        fputc(lookup_char(buf), out);
    }
}
