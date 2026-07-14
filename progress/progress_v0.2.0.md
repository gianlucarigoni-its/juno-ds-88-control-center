# Progress v0.2.0

Data compilazione: 2026-07-14 16:14 CEST  
Versione di riferimento: 0.2.0  
Progetto: Juno DS-88 Control Center

## Scopo del file

Questo file è il diario incrementale della versione 0.2.0.  
Serve a tracciare progressi, decisioni tecniche, concetti appresi, problemi incontrati e soluzioni adottate durante lo sviluppo.

## Stato della versione

La 0.2.0 è ancora nella fase di consolidamento della base tecnica, ma l’architettura sta andando nella direzione giusta: UI e logica MIDI sono state separate meglio, il flusso di discovery dei device è diventato più chiaro e la connessione MIDI è stata resa affidabile.

L’obiettivo della versione è iniziare il controllo musicale vero e proprio sopra la base MIDI della 0.1.0, senza saltare troppo presto verso un editor troppo grande.

## Aggiornamento del 2026-07-14

Data di compilazione/aggiornamento: 2026-07-14 16:14 CEST

### Progressi fatti in questa chat

- chiarita la differenza tra separazione delle responsabilità in C++ e in linguaggi come C# o Java;
- definita una divisione più pulita tra `MainComponent` e `MidiService`;
- deciso di far tornare valori semplici dai metodi del service, soprattutto `bool` e `juce::Array<juce::MidiDeviceInfo>`;
- mantenuto `onLog` solo dove serve davvero, cioè come ponte per la ricezione MIDI e per il log verso la UI;
- migliorato la funzione di popolamento dei device nei `ComboBox`;
- compreso che `juce::ComboBox` va passato per riferimento e non per valore;
- chiarito che è meglio mantenere una funzione semplice e chiamarla due volte piuttosto che complicarla troppo presto;
- preparato il terreno per la futura 0.2.0 centrata sui parametri musicali.

### Decisioni tecniche prese

- `MidiService` gestisce device, connessioni, invio/ricezione MIDI;
- `MainComponent` gestisce UI, eventi dei bottoni, log visivo e aggiornamento dello stato;
- i metodi operativi del service ritornano valori semplici invece di dipendere dal log interno;
- la callback `onLog` resta come meccanismo di comunicazione con la UI, ma non viene abusata come risposta a ogni funzione;
- per ora è preferibile una funzione piccola e leggibile per aggiungere i device ai combo box, anche se viene chiamata due volte;
- la crescita dell’architettura deve restare graduale, senza introdurre complessità prematura.

### Concetti appresi

- in C++ header e implementation file hanno ruoli diversi: il `.h` dichiara, il `.cpp` definisce;
- molti oggetti JUCE, come `juce::ComboBox`, non si copiano: vanno passati per riferimento;
- `const &` è utile quando si vuole leggere senza copiare;
- `&` è utile quando si vuole modificare un oggetto esistente;
- un service dovrebbe esporre solo il necessario verso l’esterno;
- una callback `void` è perfetta quando serve notificare un evento, non restituire un risultato;
- `callAsync` è la strada giusta per riportare al thread UI un evento ricevuto dal callback MIDI;
- è meglio tenere la logica semplice e chiara che ottimizzarla troppo presto;
- il numero di porte MIDI rilevate non corrisponde sempre al numero di dispositivi fisici, perché un device può esporre più porte logiche.

### Problemi riscontrati

- errore di copia di `juce::ComboBox` quando la funzione riceveva il controllo per valore;
- confusione iniziale tra input e output nella popolazione dei combo box;
- log invertiti sul risultato della connessione;
- tendenza iniziale a far fare al service troppe cose, invece di limitarsi alle sue responsabilità;
- necessità di imparare a ragionare per riferimento e non per copia in C++;
- bisogno di distinguere con precisione tra UI, service e dati di dominio.

### Soluzioni adottate

- `appendMidiDevices(...)` è stata resa una funzione più semplice, da chiamare separatamente per input e output;
- il `ComboBox` viene passato per riferimento;
- i metodi del service ritornano `bool` o liste di device, e non si occupano della logica visiva;
- la UI decide come mostrare successo, fallimento e stato della connessione;
- la callback di MIDI incoming è rimasta il punto giusto per il passaggio dei messaggi verso il log grafico;
- si è scelto di mantenere la struttura attuale semplice e leggibile, invece di introdurre astrazioni premature.

## Concetti consolidati

### 1. Separazione delle responsabilità

Il progetto sta evolvendo verso una divisione più pulita:

- `MainComponent`: interfaccia utente e interazione;
- `MidiService`: gestione MIDI e connessioni;
- callback: comunicazione minima e controllata verso la UI.

### 2. Flusso dati più chiaro

Il flusso ora è più comprensibile:

- la UI chiede la discovery dei device;
- il service restituisce gli array;
- la UI popola i combo box;
- la UI chiede la connessione;
- il service ritorna `bool`;
- la UI aggiorna stato e log.

### 3. Progettazione graduale

Non serve costruire subito un’architettura completa per patch, performance, parametri e storage.  
Per questa fase, la struttura attuale è già abbastanza buona per imparare bene e non complicarsi inutilmente.

## Stato tecnico attuale

A questo punto il progetto ha una base più ordinata rispetto all’inizio:

- UI minima funzionante;
- discovery dei device corretta;
- populazione dei combo box corretta;
- gestione della connessione più pulita;
- feedback in UI più controllato;
- prime basi per la futura 0.2.0 sui parametri musicali.

## Limiti attuali

La versione non è ancora pronta per la parte musicale più avanzata:

- non c’è ancora un sistema di parametri/preset vero e proprio;
- non c’è ancora una struttura di dominio per patch o performance;
- il codice è ancora concentrato in un file principale, scelta accettabile per ora ma non finale;
- la logica del progetto deve ancora essere ulteriormente separata in moduli più chiari.

## Prossimi passi consigliati

1. consolidare la base UI/MIDI già funzionante;
2. introdurre i primi concetti di parametro musicale controllabile;
3. definire un piccolo oggetto di dominio per i controlli della 0.2.0;
4. mantenere il codice semplice e leggibile;
5. evitare di trasformare troppo presto il progetto in un editor completo.

## Nota finale

La 0.2.0 sta iniziando nel modo giusto: non con più codice, ma con più chiarezza.  
La cosa più importante imparata finora è che in C++ il modo in cui passi i dati, separi i ruoli e scegli cosa ritornare conta quanto la logica stessa.