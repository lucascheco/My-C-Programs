//Author: Lucas Pacheco.
//Description: A test exercise from "The Audio Programming Book", chapter 1, covert all programs developed so far to use argc and argv.
//Date: 17/05/2020.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    double semitone_ratio;
    double c0;        /* for frequency of MIDI Note 0 */
    double c5;        /* for frequency of Middle C */
    double frequency; /* . . . which we want to find, */
    int midinote;     /* . . . given this note. */
    double fracmidi;
    double dif;

    if (argc != 3)
    {
        printf("Exercises141: finds the nearest MIDI note to a frequency.\n" /*,argv[0]*/);
        printf("usage: Exercises frequency rootA\n" /* ,argv[0]*/);
        printf(" range: 20.000 <= frequency <= 20000.000 \n");
        return 1;
    }

    double rootA = atoi(argv[2]);

    /* calculate required numbers */
    semitone_ratio = pow(2, 1 / 12.0); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(semitone_ratio, 3);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    //ANSWER (a): User types a frequency
    printf("Frequency: ");
    scanf("%lf", &frequency);
    /* find nearest MIDI note to a given frequency in Hz */ /* uses the log rule: log_a(N) = log_b(N) / log_b(a) to find the log of a value to base 'semitone_ratio'. */
    fracmidi = log(frequency / c0) / log(semitone_ratio);
    printf("FRACMIDI: %lf\n", fracmidi);

    /* round fracmidi to the nearest whole number */
    midinote = (int)(fracmidi + 0.5);
    printf("MIDINOTE: %d\n", midinote);

    /* Extract decimals */
    dif = fracmidi - (double)midinote;
    printf("Difference: %f\n", dif);

    /* Percentage */
    dif *= 100;

    // (b) round function of math.h to round a number.
    printf("The nearest MIDI note to frequency %.1f is %d with pitch bend of %.1f%%\n", frequency, midinote, round(dif));

    return 0;
}

/*
    OUTPUT SAMPLE:
        FRACMIDI: 68.601998
        MIDINOTE: 69
        Difference: -0.398002
        The nearest MIDI note to frequency 430.0 is 69 with pitch bend of -39.8%

*/