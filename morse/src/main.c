/**
 * @file main.c
 * @brief Hauptprogramm für das Morse-Tool mit Kommandozeilenoptionen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include "morse.h"

/*----------------------------------------------------------
 * Globale Flags, die in process_stream() und main() genutzt werden
 *----------------------------------------------------------*/
static int encode_flag = 0;
static int decode_flag = 0;
static int slash_flag = 0;

/**
 * @brief Intern: entscheidet, ob encode_text oder decode_text aufgerufen wird.
 *
 * @param in   Eingabestrom (stdin oder Datei)
 * @param out  Ausgabestrom (stdout oder Datei)
 */
static void process_stream(FILE *in, FILE *out)
{
    if (decode_flag)
        decode_text(in, out);
    else
        encode_text(in, out, slash_flag);
}

/**
 * @brief Hauptprogramm und Kommandozeilen-Interface für das Morse-Tool.
 *
 * Parst Optionen (`--encode`, `--decode`, `--out` usw.),
 * wählt Encode- oder Decode-Modus und steuert Ein- und Ausgabe.
 *
 * @param argc  Anzahl der Kommandozeilenargumente
 * @param argv  Array der Kommandozeilenargumente (Strings)
 * @return      0 bei Erfolg, ungleich 0 bei Fehler
 */
int main(int argc, char *argv[])
{
    int opt;
    char *output_file = NULL;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"encode", no_argument, 0, 'e'},
        {"decode", no_argument, 0, 'd'},
        {"out", required_argument, 0, 'o'},
        {"programmer-info", no_argument, 0, 1000},
        {"slash-wordspacer", no_argument, 0, 1001},
        {0, 0, 0, 0}};

    /* Optionen einlesen */
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
            slash_flag = 1;
            break;
        default:
            fprintf(stderr, "Unbekannte Option. Nutze --help\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Validierung */
    if (encode_flag && decode_flag)
    {
        fprintf(stderr, "Fehler: --encode und --decode dürfen nicht gleichzeitig gesetzt sein.\n");
        exit(EXIT_FAILURE);
    }
    if (slash_flag && !encode_flag)
    {
        fprintf(stderr, "Fehler: --slash-wordspacer nur mit --encode erlaubt.\n");
        exit(EXIT_FAILURE);
    }

    /* Ausgabe-Stream vorbereiten */
    FILE *out = stdout;
    if (output_file)
    {
        out = fopen(output_file, "w");
        if (!out)
        {
            perror("Fehler beim Öffnen der Ausgabedatei");
            exit(EXIT_FAILURE);
        }
    }

    /* Eingabe-Fallunterscheidung: keine Dateien vs. Dateien vs. Pipe */
    if (optind >= argc)
    {
        if (isatty(STDIN_FILENO))
        {
            print_help();
            if (out != stdout)
                fclose(out);
            exit(EXIT_SUCCESS);
        }
        process_stream(stdin, out);
    }
    else
    {
        int file_count = argc - optind;
        if (output_file && file_count != 1)
        {
            fprintf(stderr, "Fehler: -o nur mit exakt einer Eingabedatei erlaubt.\n");
            if (out != stdout)
                fclose(out);
            exit(EXIT_FAILURE);
        }
        for (int i = optind; i < argc; ++i)
        {
            FILE *in = fopen(argv[i], "r");
            if (!in)
            {
                perror("Fehler beim Öffnen der Eingabedatei");
                if (out != stdout)
                    fclose(out);
                exit(EXIT_FAILURE);
            }
            process_stream(in, out);
            fclose(in);
        }
    }

    /* Abschluss: Streams schließen und Zeilenumbruch */
    if (out != stdout)
        fclose(out);
    fputc('\n', stdout);

    return 0;
}
