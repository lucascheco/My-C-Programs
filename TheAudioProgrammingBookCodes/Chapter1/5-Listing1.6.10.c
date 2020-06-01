//Author: Lucas Pacheco.
//Description: Code  from "The Audio Programming Book", chapter 1, Listing1.6.10 .
//Date: 01/06/2020.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
    usage iscale [-m][-i] N startval [outfile.txt]
    -m : sets format of startval as MIDI note  
    -i : prints the calculated interval as well as the abs freq  
    outfile: optional text filename for output data
*/

int main(int argc, char *argv[])
{
    int notes, i;
    int ismidi = 0;
    int write_interval = 0;
    int err = 0;
    double startval, basefreq, ratio;
    FILE *fp;
    double intervals[25];

    /* check first arg for flag option: argc at least */
    while (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'm')
                ismidi = 1;

            else if (argv[1][1] == 'i')
                write_interval = 1;
            else
            {
                printf("error: unrecognized option %s\n", argv[1]);

                return 1;
            }

            /* step up to next arg */
            argc--;
            argv++;
        }
        else
            break;
    }

    if (argc < 3)
    {
        printf("insufficient arguments\n");
        printf("Usage: itable [-m][-i] N startval [outfile.txt]\n");

        return 1;
    }

    /*
        Now read and check all arguments
        We now expected argv[1] to hold N and argv[2] startval
    */
    notes = atoi(argv[1]);

    if (notes < 1 || notes > 24)
    {
        printf("error: N out of range. Must be between 1 and 24.\n");

        return 1;
    }

    startval = atof(argv[2]);

    if (ismidi)
    {
        if (startval > 127.0)
        {
            printf("error: MIDI startval must be <= 127.\n");

            return 1;
        }

        /* for MIDI, startval = 0 is legal */
        if (startval < 0.0)
        {
            printf("error: MIDI startval must be >= 0.\n");

            return 1;
        }
    }
    else
    /*
        it's freq: must be positive number
        check low limit
    */
    {
        if (startval <= 0.0)
        {
            printf("error: frequency startval must be positive.\n");

            return 1;
        }
    }

    /* check for optional filename */
    fp = NULL;

    if (argc == 4)
    {
        fp = fopen(argv[3], "w");

        if (fp == NULL)
        {
            printf("WARNING: unable to create file %s\n", argv[3]);
            perror("");
        }
    }

    /*
        all params ready - fill array and write to file if created
        find basefreq, if val is MIDI
    */

    if (ismidi)
    {
        double c0, c5;

        /* find base MIDI note */
        ratio = pow(2.0, 1.0 / 12.0);
        c5 = 220.0 * pow(ratio, 3);
        c0 = c5 * pow(0.5, 5);
        basefreq = c0 * pow(ratio, startval);
    }
    else
        basefreq = startval;

    return 0;
}