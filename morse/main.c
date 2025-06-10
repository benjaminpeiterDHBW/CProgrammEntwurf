#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "morse.h"

int main(int argc, char *argv[])
{
    int opt;
    int encode_flag = 0, decode_flag = 0;
    char *output_file = NULL;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"encode", no_argument, 0, 'e'},
        {"decode", no_argument, 0, 'd'},
        {"out", required_argument, 0, 'o'},
        {"programmer-info", no_argument, 0, 1000},
        {"slash-wordspacer", no_argument, 0, 1001},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "hedo:", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help();
            exit(EXIT_SUCCESS);
        case 'e':
            encode_flag = 1;
            break;
        case 'd':
            decode_flag = 1;
            break;
        case 'o':
            output_file = optarg;
            break;
        case 1000:
            print_programmer_info();
            exit(EXIT_SUCCESS);
        case 1001:
            // Handhabung später
            break;
        default:
            fprintf(stderr, "Unbekannte Option. Nutze --help\n");
            exit(EXIT_FAILURE);
        }
    }

    if (encode_flag && decode_flag)
    {
        fprintf(stderr, "Fehler: --encode und --decode dürfen nicht gleichzeitig gesetzt sein.\n");
        exit(EXIT_FAILURE);
    }

    // TODO: Verarbeitung basierend auf Modus und Argumenten

    return 0;
}
