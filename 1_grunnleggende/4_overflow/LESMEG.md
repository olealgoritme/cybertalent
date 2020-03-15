# Buffer overflow

Hver prosess har sitt eget minneområde. Hvis man ved hjelp av en sårbarhet kan *endre på vilkårlige data i minnet* kan man få programmet til å gjøre noe annet enn tiltenkt.

Den klassiske måten å gjøre dette på ble beskrevet i artikkelen *Smashing The Stack For Fun And Profit*, publisert i *Phrack Magazine* #49 i 1996. For å forstå resten av denne teksten, anbefaler vi å lese artikkelen på `http://phrack.org/issues/49/14.html`.

Siden 90-tallet har både prosessorer, operativsystemer, kompilatorer og programmeringspråk introdusert mange mekanismer som forsøker å gjøre det vanskeligere å utnytte sårbarheter som tillater *minnekorrupsjon*. Hver for seg er disse mekanismene som regel enkle å omgå, men kombinasjonen av dem gjør det langt mer tidkrevende og komplisert å skrive *exploits* i dag enn for 20 år siden. Ofte vil man ha behov for å kombinere flere sårbarheter før man kan ta full kontroll over en prosess, for eksempel *minnelekkasjer* for å omgå *minnerandomisering* (ASLR), før man kan overskrive en *returadresse*.

Programmet i denne mappen er laget for å visualisere hvordan data plasseres på *stacken* og hvordan man kan påvirke programflyten i `main()`. Funksjonen setter av plass i minnet til en håndfull lokale variabler, og en av disse er et *buffer* på 32 byte. Det første argumentet kopieres inn i bufferet ved hjelp av `strcpy()` (uten å sjekke størrelsen på tekststrengen). Dette fører til at variablene som ligger på høyere minneadresser kan overskrives.

Det første skrittet for å lese ut flagget er å endre 'above' til en hardkodet verdi du finner i kildekoden. For å gjøre det siste skrittet lettere, allokeres det *eksekverbart minne* hvor du kan legge inn egen *shellkode*, eller bruke den som ligger i filen `sample_shellcode`.

```sh
$ export SHC=$(cat sample_shellcode)
$ cat overflow.c
$ ./overflow AAAAAAAA
$ ./overflow AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
$ ???
```
