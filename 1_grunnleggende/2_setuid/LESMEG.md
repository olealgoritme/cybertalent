# SUID, også kjent som set-user-id

I Linux har alle brukere en bruker-id (uid) og minst én gruppe-id (gid). Alle filer eies av én bruker og én gruppe, og har rettigheter knyttet til eieren, gruppen og *alle andre*. Disse rettighetene er read, write og execute, og kan sees ved å kjøre kommandoen `ls -l`:

```sh
$ ls -l FLAGG /usr/bin/id
-r-------- 1 basic2 login    33 Oct  3 10:27 FLAGG
-rwxr-xr-x 1 root   root  43808 Feb 28  2019 /usr/bin/id
 \_/\_/\_/   \___/  \___/
  |  |  |      |      `----- Gruppe
  |  |  |      `------------ Eier
  |  |  `------------------- Rettigheter for "andre"
  |  `---------------------- Rettigheter for gruppe
  `------------------------- Rettigheter for eier
```

Filen `FLAGG` kan kun leses av eieren (basic2), og ingen kan skrive eller kjøre filen. Filen `/usr/bin/id` kan leses og kjøres av alle, men kun eieren (root) kan skrive til filen.

Normalt vil en prosess (et kjørende program) ha samme rettigheter som brukeren som starter programmet. I noen tilfeller ønsker man at prosessen skal ha mulighet til å gjøre mer enn hva brukeren vanligvis har lov til, for eksempel `sudo` som lar en bruker kjøre kommandoer på vegne av en annen bruker.

Én løsning er å sette et flagg på programfilen som kalles *set-user-id*, eller *suid*. Dette gir prosessen samme rettigheter som eier av fila.

```sh
$ ls -l id
-r-sr-xr-x 1 basic2 login 43808 Oct  3 10:27 id
```

Her er rettigheter for eier `r-s`, som betyr read+execute med *suid*-flagget satt. Når man kjører denne programfilen vil prosessen ha samme rettigheter som eieren (basic2).

For å kjøre filer i mappen du står i må du skrive `./program`. Prøv selv:

```sh
$ ls -l /usr/bin/id ./id
$ /usr/bin/id
$ ./id
$ cat FLAGG
$ ???
$ scoreboard <FLAGG>
```
