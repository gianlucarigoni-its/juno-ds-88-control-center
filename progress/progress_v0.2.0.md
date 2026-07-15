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

## Aggiornamento del 2026-07-15

Data di compilazione/aggiornamento: 2026-07-15 03:41 CEST

### Progressi fatti in questa chat

- chiarita la scelta dei primi parametri musicali da controllare nella 0.2.0: volume, reverb, cutoff e chorus;
- confermato che i primi parametri possono essere modellati con una struttura semplice e generica, senza introdurre complessità prematura;
- capito che `MidiParameter` può restare una struct leggera con nome, numero di CC, valore e validazione del range tramite `jlimit`;
- chiarito che `jlimit` non genera errori, ma adatta silenziosamente il valore dentro il range valido;
- capito quando servono davvero getter e setter e quando invece bastano campi semplici con un solo setter per il valore;
- chiarita la differenza tra struct e class in C++ e il motivo per cui una struct è adatta a rappresentare dati di dominio semplici;
- capito che nel setup manuale con CMake non si usa `JuceHeader.h`, ma gli header dei moduli necessari, a partire da `juce_core`;
- chiarito che per la struct `MidiParameter` non serve un `.cpp`, perché i metodi sono piccoli e possono restare inline nell’header;
- iniziato a separare meglio il dominio dei parametri dal service MIDI;
- verificato che il servizio MIDI può ricevere un parametro generico e inviare un Control Change senza conoscere il nome specifico del controllo;
- confermato che il canale MIDI nel `controllerEvent(...)` è un dato importante e che il messaggio costruito è corretto come forma;
- chiarito che il warning su `commandLine` in `initialise(...)` non era il vero problema di compilazione, ma solo un parametro non usato;
- capito come sopprimere correttamente il warning di parametro non usato con `juce::ignoreUnused(...)` o con `(void) commandLine`;
- risolto che l’errore reale di build era un `LNK1168`, quindi un problema di file eseguibile ancora aperto o bloccato, non di codice sorgente;
- chiarito che uno slider JUCE non mostra da solo una label esterna e che per una UI leggibile conviene usare una `juce::Label` separata;
- compreso che `CC11` è più adatto della classica idea di volume in patch mode e che `CC7`/`CC11` hanno significati diversi nella catena del suono;
- compreso che `reverb send` e `chorus send` regolano la quantità di segnale mandata agli effetti, non il volume diretto del suono;
- verificato che volume, cutoff, reverb e chorus funzionano come controllo MIDI lato app e che il comportamento è coerente con le aspettative del progetto;
- chiarito che per la 0.2.0 ha più senso restare in patch mode e non anticipare la performance mode;
- consolidato l’idea che la 0.2.0 debba restare focalizzata su un controllo musicale semplice, utile e ben leggibile, senza diventare un editor completo troppo presto.

### Decisioni tecniche prese

- i primi quattro controlli della 0.2.0 restano volume, reverb, cutoff e chorus;
- `MidiParameter` viene trattata come una struttura di dominio semplice, generica e riusabile;
- il valore del parametro viene validato internamente con `jlimit` per restare sempre nel range 0-127;
- per ora non servono classi più complesse o gerarchie di parametri;
- il service MIDI espone una funzione generica `setParameterValue(...)` per inviare qualsiasi parametro controllabile;
- il codice di invio MIDI resta basato su `juce::MidiMessage::controllerEvent(...)` e `sendMessageNow(...)`;
- la 0.2.0 viene mantenuta focalizzata sulla patch mode, rimandando la performance mode alle versioni future;
- la UI attuale può restare semplice e non perfetta, perché ha già raggiunto un livello sufficiente per questa fase;
- la crescita dell’interfaccia grafica sarà affrontata solo se e quando servirà davvero per la versione successiva;
- la documentazione di progresso deve seguire la realtà del lavoro svolto, non solo il piano iniziale.

### Concetti appresi

- una struct in C++ può avere anche metodi, ma resta concettualmente adatta a contenere dati semplici;
- un setter ha senso quando deve garantire una regola, come il clamp del valore nel range MIDI;
- un getter o setter banale non serve sempre: va introdotto solo quando c’è un motivo reale;
- `juce::jlimit(low, high, value)` limita il valore dentro il range senza lanciare errori;
- un controllo MIDI può essere astratto in una struttura dati semplice, lasciando al service solo l’invio;
- `juce::Slider` non fornisce automaticamente una label leggibile separata: va aggiunta a mano se serve chiarezza;
- `CC11` può essere usato come controllo dinamico di espressione, non come volume assoluto;
- `reverb send` e `chorus send` sono parametri di mandata agli effetti e possono risultare meno immediati da percepire;
- in una fase iniziale del progetto conviene distinguere tra ciò che è utile oggi e ciò che potrebbe servire domani;
- preparare il codice per crescere non significa progettare in anticipo tutta la futura architettura.

### Problemi riscontrati

- iniziale confusione su quale struttura dati usare per rappresentare i parametri musicali;
- dubbio su quali moduli JUCE includere nel file header in assenza del template Projucer;
- errore di interpretazione del comportamento di `jlimit`, pensato inizialmente come possibile fonte di errore;
- warning sul parametro `commandLine` nella `JUCEApplication`, che sembrava un problema di build ma non lo era;
- errore di link `LNK1168` causato da eseguibile ancora aperto o bloccato;
- iniziale mancanza di chiarezza sul ruolo della label nella UI degli slider;
- difficoltà nel capire perché i parametri `reverb` e `chorus` fossero meno evidenti all’ascolto rispetto a volume e cutoff;
- rischio iniziale di anticipare troppo la performance mode rispetto agli obiettivi reali della 0.2.0;
- tendenza a voler aggiungere struttura e astrazione prima di aver consolidato il comportamento base.

### Soluzioni adottate

- scelta di una struct semplice e generica per rappresentare i parametri MIDI;
- uso di `juce::jlimit` per proteggere i valori del parametro;
- mantenimento del service MIDI come unico punto di invio dei messaggi;
- adozione di una funzione generica per l’invio del parametro invece di quattro funzioni specializzate;
- uso di `juce::ignoreUnused(...)` o `(void) commandLine` per i parametri non usati;
- interpretazione corretta del problema di build come errore di file bloccato, non di codice;
- uso di label separate per rendere più leggibile la UI dei controlli;
- mantenimento della 0.2.0 dentro il perimetro patch mode;
- accettazione della UI attuale come sufficiente per questa fase, senza rifarla subito;
- consolidamento del principio che prima si stabilizza il comportamento, poi si migliora l’aspetto.

### Stato aggiornato della versione

A questo punto la 0.2.0 ha una base molto più concreta:

- i parametri principali sono stati individuati e testati;
- il flusso UI → `MidiParameter` → `MidiService` → tastiera è funzionante;
- il comportamento dei controlli è stato verificato e risulta coerente con l’uso previsto;
- la distinzione tra patch mode e performance mode è stata chiarita;
- il progetto resta coerente con l’idea di partire piccolo ma funzionante;
- la struttura tecnica è abbastanza stabile da permettere il passo successivo senza dover ripartire da zero.

### Prossimi passi consigliati

1. consolidare il blocco dei quattro parametri come primo nucleo della 0.2.0;
2. rendere più ordinato il `MainComponent` senza stravolgere la UI;
3. tenere il service MIDI generico e pulito;
4. continuare a documentare ciò che si scopre davvero durante i test;
5. evitare di introdurre ora la performance mode o altre strutture non necessarie;
6. prepararsi alla prossima versione solo quando la base attuale è davvero stabile.

### Nota finale

La 0.2.0 sta seguendo una direzione sana: prima si è chiarita la base tecnica, poi si sono introdotti i primi controlli musicali reali, infine si è capito meglio il comportamento della tastiera e dei parametri MIDI.  
Il passo avanti più importante non è stato aggiungere feature, ma capire quali scelte sono davvero utili per il progetto e quali invece vanno rimandate.