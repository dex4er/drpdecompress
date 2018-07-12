# Dowód Rejestracyjny Pojazdu - decompression

[![Build Status](https://secure.travis-ci.org/dex4er/drpdecompress.svg)](http://travis-ci.org/dex4er/drpdecompress)

This is command line utility to decompress data for Dowód Rejestracyjny Pojazdu
(vehicle registration certificate in Poland).

See: <https://pl.wikipedia.org/wiki/Dow%C3%B3d_rejestracyjny_pojazdu>

## Usage

```sh
drpdecompress < input.txt > output.txt
```

or

```sh
drpdecompress input.txt output.txt
```

Use Aztec 2D scanner to decode data from Dowód Rejestracyjny Pojazdów document
and save it in a text file.

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

### Windows/ Cygwin

Download Cygwin setup [setup-x86_64.exe](http://www.cygwin.com/setup-x86_64.exe)
and install packages:

* gcc-core
* make
* ucl

Run Cygwin shell and:

```sh
make
make install
```

## Technical details

The registry document is a text file encoded as UCS-2LE (2-bytes Windows Unicode
format), compressed with NRV2E (8-bit variant) algorithm and encoded with
Base64.

## Output format

The list of fields (in Polish language):

| LP | Oznaczenie                 | Przykład                  | Opis
| --:| -------------------------- | ------------------------- | ----
|  0 | nd.                        | XXC1                      | identyfikator formatu
|  1 | SERIA DR                   | AAA0007046                |
|  2 | nd.                        | 1465058                   | kod terytorialny urzędu rejestrującego
|  3 | ORGAN WYDAJĄCY             | PREZYDENT M. ST. WARSZAWY | linia 1
|  4 | ORGAN WYDAJĄCY             | DZIELNICA MOKOTÓW         | linia 2
|  5 | ORGAN WYDAJĄCY             | UL. RAKOWIECKA 25/27      | linia 3
|  6 | ORGAN WYDAJĄCY             | 02-517 WARSZAWA           | linia 4
|  7 | A                          | DMI 1PNK                  | numer rejestracyjny pojazdu
|  8 | D.1                        | TOYOTA                    | marka pojazdu
|  9 | D.2                        | E12J                      | typ pojazdu
| 10 | D.2                        | ZZE120(H)                 | wariant, jeżeli występuje
| 11 | D.2                        |                           | wersja, jeżeli występuje
| 12 | D.3                        | COROLLA                   | model pojazdu
| 13 | E                          | JTDKM28E100089120         | numer identyfikacyjny pojazdu (numer VIN albo numer nadwozia, podwozia lub ramy)
| 14 | I                          | 2013-11-06                | data wydania dowodu rejestracyjnego (YYYY-MM-DD)
| 15 | H                          | ---                       | okres ważności dowodu, jeżeli występuje takie ograniczenie
| 16 | C.1.1                      | KOWALSKI JAN              | pełne nazwisko lub nazwa posiadacza dowodu rejestracyjnego
| 17 | C.1.1                      | JAN                       | imię posiadacza dowodu rejestracyjnego
| 18 | C.1.1                      | KOWALSKI                  | nazwisko posiadacza dowodu rejestracyjnego
| 19 | C.1.1                      |                           | nazwa posiadacza dowodu rejestracyjnego
| 20 | C.1.2                      | 82091711022               | numer PESEL lub REGON dowodu rejestracyjnego
| 21 | C.1.3                      | 02-517                    | kod pocztowy posiadacza dowodu rejestracyjnego
| 22 | C.1.3                      | WARSZAWA                  | miejscowość posiadacza dowodu rejestracyjnego
| 23 | C.1.3                      |                           | gmina posiadacza dowodu rejestracyjnego
| 24 | C.1.3                      | WAŁBRZYSKA                | ulica posiadacza dowodu rejestracyjnego
| 25 | C.1.3                      | 24                        | nr domu posiadacza dowodu rejestracyjnego
| 26 | C.1.3                      | 30                        | nr mieszkania posiadacza dowodu rejestracyjnego
| 27 | C.2.1                      | KOWALSKA MARIA            | pełne nazwisko lub nazwa właściciela pojazdu
| 28 | C.2.1                      | MARIA                     | imię właściciela pojazdu
| 29 | C.2.1                      | KOWALSKA                  | nazwisko właściciela pojazdu
| 30 | C.2.1                      |                           | nazwa właściciela pojazdu
| 31 | C.2.2                      | 88030971022               | numer PESEL lub REGON właściciela pojazdu
| 32 | C.2.3                      | 02-517                    | kod pocztowy właściciela pojazdu
| 33 | C.2.3                      | WARSZAWA                  | miejscowość właściciela pojazdu
| 34 | C.2.3                      |                           | gmina właściciela pojazdu
| 35 | C.2.3                      | WAŁBRZYSKA                | ulica właściciela pojazdu
| 36 | C.2.3                      | 24                        | nr domu właściciela pojazdu
| 37 | C.2.3                      | 30                        | nr mieszkania właściciela pojazdu
| 38 | F.1                        | 1655                      | maksymalna masa całkowita pojazdu, wyłączając motocykle i motorowery (w kg)
| 39 | F.2                        | 1655                      | dopuszczalna masa całkowita pojazdu (w kg)
| 40 | F.3                        | 2655                      | dopuszczalna masa całkowita zespołu pojazdów (w kg)
| 41 | G                          | 1205                      | masa własna pojazdu; w przypadku pojazdu ciągnącego innego niż kategoria M1 masa własna pojazdu obejmuje urządzenie sprzęgające (w kg)
| 42 | J                          | M1                        | kategoria pojazdu
| 43 | K                          | e11\*2001/116\*0180\*04   | numer świadectwa homologacji typu pojazdu, jeżeli występuje
| 44 | L                          | 2                         | liczba osi
| 45 | O.1                        | 1000                      | maksymalna masa całkowita przyczepy z hamulcem (w kg)
| 46 | O.2                        | 450                       | maksymalna masa całkowita przyczepy bez hamulca (w kg)
| 47 | Q                          | ---                       | stosunek mocy do masy własnej (w kW/kg); dotyczy motocykli i motorowerów
| 48 | P.1                        | 1398,00                   | pojemność silnika (w cm3)
| 49 | P.2                        | 71,00                     | maksymalna moc netto silnika (w kW)
| 50 | P.3                        | P                         | rodzaj paliwa
| 51 | B                          | 2005-07-01                | data pierwszej rejestracji pojazdu (YYYY-MM-DD)
| 52 | S.1                        | 5                         | liczba miejsc siedzących, włączając siedzenie kierowcy
| 53 | S.2                        | ---                       | liczba miejsc stojących, jeżeli występuje
| 54 | RODZAJ POJAZDU             | SAMOCHÓD OSOBOWY          |
| 55 | PRZEZNACZENIE              |---                        |
| 56 | ROK PRODUKCJI              | 2005                      |
| 57 | DOPUSZCZALNA ŁADOWNOŚĆ     | ---                       |
| 58 | NAJWIĘKSZY DOP. NACISK OSI | 8,82                      | kN
| 59 | NR KARTY POJAZDU           | AAA0000000                |
| 60 | ?                          | 02650008000158            | kod identyfikacyjny
| 61 | ?                          | 03                        | rodzaj - kod
| 62 | ?                          | 02                        | podrodzaj - kod
| 63 | ?                          | 000                       | przeznaczenie - kod
| 64 | ?                          | 2000NNNNNNNN              | ?
| 65 | ?                          | 009002001                 | ?

Rodzaj paliwa:

* P – benzyna
* D – olej napędowy
* M – mieszanka (paliwo-olej)
* LPG – gaz płynny (propan-butan)
* CNG – gaz ziemny sprężony (metan)
* H – wodór
* LNG – gaz ziemny skroplony (metan)
* BD – biodiesel
* E85 – etanol
* EE – energia elektryczna
* 999 – inne

## License

Copyright (c) 2018 Piotr Roszatycki <piotr.roszatycki@gmail.com>

[GPL-3.0](https://opensource.org/licenses/GPL-3.0)
