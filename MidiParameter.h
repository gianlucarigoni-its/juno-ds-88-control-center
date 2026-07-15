#pragma once
#include <juce_core/juce_core.h>

struct MidiParameter
{
    juce::String name;
    int ccNumber;

    void setValue (int newValue)
    {
        value = juce::jlimit (0, 127, newValue);
    }

    int getValue() const { return value; }

private:
    int value = 0;
};