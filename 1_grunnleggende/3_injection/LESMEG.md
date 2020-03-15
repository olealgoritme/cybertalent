# Command injection

Sårbarheter der *brukerdata* tolkes som kommandoer er en klassiker som aldri går av moten. En av de enkleste variantene oppstår når brukerdata sendes rett til et *shell*. Teknikken kalles *command injection*, og man kan få programmet til å kjøre flere kommandoer enn tiltenkt ved å skille dem med en semikolon.

*Cross-site scripting* (*XSS*), *SQL injection*, *deserialization attacks* og *format string vulnerabilities* er andre variasjoner som kan føre til hele spekteret fra *informasjonslekkasjer* til *kodeeksekvering*.

Programfilene i denne katalogen sender brukerkontrollert data videre til operativsystemets `system()`-funksjon uten *sanitisering*. Det er bra for en hacker :)

Det er også en artig *format string-sårbarhet* her. Det er mulig å lese minne fra *stacken* ved å sende inn "%p.%p.%p....%p" (men dette trengs ikke for å lese ut flagget).

Prøv selv:

```sh
$ cat md5sum.c
$ ./md5sum FLAGG
$ ./md5sum "FLAGG LESMEG.md"
$ ./md5sum "FLAGG; id"
$ ???
$ scoreboard <FLAGG>
```
