/**
 * @file encode.c
 * @brief Implementierung der Encodierfunktion für Morsecode.
 */

#include <stdio.h>
#include <ctype.h>
#include "morse.h"
#include "morse_table.h"

/**
 * @brief Encodiert Text in Morsecode, Buchstaben durch SP getrennt, Wörter durch 3×SP oder '/'.
 */
void encode_text(FILE *in, FILE *out, int slash_wordspacer)
{
    int c;
    int prev_space = 0;

    while ((c = fgetc(in)) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
        {
            if (!prev_space)
            {
                if (slash_wordspacer)
                    fprintf(out, " / ");
                else
                    fprintf(out, "   ");
                prev_space = 1;
            }
            continue;
        }
        prev_space = 0;
        const char *m = lookup_morse((char)c);
        if (m)
            fprintf(out, "%s ", m);
        else
            fprintf(out, "* ");
    }
}
