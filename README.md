# Dowód Rejestracyjny Pojazdu - decompression

[![Build Status](https://secure.travis-ci.org/dex4er/drpdecompress.svg)](http://travis-ci.org/dex4er/drpdecompress)

This is command line utility to decompress data for Dowód Rejestracyjny Pojazdu
(vehicle registration certificate in Poland).

See: <https://pl.wikipedia.org/wiki/Dow%C3%B3d_rejestracyjny_pojazdu>

## Usage

```sh
drpdecompress < input.txt > output.txt
```

Decode data from Dowód Rejestracyjny Pojazdów document with Aztec 2D scanner to get Base64 encoded text string.

Example image:

<https://www.pwpw.pl/binaries/content/gallery/pwpwcms_pl/Dla_mediow/zdjecia_do_artykulow/2016/03/dsc_1548.jpg>

Then from command line:

```sh
cat input.txt | base64 --decode | drpdecompress | iconv -f UCS-2LE -t UTF-8//TRANSLIT > output.txt
```

Output is a text file with fields separated with pipe (`|`) character.

## Compilation

This utility requires [UCL 1.03 library](http://www.oberhumer.com/opensource/ucl/)

### Debian / Ubuntu

```sh
sudo apt install build-essential
sudo apt install libucl-dev
make
make install
```

### MacOSX

```sh
brew install ucl
make
make install
```

## Technical details

The registry document is a text file encoded as UCS-2LE (2-bytes Windows Unicode format), compressed with NRV2E algorithm and encoded with Base64.

## License

Copyright (c) 2018 Piotr Roszatycki <piotr.roszatycki@gmail.com>

[GPL-3.0](https://opensource.org/licenses/GPL-3.0)
