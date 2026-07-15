#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "MidiService.h" 
#include "MidiParameter.h"

// 1. IL COMPONENTE GRAFICO (Il contenuto)
class MainComponent  :  public juce::Component
{
public:
    MainComponent()
    {
        midiService.setLogCallback([this](const juce::String& s){ appendLog(s); });

        // TITLE
        addAndMakeVisible(titleLabel);
        titleLabel.setText("juno-ds Control Center v0.2.0", juce::dontSendNotification);
        titleLabel.setJustificationType(juce::Justification::centredTop);

        // CONNECTION BUTTON
        addAndMakeVisible(connectionButton);
        connectionButton.onClick = [this]
        {
            midiService.resetConnection();
            
            auto inId = midiInputCombo.getSelectedId();
            auto outId = midiOutputCombo.getSelectedId();
            
            const auto& inputs = midiService.getMidiInputDevices();
            const auto& outputs = midiService.getMidiOutputDevices();
            
            if (inId <= 0 || outId <= 0)
            {
                connectionStatusValue.setText("Connessione fallita", juce::dontSendNotification);
                appendLog("Connessione fallita: input o output non selezionati");
                return;
            }

            auto inIndex = inId - 1;
            auto outIndex = outId - 1;

            if (inIndex < 0 || inIndex >= inputs.size() || outIndex < 0 || outIndex >= outputs.size())
            {
                connectionStatusValue.setText("Connessione fallita", juce::dontSendNotification);
                appendLog("Connessione fallita: selezione non valida rispetto ai device rilevati");
                return;
            }

            if (midiService.connectSelectedDevices(static_cast<int>(inIndex), static_cast<int>(outIndex)))
            {
                connectionStatusValue.setText("Connesso", juce::dontSendNotification);
                appendLog("MIDI input e output connessi correttamente");
            }
            else
            {
                connectionStatusValue.setText("Connessione fallita", juce::dontSendNotification);
                appendLog("Connessione MIDI fallita durante connectSelectedDevices");
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
            appendLog("Identifier " +  juce::String(midiService.getMidiInputDevices()[id].identifier));
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
            juce::int32 id = midiOutputCombo.getSelectedId()-1;
            appendLog("Identifier " +  juce::String(midiService.getMidiOutputDevices()[id].identifier));
        };

        // REFRESH DEVICES BUTTON
        addAndMakeVisible(refreshDevicesButton);
        refreshDevicesButton.onClick = [this]
        {
            appendLog("Button pressed: Refresh devices");
            clearCombo();
            
            juce::Array<juce::MidiDeviceInfo> midiInputAvailable = midiService.detectMidiInputDevices();
            appendMidiDevices(midiInputAvailable, midiInputCombo);
            appendLog("Found " +  juce::String(midiInputAvailable.size()) + " MIDI input devices");

            juce::Array<juce::MidiDeviceInfo> midiOutputAvailable = midiService.detectMidiOutputDevices();
            appendMidiDevices(midiOutputAvailable, midiOutputCombo);
            appendLog("Found " +  juce::String(midiOutputAvailable.size()) + " MIDI output devices");
        };

        // SEND NOTE BUTTON
        addAndMakeVisible(sendNoteButton);
        sendNoteButton.onClick = [this]
        {
            if(midiService.sendNote())  { appendLog("Note send"); }
            else                        { appendLog("Impossible to send the note. \n\tERRORE: device is not connected"); }
        };

        // VOLUME SLIDER + MIDI PARAMETER
        volumeMidiParameter.name = juce::String("Volume");
        volumeMidiParameter.ccNumber = 11;
        createSlider(volumeSlider, volumeMidiParameter, volumeLabel);

        // REVERB SLIDER + MIDI PARAMETER
        reverbMidiParameter.name = juce::String("Reverb");
        reverbMidiParameter.ccNumber = 91;
        createSlider(reverbSlider, reverbMidiParameter, reverbLabel);

        // CUTOFF SLIDER + MIDI PARAMETER
        cutoffMidiParameter.name = juce::String("Cutoff");
        cutoffMidiParameter.ccNumber = 74;
        createSlider(cutoffSlider, cutoffMidiParameter, cutoffLabel);

        // CHORUS SLIDER + MIDI PARAMETER
        chorusMidiParameter.name = juce::String("Chorus");
        chorusMidiParameter.ccNumber = 93;
        createSlider(chorusSlider, chorusMidiParameter, chorusLabel);

        // LOG
        addAndMakeVisible(logEditor);
        logEditor.setReadOnly(true);
        logEditor.setScrollbarsShown(true);
        logEditor.setMultiLine(true);
        logEditor.setReturnKeyStartsNewLine(true);
        

        juce::Array<juce::MidiDeviceInfo> midiInputAvailable = midiService.detectMidiInputDevices();
        appendMidiDevices(midiInputAvailable, midiInputCombo);
        appendLog("Found " +  juce::String(midiInputAvailable.size()) + " MIDI input devices");

        juce::Array<juce::MidiDeviceInfo> midiOutputAvailable = midiService.detectMidiOutputDevices();
        appendMidiDevices(midiOutputAvailable, midiOutputCombo);
        appendLog("Found " +  juce::String(midiOutputAvailable.size()) + " MIDI output devices");
        
        setSize(1200, 800);
    }

    ~MainComponent() override = default;

    void resized() override 
    {
        auto area = getLocalBounds().reduced(10);
        titleLabel.setBounds(area.removeFromTop(40));

        area.removeFromTop(10);
        
        auto connectionStatusRow = area.removeFromTop(25);
        connectionStatusRow.removeFromLeft(10);
        connectionStatusLabel.setBounds(connectionStatusRow.removeFromLeft(80));
        connectionStatusRow.removeFromLeft(10);
        refreshDevicesButton.setBounds(connectionStatusRow.withSizeKeepingCentre(150, 25));
        connectionStatusValue.setBounds(connectionStatusRow.removeFromLeft(150));
        connectionButton.setBounds(connectionStatusRow.removeFromRight(100));

        area.removeFromTop(15);
        

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

        // sendNoteButton.setBounds(area.removeFromTop(20));
        auto midiParameterLabelRow1 = area.removeFromTop(15);
        volumeLabel.setBounds(midiParameterLabelRow1.removeFromLeft(250));
        reverbLabel.setBounds(midiParameterLabelRow1.removeFromRight(250));
        auto midiParameterRow1 = area.removeFromTop(25);
        volumeSlider.setBounds(midiParameterRow1.removeFromLeft(250));
        reverbSlider.setBounds(midiParameterRow1.removeFromRight(250));
        auto midiParameterLabelRow2 = area.removeFromTop(15);
        cutoffLabel.setBounds(midiParameterLabelRow2.removeFromLeft(250));
        chorusLabel.setBounds(midiParameterLabelRow2.removeFromRight(250));
        auto midiParameterRow2 = area.removeFromTop(25);
        cutoffSlider.setBounds(midiParameterRow2.removeFromLeft(250));
        chorusSlider.setBounds(midiParameterRow2.removeFromRight(250));

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

    void clearCombo()
    {
        midiInputCombo.clear();
        midiOutputCombo.clear();
    }

    void appendMidiDevices(juce::Array<juce::MidiDeviceInfo> devicesList, juce::ComboBox& combo){
        for(int i=0; i<devicesList.size(); i++)
        {
            auto midiInfo = devicesList[i];
            combo.addItem(midiInfo.name, i+1);
        }
    }

    void createSlider(juce::Slider& slider, MidiParameter& parameter, juce::Label& label)
    {
        addAndMakeVisible(slider);

        slider.setRange(0, 127, 1);
        slider.onValueChange = [this, sliderPtr = &slider, parameterPtr = &parameter]
        {
            int value = sliderPtr->getValue();
            parameterPtr->setValue(value);

            if(midiService.setParameterValue(*parameterPtr))
                appendLog(parameterPtr->name + " (cc" + juce::String(parameterPtr->ccNumber) + ") midi inpostato a " + juce::String(parameterPtr->getValue()));
            else
                appendLog("Set" + parameterPtr->name + " (cc" + juce::String(parameterPtr->ccNumber) + ") failed");
        };

        addAndMakeVisible(label);
        label.setText(parameter.name, juce::dontSendNotification);
    }
    

private:
    MidiService midiService;

    juce::Label titleLabel;
    
    juce::Label connectionStatusLabel;
    juce::Label connectionStatusValue;
    
    juce::TextButton connectionButton { "Connect" };
    juce::TextButton refreshDevicesButton { "Refresh devices" };

    juce::Label midiInputLabel;
    juce::Label midiOutputLabel;
    juce::ComboBox midiInputCombo;
    juce::ComboBox midiOutputCombo;
    
    juce::TextButton sendNoteButton { "Send note"};
    
    juce::Slider volumeSlider;
    MidiParameter volumeMidiParameter;
    juce::Label volumeLabel;
    juce::Slider reverbSlider;
    MidiParameter reverbMidiParameter;
    juce::Label reverbLabel;
    juce::Slider cutoffSlider;
    MidiParameter cutoffMidiParameter;
    juce::Label cutoffLabel;
    juce::Slider chorusSlider;
    MidiParameter chorusMidiParameter;
    juce::Label chorusLabel;

    juce::TextEditor logEditor; 

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
        (void)commandLine; // currently unused
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
