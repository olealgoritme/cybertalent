# Reverse engineering

Enten du leter etter sårbarheter eller analyserer skadevare må du kunne plukke fra hverandre en programfil for å se hva den gjør, uten å ha tilgang til kildekode. Denne prosessen blir kalt *reverse engineering*, eller mer populært bare *reversing*. Å reverse større programmer krever mye tid og erfaring, og det tar lang tid å lære verktøyene til det fulle.

I lang tid har det beste verktøyet for reversing av programmer vært *IDA Pro*, og dette har nærmest vært en industristandard. I 2019 publiserte amerikanske *NSA* et internt verktøy de kaller *Ghidra*, som er gratis og åpen kildekode.

Det er mulig å løse denne oppgaven med enkle verktøy som `strings` og `objdump`, men vi anbefaler å bruke *Ghidra* eller gratisversjonen av *IDA*.

For å kopiere filer ut fra denne serveren kan du bruke kommandoen `scp` fra **din egen maskin**: `scp login@ctf.cybertalent.no:1_grunnleggende/5_reversing/check_password ./check_password`

Hvordan løser **du** denne oppgaven?

Linker:

* [Ghidra](https://ghidra-sre.org/)
* [Presentasjon av Ghidra fra INFILTRATE 2019](https://vimeo.com/335158460)
* [IDA](https://www.hex-rays.com/products/ida/support/download.shtml)
* [Radare2](https://www.radare.org/r/)
* [Binary ninja](https://binary.ninja/)
