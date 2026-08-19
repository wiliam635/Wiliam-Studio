#pragma once
#include <JuceHeader.h>
#include <initializer_list>

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

    // Retorna false para conjuntos vazios ou não reconhecidos.
    bool isRecognised(const juce::Array<int>& heldNotes) const { return detect(heldNotes).valid; }

private:
    static juce::String noteName(int pitchClass);
};
