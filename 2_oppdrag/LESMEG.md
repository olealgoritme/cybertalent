# Situasjon

Vi har mottatt informasjon om at en ukjent trusselaktør har fått tilgang til maskiner knyttet til et av våre departementer. Basert på nåværende situasjonsforståelse er det lite som er kjent om hendelsesforløpet. Trusselen kommer fra en aktør i utlandet, trolig en aktør med omfattende ressurser.

Initiell analyse tilsier at aktøren eksfiltrerer data til domenet `cloud-c2-70`, på port 1337/TCP. Formatet er ukjent.

Det er også observert trafikk knyttet til aktøren mot denne nettadressen: `http://keystore/query.php?keyname=oper@cloud-mgr-15`

## Oppdrag

Vi trenger informasjon om trusselaktørens kapabiliteter og intensjon.

Initielt ønsker vi å få vite hvem som lastet opp nøkler til `keystore`.

Videre er din oppgave er å få tilgang til serveren `cloud-c2-70` og forsøke å avdekke hva som er stjålet i angrepet. Informasjon om trusselaktørens verktøy, infrastruktur, sertifikater og nøkler kan også være av interesse.

Viktig: Før du kan sette i gang med oppdraget må du **logge ut** og kjøre kommandoen:

```sh
$ ssh login@ctf.cybertalent.no START-OPPDRAG
```

Lykke til!
