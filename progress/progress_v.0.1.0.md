# Progress v0.1.0

Data compilazione: 2026-07-13
Versione di riferimento: 0.1.0
Progetto: Juno DS-88 Control Center

## Scopo del file

Questo file serve come memoria di continuità tra chat diverse durante lo sviluppo della versione 0.1.0.
Non va riscritto da zero ogni volta: va aggiornato aggiungendo nuovi progressi, decisioni, problemi e concetti emersi.

## Come aggiornarlo nelle prossime chat

Ad ogni nuova chat aperta durante la 0.1.0, aggiungere in coda:
- data di compilazione/aggiornamento;
- progressi fatti in quella chat;
- decisioni tecniche prese;
- concetti appresi;
- problemi riscontrati;
- eventuali prossimi passi.

## Stato attuale generale

La base tecnica iniziale della 0.1.0 è stata impostata e resa funzionante a livello di UI minima + discovery MIDI + prima connessione MIDI.
L'app attualmente:
- apre una finestra JUCE funzionante;
- mostra una UI minima con stato, selezione input/output, pulsanti e log;
- rileva i device MIDI disponibili;
- popola i ComboBox di input e output;
- conserva in memoria i `MidiDeviceInfo` rilevati;
- apre una connessione MIDI input/output sui device selezionati;
- aggiorna stato e log in base all'esito della connessione.

## Scelte tecniche prese

### Stack e base progetto
- Uso di **CMake + JUCE** con moduli espliciti.
- Inclusi nel codice:
  - `juce_gui_basics`
  - `juce_audio_devices`
- Per la fase attuale si è scelto di mantenere ancora tutto in un singolo `main.cpp`, accettandolo come passaggio didattico temporaneo.

### Impostazione UI attuale
La UI minima contiene:
- titolo;
- stato connessione;
- pulsante `Connect`;
- pulsante `Refresh devices`;
- combo box per MIDI input;
- combo box per MIDI output;
- area log.

### Discovery MIDI
La funzione `detectMidiDevices()` è stata introdotta con queste responsabilità:
- pulire i combo box;
- leggere i device MIDI input disponibili;
- leggere i device MIDI output disponibili;
- popolare i combo box;
- salvare in memoria gli array di `juce::MidiDeviceInfo`;
- scrivere un log minimale sul numero di device trovati.

### Connessione MIDI
Si è scelto, per ora, di non usare `AudioDeviceManager`, ma di aprire direttamente i device con:
- `juce::MidiInput::openDevice(...)`
- `juce::MidiOutput::openDevice(...)`

Questa scelta è stata fatta perché, in questa fase, il progetto è MIDI-only e serve soprattutto capire bene il flusso base di connessione.

La connessione attuale funziona così:
- l'utente seleziona input e output dai combo box;
- il pulsante `Connect` legge i selected id;
- i selected id vengono convertiti in indice array (`id - 1`);
- si recuperano i `MidiDeviceInfo` corrispondenti;
- si aprono input e output usando `identifier`;
- se l'apertura riesce, l'input viene avviato con `start()`;
- lo stato passa a `Connected`;
- il log viene aggiornato.

Prima di una nuova connessione, il codice:
- ferma l'eventuale input esistente con `stop()`;
- resetta le connessioni esistenti.

## Concetti appresi

### 1. Differenza tra modulo CMake e include C++
Aggiungere un modulo in `target_link_libraries(...)` non basta da solo: nel file sorgente serve anche l'`#include` corretto del modulo usato.

### 2. `juce::Button` è astratta
`juce::Button` non può essere istanziata direttamente perché contiene metodi virtuali puri.
Per i pulsanti normali della UI è corretto usare `juce::TextButton`.

### 3. `juce::MidiInputCallback` rende la classe astratta finché non si implementa il callback
Quando `MainComponent` eredita da `juce::MidiInputCallback`, deve implementare:
- `handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage&)`

### 4. `ComboBox`: selected id vs indice array
È emersa la distinzione importante tra:
- `getSelectedId()` -> id UI del combo box;
- indice reale dell'array -> da ricavare con `selectedId - 1` se gli item sono stati aggiunti con `i + 1`.

### 5. Gli item id del `ComboBox` non devono partire da 0
Negli item del combo box, `0` significa “nessuna selezione”.
Quindi gli item vengono aggiunti con `i + 1`, mentre gli array restano 0-based.

### 6. Nome device vs identifier
Per mostrare i device all'utente si usa il `name`.
Per aprire davvero il device si usa l'`identifier`.

### 7. Un device fisico può esporre più porte MIDI logiche
È stato osservato che una tastiera fisica può apparire con più entry MIDI, ad esempio una porta principale e una porta dedicata a controllo DAW.
Questo ha aiutato a capire perché il numero di input e output rilevati possa non coincidere con il numero di hardware fisici collegati.

### 8. Le connessioni non devono essere locali alla funzione
Gli oggetti `std::unique_ptr<juce::MidiInput>` e `std::unique_ptr<juce::MidiOutput>` devono vivere come membri della classe, altrimenti la connessione viene persa alla fine della funzione.

## Problemi riscontrati

### Errori iniziali di include/moduli
- Errore su include JUCE non corretto o non necessario.
- Necessità di aggiungere `juce_audio_devices` al target e agli include del sorgente.

### Errore con classe astratta `juce::Button`
Tentativo iniziale di dichiarare un `juce::Button` diretto, poi corretto usando `juce::TextButton`.

### Errore con classe astratta `MainComponent`
Dopo aver ereditato da `juce::MidiInputCallback`, `MainComponent` risultava astratta finché non è stato aggiunto l'override di `handleIncomingMidiMessage(...)`.

### Bug sugli indici nei cicli discovery
In una versione iniziale della discovery i cicli partivano da `1` e usavano accessi fuori range.
Il codice è stato corretto riportando i cicli a indice 0-based.

### Errore concettuale sugli item id del `ComboBox`
In una fase intermedia si usava direttamente `i` come item id, ma il primo elemento risultava con id `0`, che in JUCE non è valido come selezione reale.
Corretto passando a `i + 1`.

## Stato del codice a fine chat

A fine di questa chat, il codice riesce a fare correttamente:
- discovery dei device MIDI;
- popolamento dei combo box;
- selezione dei device;
- apertura di input/output;
- reset delle connessioni precedenti;
- aggiornamento stato e log;
- struttura base pronta per il prossimo test MIDI reale.

## Limiti attuali

La versione attuale non fa ancora:
- gestione reale dei messaggi MIDI in ingresso nel callback;
- invio di messaggi MIDI di test in uscita;
- distinzione tra UI, service MIDI e domain in classi separate;
- disconnect esplicito come azione UI dedicata;
- gestione più raffinata degli errori.

## Prossimi passi consigliati

Ordine consigliato per continuare la 0.1.0:
1. verificare un primo test MIDI reale (input o output);
2. decidere se testare prima ricezione o invio;
3. aggiungere feedback minimo sul test riuscito;
4. valutare quando iniziare a separare la logica MIDI dalla UI.

## Istruzione per l'uso futuro del file

Questo file va mantenuto come diario incrementale della 0.1.0.
Nelle prossime chat non va sostituito integralmente: vanno aggiunte nuove sezioni o nuovi blocchi datati in fondo, mantenendo traccia dell'evoluzione reale del progetto.


## Aggiornamento del 2026-07-14

Data di compilazione/aggiornamento: 2026-07-14

### Progressi fatti in questa chat
- test di input MIDI verificato come funzionante;
- test di output MIDI verificato con invio Note On/Note Off;
- test di Program Change verificato;
- introdotto e compreso il Bank Select tramite CC#0 e CC#32;
- chiarita la differenza tra numerazione umana delle patch e numero MIDI zero-based;
- confermato che la Juno DS-88 riceve messaggi MIDI reali dal software.

### Decisioni tecniche prese
- la v0.1.0 viene considerata chiusa con esito positivo;
- il file progress viene mantenuto come diario incrementale del progetto;
- la base attuale resta per ora concentrata in un singolo `main.cpp` come scelta didattica temporanea;
- il lavoro futuro dovrà iniziare come evoluzione della base già validata.

### Concetti appresi
- `handleIncomingMidiMessage(...)` viene chiamata automaticamente da JUCE quando arriva un messaggio MIDI;
- `juce::MessageManager::callAsync(...)` è la strada giusta per riportare dati al thread UI dal callback MIDI;
- il Bank Select non è un unico messaggio, ma una combinazione di due controller MIDI distinti;
- il Program Change è zero-based e spesso va convertito con `-1` rispetto al numero mostrato nelle patch list;
- i valori MIDI vanno trattati con attenzione rispetto alle liste patch della tastiera.

### Problemi riscontrati
- crash iniziale dovuto al tentativo di inviare note senza connessione MIDI attiva;
- confusione iniziale tra patch numbering umano e Program Change MIDI;
- necessità di capire la mappatura MSB/LSB/PC per selezionare patch precise sulla Juno DS-88.

### Eventuali prossimi passi
1. aprire la definizione della v0.2.0;
2. decidere le prime separazioni architetturali utili;
3. iniziare a progettare una struttura più ordinata per patch e performance;
4. mantenere il focus su semplicità, chiarezza e crescita progressiva.
