/*
    drpdecompress -- Dowod Rejestracyjny Pojazdu - decompression

    Copyright (c) 2018 Piotr Roszatycki <piotr.roszatycki@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ucl/ucl.h>

#define MAX_BUFFER 10240
#define SKIP_BYTES 4

int main (int argc, char *argv[])  {
    unsigned char *input, *output;
    FILE *fin, *fout;
    ucl_uint sizein, sizeout;
    int status;

    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s [input [output]]\n", argv[0]);
            exit(0);
        }
        if (!(fin = fopen(argv[1], "rb"))) {
            fprintf(stderr, "Cannot open input file\n");
            exit(1);
        }
    } else {
        fin = stdin;
    }

    if (argc > 2) {
        if (!(fout = fopen(argv[2], "wb"))) {
            fprintf(stderr, "Cannot open output file\n");
            exit(1);
        }
    } else {
        fout = stdout;
    }

    if (!(input = calloc(MAX_BUFFER, 1))) {
        fprintf(stderr, "Cannot allocate memory for input\n");
        exit(1);
    }

    if (!(output = calloc(MAX_BUFFER, 1))) {
        fprintf(stderr, "Cannot allocate memory for output\n");
        exit(1);
    }

    if (!(sizein = fread(input, 1, MAX_BUFFER-1, fin))) {
        fprintf(stderr, "Cannot read from input\n");
        exit(1);
    }
    if (sizein < SKIP_BYTES) {
        fprintf(stderr, "Input is not valid\n");
        exit(1);
    }
    fclose(fin);

    if ((status = ucl_nrv2e_decompress_8(input + SKIP_BYTES, sizein - SKIP_BYTES, output, &sizeout, NULL)) != 0) {
        fprintf(stderr, "Cannot decompress; status=%d\n", status);
    }

    if (!(fwrite(output, 1, sizeout, fout))) {
        fprintf(stderr, "Cannot write to output\n");
        exit(1);
    }
    fclose(fout);

    free(input);
    free(output);

    return 0;
}
