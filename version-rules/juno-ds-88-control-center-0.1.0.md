# Juno DS-88 Control Center - Versione 0.1.0

## Obiettivo

La `0.1.0` è la prima base tecnica reale del progetto. L'obiettivo è verificare che il software riesca a vedere la Juno DS-88, aprire una comunicazione MIDI affidabile e mostrare in modo chiaro lo stato di tutto ciò che accade.

Questa versione non deve ancora essere ricca di funzioni musicali: deve essere solida, leggibile e pronta per crescere.

## Scopo della versione

La `0.1.0` serve a costruire il fondamento del progetto:

- riconoscere i device MIDI disponibili;
- selezionare input e output corretti;
- aprire e chiudere la connessione in modo controllato;
- inviare e ricevere messaggi MIDI base;
- mostrare feedback chiaro all'utente;
- verificare che la base tecnica sia stabile su Windows nativo.

## Cosa deve fare

### 1. Rilevamento device MIDI

Il software deve elencare i device MIDI disponibili sul sistema e distinguere chiaramente quelli rilevati come input e output.

Requisiti:

- lista device aggiornata;
- nome device leggibile;
- stato di disponibilità comprensibile;
- selezione manuale del device corretto.

### 2. Connessione MIDI

Il software deve poter aprire una connessione MIDI verso la tastiera e chiuderla senza ambiguità.

Requisiti:

- apertura input;
- apertura output;
- stato connessione visibile;
- gestione base degli errori;
- possibilità di disconnessione pulita.

### 3. Comunicazione base

La versione deve confermare che il controller può scambiare messaggi MIDI con la Juno DS-88.

Requisiti:

- invio di messaggi MIDI semplici;
- ricezione di risposte o eventi, se disponibili;
- conferma visiva dell'esito;
- log minimale dei messaggi utili al debug.

### 4. UI minima e chiara

La schermata deve essere semplice ma leggibile.

Requisiti:

- stato connessione immediatamente visibile;
- device selezionato chiaramente mostrato;
- area dedicata ai test MIDI;
- messaggi di esito comprensibili;
- nessuna confusione tra stato, test e azioni dell'utente.

## Standard di completamento

La `0.1.0` è considerata completa quando:

- la Juno DS-88 viene rilevata correttamente;
- il device giusto può essere selezionato senza ambiguità;
- la connessione MIDI funziona in modo affidabile;
- l'invio base di messaggi MIDI è verificabile;
- l'utente capisce sempre cosa sta succedendo;
- l'interfaccia resta semplice e pulita.

## Cosa non deve includere

In questa versione non è necessario completare:

- editing avanzato dei parametri;
- salvataggio strutturato di patch;
- libreria locale dei suoni;
- layer, split, dual o creazioni complesse;
- gestione SysEx avanzata;
- logica di richiamo rapido dei preset;
- organizzazione musicale del contenuto del progetto.

## Struttura tecnica minima

La `0.1.0` deve già rispettare una separazione minima tra responsabilità.

- **UI:** mostra stato, seleziona device, avvia test;
- **MIDI:** gestisce discovery, connessione, input e output;
- **Domain:** contiene lo stato concettuale della connessione e dei test;
- **Storage:** non è ancora una parte centrale della versione.

## Note di qualità

La qualità della `0.1.0` non dipende dal numero di feature, ma dalla chiarezza della base tecnica.

La versione è ben riuscita se:

- è stabile;
- è facile capire cosa fa;
- è facile vedere se la connessione funziona;
- non mescola logica e UI in modo confuso;
- permette di partire bene con le versioni successive.
