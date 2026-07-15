#include <juce_audio_devices/juce_audio_devices.h>
#include "MidiService.h"
#include "MidiParameter.h"

MidiService::MidiService() {}

void MidiService::setLogCallback(std::function<void(const juce::String&)> callback)
{
    onLog = callback;
}

juce::Array<juce::MidiDeviceInfo> MidiService::getMidiInputDevices()
{
    return midiInputDevices;
}

juce::Array<juce::MidiDeviceInfo> MidiService::getMidiOutputDevices()
{
    return midiOutputDevices;
}

void MidiService::handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
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
        if (onLog)
            onLog("[IN] " + description);
    });
    
};

juce::Array<juce::MidiDeviceInfo> MidiService::detectMidiInputDevices()
{
    midiInputDevices = juce::MidiInput::getAvailableDevices();
    return midiInputDevices;
}

juce::Array<juce::MidiDeviceInfo> MidiService::detectMidiOutputDevices()
{
    midiOutputDevices = juce::MidiOutput::getAvailableDevices();
    return midiOutputDevices;
}

void MidiService::resetConnection(){
    //RESETTO LE CONESSIONI SE ESISTONO
    if (midiInputConnection) { midiInputConnection->stop(); }
    midiInputConnection.reset();
    midiOutputConnection.reset();
}

bool MidiService::connectSelectedDevices(juce::int32 midiInputID, juce::int32 midiOutputID){
    juce::MidiDeviceInfo midiInputDeviceInfo = midiInputDevices[midiInputID];
    juce::MidiDeviceInfo midiOutputDeviceInfo = midiOutputDevices[midiOutputID];

    midiInputConnection = juce::MidiInput::openDevice(midiInputDeviceInfo.identifier, this);
    midiOutputConnection = juce::MidiOutput::openDevice(midiOutputDeviceInfo.identifier);

    if (midiInputConnection == nullptr || midiOutputConnection == nullptr)
    {
        return false;
    }
    else
    {
        midiInputConnection->start();
        return true;
    }

}

bool MidiService::sendNote(){
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
        return true;
    }
    else
    {
        return false;
    }
}

bool MidiService::setParameterValue(const MidiParameter& midiParameter)
{
    if(midiOutputConnection != nullptr)
    {
        midiOutputConnection->sendMessageNow(juce::MidiMessage::controllerEvent(1, midiParameter.ccNumber, midiParameter.getValue()));
        return true;
    }
    else return false;
}