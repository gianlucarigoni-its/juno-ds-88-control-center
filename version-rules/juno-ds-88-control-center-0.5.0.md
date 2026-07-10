# Juno DS-88 Control Center - Versione 0.5.0

## Obiettivo

La `0.5.0` introduce il primo passo verso le configurazioni musicali più ricche, come layer, split, dual o strutture simili compatibili con la Juno DS-88.

## Scopo della versione

Questa versione serve a far salire il progetto di livello, passando dal singolo preset a una forma più articolata di setup.

- creare configurazioni composte da più parti;
- rappresentare in modo chiaro le zone o gli strati attivi;
- salvare localmente queste configurazioni;
- richiamarle in modo comprensibile;
- mantenere l'interfaccia semplice anche quando la struttura diventa più complessa.

## Cosa deve fare

### 1. Configurazione composta

Il software deve iniziare a gestire strutture musicali più ricche di una semplice patch singola.

Requisiti:

- supporto a più parti o elementi attivi;
- logica chiara per layer, split o dual se compatibili;
- rappresentazione visiva comprensibile;
- possibilità di distinguere i ruoli delle parti.

### 2. Visualizzazione chiara

La UI deve mostrare in modo leggibile cosa è attivo nella configurazione.

Requisiti:

- vista semplice delle zone o dei layer;
- stato immediatamente comprensibile;
- feedback chiaro quando si modifica una parte;
- nessuna confusione tra configurazione semplice e configurazione composta.

### 3. Salvataggio e richiamo

Le configurazioni complesse devono poter essere memorizzate localmente e richiamate.

Requisiti:

- salvataggio affidabile;
- caricamento coerente;
- identificazione chiara della configurazione attiva;
- flusso di richiamo leggibile per l'utente.

## Standard di completamento

La `0.5.0` è completa quando:

- una configurazione composta può essere creata e salvata;
- la UI mostra bene la struttura attiva;
- il richiamo funziona in modo affidabile;
- l'utente capisce subito cosa sta suonando;
- il sistema resta ordinato e non troppo tecnico da usare.

## Cosa non deve includere

In questa versione non è necessario completare:

- gestione avanzata di tutte le possibili combinazioni;
- browser musicale completo con filtri e tag;
- editing esteso di ogni parametro del synth;
- SysEx avanzato;
- funzioni da performance tool maturo.

## Struttura tecnica minima

La `0.5.0` deve estendere bene la struttura già esistente.

- **UI:** rappresentazione delle parti attive, selezione e richiamo;
- **MIDI:** invio dei dati necessari alla tastiera;
- **Domain:** modello delle configurazioni composte;
- **Storage:** salvataggio e caricamento delle configurazioni locali.

## Note di qualità

La `0.5.0` è ben riuscita se introduce complessità musicale senza perdere leggibilità.

La versione deve:

- restare comprensibile;
- non trasformarsi in una mini-DAW prematura;
- preparare il progetto alla fase di consolidamento verso la `1.0.0`.
