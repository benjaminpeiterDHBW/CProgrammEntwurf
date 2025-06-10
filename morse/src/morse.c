#include <stdio.h>
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
    printf("  \"firstname\": \"Benni\",\n");
    printf("  \"surname\": \"[DEIN NACHNAME]\",\n");
    printf("  \"branch_of_study\": \"[DEIN STUDIENGANG]\",\n");
    printf("  \"contact\": \"[DEINE EMAIL]\"\n");
    printf("}\n");
}
