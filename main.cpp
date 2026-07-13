#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

// 1. IL COMPONENTE GRAFICO (Il contenuto)
class MainComponent  :  public juce::Component,
                        public juce::MidiInputCallback
{
public:
    MainComponent()
    {
        // TITLE
        addAndMakeVisible(titleLabel);
        titleLabel.setText("juno-ds Control Center v0.1.0", juce::dontSendNotification);
        titleLabel.setJustificationType(juce::Justification::centredTop);

        // CONNECTION BUTTON
        addAndMakeVisible(connectionButton);
        connectionButton.onClick = [this]
        {
            //RESETTO LE CONESSIONI SE ESISTONO
            if (midiInputConnection) { midiInputConnection->stop(); }
            midiInputConnection.reset();
            midiOutputConnection.reset();

            juce::int32 midiInputID;
            juce::int32 midiOutputID;
            midiInputID = midiInputCombo.getSelectedId();
            midiOutputID = midiOutputCombo.getSelectedId();
            if(midiInputID != 0 && midiOutputID != 0) 
            { 
                connectSelectedDevices(midiInputID-1, midiOutputID-1); 
            }
            else 
            {
                connectionStatusValue.setText("Connection Failed", juce::dontSendNotification);
                appendLog("Connection button pressed: Connection failed. \n\tERROR: Input device/output device is not selected");
            }

        };
        

        // CONNECTION STATUS 
        addAndMakeVisible(connectionStatusLabel);
        connectionStatusLabel.setText("Status: ", juce::dontSendNotification);
        addAndMakeVisible(connectionStatusValue);
        connectionStatusValue.setText("Not connected", juce::dontSendNotification);

        // MIDI INPUT
        addAndMakeVisible(midiInputLabel);
        midiInputLabel.setText("MIDI Input: ", juce::dontSendNotification);
        addAndMakeVisible(midiInputCombo);
        midiInputCombo.setTextWhenNothingSelected("scegli midi input");

        midiInputCombo.onChange = [this]
        {
            auto selectedText = midiInputCombo.getText();
            appendLog("input selected: " + selectedText);
            juce::int32 id = midiInputCombo.getSelectedId()-1;
            appendLog("Identifier " +  juce::String(midiInputDevices[id].identifier));
        };

        // MIDI OUTPUT
        addAndMakeVisible(midiOutputLabel);
        midiOutputLabel.setText("MIDI Output: ", juce::dontSendNotification);
        addAndMakeVisible(midiOutputCombo);
        midiOutputCombo.setTextWhenNothingSelected("scegli midi output");

        midiOutputCombo.onChange = [this]
        {
            auto selectedText = midiOutputCombo.getText();
            appendLog("output selected: " + selectedText);
            juce::int32 id = midiInputCombo.getSelectedId()-1;
            appendLog("Identifier " +  juce::String(midiInputDevices[id].identifier));
        };

        // REFRESH DEVICES BUTTON
        addAndMakeVisible(refreshDevicesButton);
        refreshDevicesButton.onClick = [this]
        {
            appendLog("Button pressed: Refresh devices");
            detectMidiDevices();
        };

        
        addAndMakeVisible(sendNote);
        sendNote.onClick = [this]
        {
            if(midiOutputConnection != nullptr)
            {
                // juce::MidiMessage msb = juce::MidiMessage::controllerEvent(1, 0, 87); // 0 per msb
                // midiOutputConnection->sendMessageNow(msb);
                // juce::MidiMessage lsb = juce::MidiMessage::controllerEvent(1, 32, 64); // 32 per lsb
                // midiOutputConnection->sendMessageNow(lsb);
                // juce::MidiMessage pc = juce::MidiMessage::programChange(1, 119);
                // midiOutputConnection->sendMessageNow(pc);

                midiOutputConnection->sendMessageNow(juce::MidiMessage::noteOn(1, 60, (juce::uint8)100));
                juce::Timer::callAfterDelay(500, [this] {
                    midiOutputConnection->sendMessageNow(juce::MidiMessage::noteOff(1, 60));
                });
                appendLog("Note send");

            }
            else
            {
                appendLog("Impossible to send the note. \n\tERRORE: device is not connected");
            }
        };

        // LOG
        addAndMakeVisible(logEditor);
        logEditor.setReadOnly(true);
        logEditor.setScrollbarsShown(true);
        logEditor.setMultiLine(true);
        logEditor.setReturnKeyStartsNewLine(true);
        

        detectMidiDevices();
        
        setSize(600, 400);
    }

    ~MainComponent() override = default;

    void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message) override
    {
        juce::String description;

        if (message.isNoteOn())
            description = "NOTE ON  ch=" + juce::String(message.getChannel())
                        + " note=" + juce::String(message.getNoteNumber())
                        + " vel=" + juce::String(message.getVelocity());
        else if (message.isNoteOff())
            description = "NOTE OFF ch=" + juce::String(message.getChannel())
                        + " note=" + juce::String(message.getNoteNumber());
        else if (message.isController())
            description = "CC  ch=" + juce::String(message.getChannel())
                        + " cc=" + juce::String(message.getControllerNumber())
                        + " val=" + juce::String(message.getControllerValue());
        else
            description = "MIDI msg (raw, size=" + juce::String(message.getRawDataSize()) + ")";

        // Thread-safe: passiamo al thread UI
        juce::MessageManager::callAsync([this, description]()
        {
            appendLog("[IN] " + description);
        });
        
    }

    void resized() override 
    {
        auto area = getLocalBounds().reduced(10);
        titleLabel.setBounds(area.removeFromTop(40));

        area.removeFromTop(10);
        
        auto connectionStatusRow = area.removeFromTop(25);
        connectionStatusRow.removeFromLeft(10);
        connectionStatusLabel.setBounds(connectionStatusRow.removeFromLeft(80));
        connectionStatusRow.removeFromLeft(10);
        connectionStatusValue.setBounds(connectionStatusRow.removeFromLeft(150));
        connectionButton.setBounds(connectionStatusRow.removeFromRight(100));

        area.removeFromTop(15);

        auto refreshButtonRow = area.removeFromTop(25);
        refreshDevicesButton.setBounds(refreshButtonRow.withSizeKeepingCentre(150, 25));

        area.removeFromTop(10);

        auto inputRow = area.removeFromTop(25);
        midiInputLabel.setBounds(inputRow.removeFromLeft(100));
        inputRow.removeFromLeft(10);
        midiInputCombo.setBounds(inputRow);
        
        area.removeFromTop(10);

        auto outputRow = area.removeFromTop(25);
        midiOutputLabel.setBounds(outputRow.removeFromLeft(100));
        outputRow.removeFromLeft(10);
        midiOutputCombo.setBounds(outputRow);
        
        area.removeFromTop(10);

        sendNote.setBounds(area.removeFromTop(20));

        logEditor.setBounds(area.removeFromBottom(120));
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkgrey);
        // g.setFont(24.0f);
        // g.setColour(juce::Colours::white);
        // g.drawText("Juno-DS Control Center", getLocalBounds(), juce::Justification::centred, true);
    }
    
    void appendLog(const juce::String& s)
    {
        logEditor.moveCaretToEnd();
        logEditor.insertTextAtCaret(s + "\n");
    }

    void detectMidiDevices()
    {
        
        midiInputCombo.clear();
        midiOutputCombo.clear();

        auto midiInputs = juce::MidiInput::getAvailableDevices();
        for(int i=0; i<midiInputs.size(); i++)
        {
            auto midiInfo = midiInputs[i];
            midiInputCombo.addItem(midiInfo.name, i+1);
        }
        midiInputDevices = midiInputs;
        appendLog("Found " +  juce::String(midiInputs.size()) + " MIDI input devices");


        auto midiOutputs = juce::MidiOutput::getAvailableDevices();
        for(int i=0; i<midiOutputs.size(); i++)
        {
            auto midiInfo = midiOutputs[i];
            midiOutputCombo.addItem(midiInfo.name, i+1);
        }
        midiOutputDevices = midiOutputs;
        appendLog("Found " +  juce::String(midiOutputs.size()) + " MIDI output devices");
    }

    void connectSelectedDevices(juce::int32 midiInputID, juce::int32 midiOutputID){
        juce::MidiDeviceInfo midiInputDeviceInfo = midiInputDevices[midiInputID];
        juce::MidiDeviceInfo midiOutputDeviceInfo = midiOutputDevices[midiOutputID];

        midiInputConnection = juce::MidiInput::openDevice(midiInputDeviceInfo.identifier, this);
        midiOutputConnection = juce::MidiOutput::openDevice(midiOutputDeviceInfo.identifier);

        if (midiInputConnection == nullptr || midiOutputConnection == nullptr)
        {
            connectionStatusValue.setText("Connection failed", juce::dontSendNotification);
            appendLog("Midi input/output device failed to connect");
        }
        else
        {
            midiInputConnection->start();
            connectionStatusValue.setText("Connected", juce::dontSendNotification);
            appendLog("Midi input and output devices are connected");
        }

    }

private:
    // ARRAY DI DEVICES RILEVATI
    juce::Array<juce::MidiDeviceInfo> midiInputDevices;
    juce::Array<juce::MidiDeviceInfo> midiOutputDevices;
    
    // CONNESSIONI
    std::unique_ptr<juce::MidiInput> midiInputConnection;
    std::unique_ptr<juce::MidiOutput> midiOutputConnection;


    juce::Label titleLabel;
    
    juce::Label connectionStatusLabel;
    juce::Label connectionStatusValue;
    
    juce::TextButton connectionButton { "Connect" };
    juce::TextButton refreshDevicesButton { "Refresh devices" };

    juce::Label midiInputLabel;
    juce::Label midiOutputLabel;
    juce::ComboBox midiInputCombo;
    juce::ComboBox midiOutputCombo;

    juce::TextEditor logEditor; 

    juce::TextButton sendNote { "Send note"};
};

// 2. LA FINESTRA PRINCIPALE (Il contenitore del sistema operativo)
class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow(juce::String name)
        : DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

// 3. IL CICLO DI VITA DELL'APPLICAZIONE (Il manager)
class JunoDsApplication : public juce::JUCEApplication
{
public:
    JunoDsApplication() = default;

    const juce::String getApplicationName() override       { return "Juno-DS Control Center"; }
    const juce::String getApplicationVersion() override    { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise(const juce::String& commandLine) override
    {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        mainWindow.reset();
    }

    void systemRequestedQuit() override
    {
        quit();
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(JunoDsApplication)
