# Juno DS-88 Control Center - Versione 0.3.0

## Obiettivo

La `0.3.0` introduce il primo livello di gestione locale delle patch o dei suoni salvati. Dopo la connessione MIDI e il controllo base dei parametri, il progetto inizia a costruire una memoria personale utilizzabile dal computer.

## Scopo della versione

Questa versione serve a rendere il progetto più utile nella pratica quotidiana.

- salvare localmente patch o preset personalizzati;
- ricaricare i dati salvati in modo affidabile;
- distinguere chiaramente ciò che è temporaneo da ciò che è memorizzato;
- preparare il terreno per il richiamo rapido delle configurazioni;
- mantenere la struttura semplice e ordinata.

## Cosa deve fare

### 1. Salvataggio locale

Il software deve poter salvare una patch o un preset personalizzato in memoria locale.

Requisiti:

- salvataggio stabile;
- dati chiari e leggibili;
- organizzazione minima comprensibile;
- nessuna dipendenza da servizi esterni.

### 2. Caricamento locale

Il software deve poter ricaricare correttamente i dati salvati.

Requisiti:

- caricamento affidabile;
- coerenza tra dato salvato e dato letto;
- gestione chiara degli errori;
- comportamento prevedibile.

### 3. Organizzazione base

Le patch salvate devono iniziare ad avere una forma utile per l'uso futuro.

Requisiti:

- nome leggibile;
- identificazione chiara;
- struttura pronta per evolvere in una libreria più completa.

## Standard di completamento

La `0.3.0` è completa quando:

- il salvataggio locale funziona senza perdita dei dati;
- il caricamento locale restituisce correttamente ciò che è stato salvato;
- l'utente distingue bene i preset locali da quelli solo modificati in sessione;
- la UI resta semplice e non confusa;
- il sistema è pronto per il richiamo rapido nella versione successiva.

## Cosa non deve includere

In questa versione non è necessario completare:

- gestione avanzata di layer, split o dual;
- editing esteso dell'intero synth;
- libreria completa con filtri e tag;
- richiamo immediato delle patch memorizzate verso la tastiera;
- gestione SysEx avanzata;
- workflow completi da performance tool.

## Struttura tecnica minima

La `0.3.0` deve rafforzare la separazione già impostata.

- **UI:** salva, carica e mostra lo stato dei preset;
- **MIDI:** resta il canale di comunicazione con la tastiera;
- **Domain:** definisce il modello dei preset memorizzati;
- **Storage:** diventa una parte attiva e centrale della versione.

## Note di qualità

La `0.3.0` è ben riuscita se il sistema di memoria locale è semplice da usare e affidabile.

La versione deve:

- evitare confusione tra editing temporaneo e salvataggio reale;
- restare leggera da usare;
- preparare il progetto al richiamo rapido delle patch nella versione successiva.
