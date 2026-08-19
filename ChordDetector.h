#pragma once
#include <JuceHeader.h>

class ChordDetector
{
public:
    struct Result
    {
        juce::String name;
        juce::String root;
        juce::String bass;
        juce::Array<int> notes;
        bool valid = false;
    };

    Result detect(const juce::Array<int>& heldNotes) const;

private:
    static juce::String noteName(int pitchClass);
};
