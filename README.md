# Opdracht: Conway's Game of Life

## Context

Conway's *Game of Life* is een cellulair automaat dat bestaat uit een tweedimensionaal raster van cellen. Elke cel is **levend** of **dood**. De toestand van het raster evolueert in discrete stappen ("generaties") volgens vaste regels die alleen afhangen van de directe buren van elke cel.

Deze opdracht is bedoeld om basisvaardigheden in **imperatief programmeren**, **datastructure**, **iteratie**, **functies/methodes**, en **programmastructuur** te oefenen.

---

## Leerdoelen

Na het afronden van deze opdracht kun je:

- Een probleem analyseren en vertalen naar een algoritme
- Werken met 2D-datastructuren (arrays, vectors, lists, etc.)
- Pure logica scheiden van input/output
- Een programma modulair opbouwen
- Dezelfde specificatie implementeren in meerdere programmeertalen

---

## Probleembeschrijving

Je implementeert Conway's *Game of Life* volgens de volgende regels:

Voor elke cel in het raster geldt:

1. Een **levende cel** met minder dan 2 levende buren sterft (onderbevolking)
2. Een **levende cel** met 2 of 3 levende buren blijft leven
3. Een **levende cel** met meer dan 3 levende buren sterft (overbevolking)
4. Een **dode cel** met precies 3 levende buren wordt levend (voortplanting)

Alle updates gebeuren **gelijktijdig**: de volgende generatie wordt volledig berekend op basis van de huidige generatie.

---

## Functionele vereisten

Je programma moet minimaal het volgende ondersteunen:

### 1. Representatie van het speelveld

- Een rechthoekig raster met vaste afmetingen (bijv. `width x height`)
- Elke cel is levend of dood
- Randen mogen:
  - of altijd als dood beschouwd worden
  - of "wrap-around" gedrag hebben (toroidaal)

    --> kies een en documenteer je keuze

### 2. Initialisatie

Ondersteun minstens een van de volgende opties:

- Hard-coded startpatroon (bijv. glider, blinker)
- Willekeurige initialisatie
- Inlezen van een tekstbestand

*(Extra opties zijn toegestaan)*

### 3. Evolutie

- Bereken correct de volgende generatie
- Gebruik een **aparte datastructuur** voor de nieuwe generatie
- De huidige generatie mag niet tijdens de update worden overschreven

### 4. Visualisatie

- Toon het raster in tekstvorm (console)
  - Levend: bijv. `#` of `O`
  - Dood: bijv. `.` of spatie
- Toon meerdere generaties achter elkaar
- Voeg een korte pauze toe tussen generaties

---

## Technische eisen

- De implementatie moet **volledig in een taal** zijn

  (dus geen bindings, libraries of mixed-language oplossingen)
- Gebruik alleen standaardbibliotheken van de taal
- Geen externe Game of Life libraries
- De code moet compileerbaar / uitvoerbaar zijn via de command line

---

## Ontwerpvereisten

Je oplossing moet logisch gestructureerd zijn. Denk aan:

- Een aparte functie/methode voor:
  - het tellen van levende buren
  - het berekenen van de volgende generatie
  - het printen van het veld
- Beperkte code duplicatie
- Duidelijke namen voor variabelen en functies

---

## Verwachte output (voorbeeld)

```txt
Generation 12
................
.....###........
......#........
................
```

---

## Extra opdrachten (optioneel, voor verdieping)

Kies er een of meer:

- Voeg command-line argumenten toe (grootte, snelheid, aantal stappen)
- Ondersteun meerdere startpatronen
- Implementeer toroidale randen
- Stop de simulatie als het systeem stabiel wordt
- Tel en print statistieken (aantal levende cellen per generatie)
- Maak een eenvoudige GUI (alleen in talen waar dat logisch is)

---

## Reflectie

Schrijf kort (max. 1/2 pagina):

- Welke datastructuren heb je gekozen en waarom?
- Wat vond je lastig bij het implementeren?
- Wat zou je anders doen in een andere programmeertaal?

