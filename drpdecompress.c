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

#include <ucl/ucl.h>

#define MAX_BUFFER 10240
#define SKIP_BYTES 4

int main () {
    unsigned char input[MAX_BUFFER], output[MAX_BUFFER];

    ucl_uint sizein, sizeout;

    if (!(sizein = fread(input, 1, sizeof input, stdin))) {
        fprintf(stderr, "Cannot read from input\n");
        exit(1);
    }
    if (sizein < SKIP_BYTES) {
        fprintf(stderr, "Input is not valid\n");
        exit(1);
    }

    ucl_nrv2e_decompress_8(input + SKIP_BYTES, sizein - SKIP_BYTES, output, &sizeout, NULL);

    if (!(fwrite(output, 1, sizeout, stdout))) {
        fprintf(stderr, "Cannot write to output\n");
        exit(1);
    }

    return 0;
}
