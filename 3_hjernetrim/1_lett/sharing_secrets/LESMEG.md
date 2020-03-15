# Shamir's secret sharing

## Bakgrunn

*Secret sharing* er et konsept innen kryptografi hvor man deler en hemmelighet inn i *n* andeler, og krever *k* andeler for å finne ut hva hemmeligheten er. En måte å gjøre dette effektivt på er beskrevet av Adi Shamir, i systemet kalt *Shamir's Secret Sharing* (SSS).

SSS baserer seg på polynomligninger av grad *n-1*. Den resulterende funksjonen er lik hemmeligheten som skal distribueres når `x = 0`, og hver andel `x` av hemmeligheten tilsvarer `f(x)`.

Den generiske formelen blir da:

```
f_n(x) = a_0 + a_1*x + a_2*x^2 + a_3*x^3 + ... + a_(n-1)*x^(n-1)
f_n(0) = a_0 = ?
```

## k=2

For å starte begynner vi enkelt, med `k = 2` og små nok tall til at vi kan regne i hodet.

```
f2(x) = a_0 + a_1*x
f2(2) = 29
f2(1) = 26
f2(0) = a_0 = ?
```

Bruk scoreboard til å levere svaret og å få en andel til neste del.

## k=3

Alle utregningene gjøres i en *endelig kropp* (engelsk: *Finite Field*) med en forhåndsdefinert størrelse, for å unngå å lekke informasjon om hemmeligheten. I resten av denne oppgaven vil alle utregninger foregå modulo det ellevte Mersenne-primtallet.

```
f3(x) = a_0 + a_1*x + a_2*x^2
f3(2) = 73673086149599787963942979835811
f3(1) = 84657984464390529825364497916194
f3(0) = ?
```

## k=4 og k=9

Du må løse andre oppgaver for å samle nok andeler til å regne ut de neste svarene.

Du kan se andelene du har samlet her:

```sh
$ scoreboard --secret-shares
```
