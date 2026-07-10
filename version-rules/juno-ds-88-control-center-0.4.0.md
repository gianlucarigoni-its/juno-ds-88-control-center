# Juno DS-88 Control Center - Versione 0.4.0

## Obiettivo

La `0.4.0` introduce il primo richiamo rapido delle patch o dei preset memorizzati. Dopo il salvataggio locale della versione precedente, il progetto inizia a diventare davvero comodo da usare nella pratica quotidiana.

## Scopo della versione

Questa versione serve a collegare memoria locale e uso reale sulla tastiera.

- richiamare rapidamente un preset salvato;
- inviare alla Juno DS-88 i dati necessari per usarlo;
- distinguere chiaramente tra preset selezionato, preset attivo e preset salvato;
- rendere il flusso di richiamo semplice e affidabile;
- preparare il progetto alle configurazioni più complesse.

## Cosa deve fare

### 1. Selezione del preset

L'utente deve poter vedere e scegliere chiaramente un preset memorizzato.

Requisiti:

- lista leggibile dei preset salvati;
- identificazione chiara del preset attivo;
- selezione semplice e veloce;
- feedback visivo immediato.

### 2. Richiamo verso la tastiera

Il preset scelto deve poter essere richiamato sulla Juno DS-88 in modo coerente.

Requisiti:

- invio corretto dei dati necessari;
- comportamento prevedibile;
- conferma dell'operazione;
- gestione chiara di eventuali limiti tecnici.

### 3. UI di richiamo

La schermata deve rendere chiaro cosa è salvato, cosa è attivo e cosa è stato richiamato.

Requisiti:

- stato visibile;
- azione di richiamo semplice;
- feedback leggibile;
- nessuna confusione tra selezione e applicazione.

## Standard di completamento

La `0.4.0` è completa quando:

- i preset salvati possono essere richiamati con affidabilità;
- la tastiera riceve il preset corretto o la configurazione prevista;
- l'utente capisce sempre il risultato dell'operazione;
- il sistema resta semplice da usare;
- il richiamo rapido è abbastanza utile da giustificare il progetto stesso.

## Cosa non deve includere

In questa versione non è necessario completare:

- gestione avanzata dei layer multipli;
- dual o split complessi come feature piena;
- editing esteso di tutto il synth;
- browser avanzato con filtri e tag;
- SysEx avanzato;
- funzioni di performance complete.

## Struttura tecnica minima

La `0.4.0` deve mantenere la separazione già impostata e usare bene la parte di storage.

- **UI:** lista preset, selezione, richiamo, stato;
- **MIDI:** invio verso la tastiera e controllo dell'operazione;
- **Domain:** definizione del preset richiamabile;
- **Storage:** lettura dei dati salvati e supporto al richiamo.

## Note di qualità

La `0.4.0` è ben riuscita se il richiamo rapido è davvero comodo e non crea ambiguità.

La versione deve:

- essere più pratica della sola memorizzazione;
- restare semplice anche se il numero di preset cresce;
- preparare il progetto alle configurazioni più ricche della fase successiva.
