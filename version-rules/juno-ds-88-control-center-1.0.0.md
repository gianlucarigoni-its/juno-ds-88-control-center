# Juno DS-88 Control Center - Versione 1.0.0

## Obiettivo

La `1.0.0` rappresenta il primo prodotto completo e sensato del progetto. Non deve essere una demo tecnica, ma una versione usabile davvero, coerente con la visione iniziale e abbastanza completa da avere valore musicale concreto.

## Scopo della versione

La `1.0.0` deve unire in un sistema unico tutte le funzioni fondamentali del progetto.

- comunicazione MIDI stabile con la Juno DS-88;
- modifica in tempo reale di parametri di suoni o patch singole;
- salvataggio locale di preset personalizzati;
- richiamo rapido di preset memorizzati;
- creazione di configurazioni più complesse;
- salvataggio e richiamo di queste configurazioni;
- UI chiara, leggibile e coerente in tutte le sezioni principali.

## Cosa deve fare

### 1. Comunicazione MIDI completa

La connessione con la tastiera deve essere affidabile e ben gestita.

Requisiti:

- detection device stabile;
- input e output MIDI funzionanti;
- stato connessione sempre chiaro;
- invio e ricezione base verificabili;
- comportamento prevedibile.

### 2. Controllo patch singole

L'utente deve poter modificare parametri mirati di un suono e usarli in modo pratico.

Requisiti:

- parametri selezionati controllabili;
- feedback chiaro in UI;
- risposta comprensibile della tastiera;
- esperienza d'uso semplice.

### 3. Salvataggio e richiamo locale

Le patch o i preset personalizzati devono poter essere memorizzati e richiamati velocemente.

Requisiti:

- salvataggio locale stabile;
- caricamento coerente;
- distinzione chiara tra dato temporaneo e dato salvato;
- richiamo rapido affidabile.

### 4. Configurazioni complesse

Il software deve gestire anche setup più ricchi, come layer, split, dual o strutture simili compatibili con la Juno DS-88.

Requisiti:

- configurazioni composte gestibili;
- visualizzazione chiara della struttura attiva;
- salvataggio locale di queste configurazioni;
- richiamo comprensibile e usabile in pratica.

### 5. UI completa ma pulita

L'interfaccia deve essere abbastanza completa da supportare tutto il flusso principale senza diventare confusa.

Requisiti:

- sezioni leggibili;
- feedback coerente;
- stato sempre visibile;
- esperienza ordinata sia per preset singoli sia per setup complessi.

## Standard di completamento

La `1.0.0` è completa quando:

- il progetto è usabile in modo sensato per lavoro reale;
- le funzioni principali sono presenti e collegate tra loro;
- la UI resta chiara e non genera ambiguità;
- il comportamento verso la tastiera è affidabile;
- il sistema appare stabile, coerente e maturo abbastanza da essere una prima release completa.

## Cosa non deve includere

Anche nella `1.0.0` non è necessario pretendere tutto.

- non serve coprire ogni singolo parametro del synth;
- non serve già una libreria avanzata con tutte le funzioni possibili;
- non serve una gestione SysEx completa;
- non serve trasformare il progetto in una DAW;
- non serve sovraccaricare la UI con feature premature.

## Struttura tecnica minima

La `1.0.0` deve confermare una struttura pulita e stabile.

- **UI:** sezioni principali, feedback, interazione utente;
- **MIDI:** discovery, connessione, invio e ricezione messaggi;
- **Domain:** patch, preset, configurazioni e stato del progetto;
- **Storage:** salvataggio e caricamento locale affidabili.

## Note di qualità

La `1.0.0` è ben riuscita se il progetto non sembra più una raccolta di esperimenti, ma un vero strumento musicale software.

La versione deve:

- essere completa ma non sovraccarica;
- risultare coerente con la roadmap 0.x;
- lasciare spazio a evoluzioni future senza dover essere rifatta da zero.
