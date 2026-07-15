
#pragma once

#include <juce_audio_devices/juce_audio_devices.h>
#include "MidiParameter.h"
#include <functional>

class MidiService : public juce::MidiInputCallback
{
public:
    MidiService();
    ~MidiService() override = default;

    void setLogCallback(std::function<void(const juce::String&)> callback);

    juce::Array<juce::MidiDeviceInfo> detectMidiInputDevices();
    juce::Array<juce::MidiDeviceInfo> detectMidiOutputDevices();

    const juce::Array<juce::MidiDeviceInfo>& getMidiInputDevices() const;
    const juce::Array<juce::MidiDeviceInfo>& getMidiOutputDevices() const;

    void resetConnection();
    bool connectSelectedDevices(int inputIndex, int outputIndex);
    bool sendNote();

    bool setParameterValue(const MidiParameter& midiParameter);

    void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message) override;

private:
    std::function<void(const juce::String&)> onLog;
    juce::Array<juce::MidiDeviceInfo> midiInputDevices;
    juce::Array<juce::MidiDeviceInfo> midiOutputDevices;
    std::unique_ptr<juce::MidiInput> midiInputConnection;
    std::unique_ptr<juce::MidiOutput> midiOutputConnection;
};