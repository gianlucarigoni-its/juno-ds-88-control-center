# Juno DS-88 Control Center - Versione 0.2.0

## Obiettivo

La `0.2.0` introduce il primo vero livello di controllo musicale sopra la base MIDI costruita nella `0.1.0`. L'obiettivo è iniziare la modifica di parametri di suoni o patch singole in modo chiaro, affidabile e comprensibile per l'utente.

## Scopo della versione

Questa versione serve a trasformare la semplice comunicazione MIDI in un controllo più musicale e utile.

- modificare uno o pochi parametri mirati di una patch singola;
- inviare il cambiamento alla tastiera in modo corretto;
- mostrare il valore corrente in UI in modo leggibile;
- rendere chiaro se la modifica è stata applicata con successo;
- mantenere la struttura tecnica ordinata e scalabile.

## Cosa deve fare

### 1. Selezione dei parametri

La versione deve lavorare su un set piccolo e ben scelto di parametri, non sull'intero synth.

Requisiti:

- pochi parametri iniziali;
- nomi chiari e comprensibili;
- range di valori ben visibile;
- possibilità di capire subito cosa si sta modificando.

### 2. Modifica in tempo reale

Il software deve permettere all'utente di cambiare un parametro e vedere il risultato sulla tastiera nel modo più diretto possibile.

Requisiti:

- aggiornamento del valore dalla UI;
- invio del comando MIDI;
- feedback visivo dell'esito;
- comportamento stabile durante l'uso.

### 3. UI del controllo

La schermata deve rendere evidente il rapporto tra controllo e risultato musicale.

Requisiti:

- ogni parametro deve avere una rappresentazione leggibile;
- il valore attivo deve essere visibile;
- il feedback deve distinguere bene tra valore locale e valore applicato;
- l'interazione deve restare semplice.

## Standard di completamento

La `0.2.0` è completa quando:

- almeno un set piccolo di parametri è controllabile dalla UI;
- il controllo funziona in modo affidabile con la Juno DS-88;
- l'utente capisce cosa sta modificando;
- il feedback del sistema è chiaro;
- la base tecnica resta coerente con l'architettura del progetto.

## Cosa non deve includere

In questa versione non è necessario completare:

- salvataggio strutturato delle patch;
- libreria locale dei suoni;
- richiamo rapido dei preset memorizzati;
- layer, split, dual o configurazioni complesse;
- gestione avanzata SysEx;
- organizzazione completa della roadmap musicale.

## Struttura tecnica minima

La `0.2.0` deve mantenere la separazione già impostata e rafforzarla leggermente.

- **UI:** controlli, visualizzazione valore, feedback;
- **MIDI:** invio e ricezione dei messaggi necessari al controllo;
- **Domain:** rappresentazione dei parametri controllabili e dei loro valori;
- **Storage:** non ancora centrale per questa versione.

## Note di qualità

La `0.2.0` è ben fatta se il controllo è utile davvero, non solo presente.

La versione deve:

- essere chiara da usare;
- restare coerente con la 0.1.0;
- evitare di diventare un editor troppo vasto troppo presto;
- preparare bene il terreno per il salvataggio locale e il richiamo rapido delle patch.
