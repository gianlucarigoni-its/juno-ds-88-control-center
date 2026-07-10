# Juno DS-88 Control Center

## Visione del progetto

Juno DS-88 Control Center è un software desktop personale pensato per estendere in modo pratico le capacità della Roland Juno DS-88 durante studio, sound design, sperimentazione e preparazione di performance live.

L'obiettivo non è creare subito una DAW completa, ma un companion desktop serio, chiaro e progressivo che permetta di controllare, organizzare e richiamare più facilmente suoni, patch, performance e configurazioni operative. Il progetto deve partire piccolo ma funzionante, e crescere nel tempo senza perdere coerenza.

## Stato decisionale attuale

Le seguenti decisioni sono considerate fissate per la prossima fase di lavoro:

- **Sistema di sviluppo principale:** Windows nativo.
- **Percorso progetto:** `C:\DEV\juno-ds-88-control-center`.
- **Cartella JUCE locale:** `C:\DEV\JUCE`.
- **WSL:** non è il workflow principale per questo progetto.
- **Repo iniziale:** progetto personale, non pensato ora per setup multi-macchina o team.
- **Gestione JUCE:** cartella esterna alla repo, non submodule interno del progetto.
- **Obiettivo tecnico iniziale:** prima MIDI funzionante, poi evoluzione delle feature.
- **Principio architetturale:** separare logica MIDI, modello dati, persistenza e interfaccia utente.
- **Persistenza iniziale:** locale, senza database online.
- **Approccio alla complessità:** introdurre SysEx solo se richiesto da feature reali.

## Principi guida

Il progetto deve seguire questi principi:

- partire piccolo ma funzionante;
- preferire feature realmente usabili a feature solo belle da dire;
- separare bene logica MIDI, modello dei dati e interfaccia;
- progettare codice ordinato, scalabile e più facilmente testabile;
- evitare di introdurre complessità tecnica prima del necessario;
- usare la UI come parte reale della feature, non come rifinitura finale secondaria;
- costruire un software che migliori davvero il rapporto operativo con la Juno DS-88.

## Approccio alla testabilità

Per questo progetto, "più testabile" non significa iniziare subito con una suite ampia di test automatici. Significa prima di tutto strutturare il codice in moduli con responsabilità chiare.

Direzione scelta:

- la UI non deve contenere la logica di business;
- la logica MIDI non deve vivere nei componenti grafici;
- i dati del dominio non devono dipendere dalla UI;
- la persistenza locale deve restare separata dai componenti visivi.

Questo approccio rende il progetto più leggibile, più modificabile e più adatto a crescere nel tempo.

## Strategia MIDI e SysEx

La gestione della comunicazione con la tastiera seguirà questa strategia.

### Fase 1: MIDI standard

Obiettivi:

- detection device;
- apertura input/output;
- invio/ricezione messaggi base;
- test pratici di comunicazione;
- eventuale cambio programma o controllo semplice, se disponibile.

### Fase 2: studio mirato della Parameter Guide

Approccio:

- non leggere tutto in modo indiscriminato;
- scegliere 2-3 azioni concrete da ottenere;
- capire per ciascuna se bastano messaggi MIDI standard o serve SysEx.

### Fase 3: SysEx solo se una feature reale lo richiede

Regole:

- non introdurlo come obiettivo astratto;
- non usarlo per completezza teorica;
- adottarlo solo quando serve davvero a ottenere una funzione precisa.

## Visione funzionale del prodotto

Le funzioni ritenute oggi centrali per il prodotto completo sono queste:

1. Comunicazione con la tastiera MIDI.
2. Modifica di parametri di suoni o patch singoli in tempo reale.
3. Salvataggio in memoria locale di suoni o patch con parametri personalizzati.
4. Metodo veloce per richiamare suoni o patch memorizzati e farli suonare alla tastiera in tempo reale.
5. Creazione di configurazioni complesse con più suoni, layer, split, dual o strutture simili compatibili con la tastiera.
6. Memorizzazione locale delle configurazioni complesse create.
7. Metodo veloce per richiamare una configurazione complessa memorizzata e farla suonare alla tastiera in tempo reale.

Questa lista rappresenta la direzione del prodotto, non significa che tutto debba entrare immediatamente nelle primissime versioni di sviluppo.

## Standard qualitativi iniziali delle feature

Per considerare una feature davvero completata, oggi valgono almeno questi standard minimi:

- la feature deve avere una UI chiara e leggibile;
- il comportamento deve essere comprensibile all'utente;
- la tastiera deve rispondere in modo coerente alla modifica inviata;
- se il feedback live completo sulla tastiera è tecnicamente possibile, deve avvenire in tempo reale;
- se non è possibile un feedback perfettamente live, il sistema deve comunque applicare la modifica correttamente e in modo chiaro al termine dell'azione;
- l'utente deve capire se il comando è stato inviato, applicato, fallito o è limitato dal comportamento della tastiera.

Questi standard sono iniziali e potranno essere raffinati durante sviluppo e test.

## Strategia di versioning

La numerazione delle versioni seguirà una logica incrementale.

### Serie 0.x

Le versioni `0.x` rappresentano la fase di costruzione del prodotto:

- `0.1.0`, `0.2.0`, `0.3.0` ecc. serviranno per sviluppare, integrare e consolidare blocchi di funzionalità;
- una versione intermedia non deve per forza contenere una sola feature isolata;
- una versione può includere sia una nuova funzione sia la rifinitura o stabilizzazione di una precedente.

### Versione 1.0.0

La `1.0.0` rappresenterà il primo macro-obiettivo di prodotto completato:

- non una demo tecnica;
- non una mono-feature;
- ma una prima versione complessivamente sensata, usabile e coerente con la visione del progetto.

## Architettura concettuale iniziale

Quando inizierà la programmazione reale, i layer e i moduli di partenza verranno scelti in modo consapevole. Tuttavia, il principio architetturale fissato è già questo:

- **UI:** visualizzazione, input utente, feedback stato;
- **MIDI:** discovery device, connessione, invio e ricezione messaggi;
- **Domain:** concetti musicali del progetto come patch, configurazioni, setup;
- **Storage:** salvataggio e caricamento locale dei dati.

Questa separazione non va ancora considerata una struttura definitiva di cartelle o classi, ma una direzione obbligatoria di progetto.

## Persistenza locale

Per la fase iniziale del progetto la persistenza sarà locale. Non è previsto alcun database online.

Scelta operativa iniziale:

- partire semplice;
- salvare localmente i dati del progetto;
- mantenere aperta la possibilità di raffinare in seguito il formato o la struttura di memorizzazione.

## Direzione evolutiva

Nel breve periodo il progetto sarà un controller/editor personale della tastiera focalizzato sulla comunicazione reale con la Roland Juno DS-88 e sulla costruzione di una base tecnica ordinata.

Nel medio periodo potrà evolvere verso:

- editing più ricco di parametri selezionati;
- libreria locale di patch e configurazioni;
- richiamo rapido di suoni e setup;
- gestione di layer, split, dual e combinazioni più complesse.

Nel lungo periodo potrà aprire la strada a strumenti musicali software più ambiziosi, ma senza anticipare complessità inutili nelle prime versioni.