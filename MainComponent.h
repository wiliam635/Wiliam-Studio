#pragma once
#include <JuceHeader.h>
#include "NamedKeyboard.h"
#include "ChordDetector.h"

class MainComponent final : public juce::AudioAppComponent,
                            private juce::MidiInputCallback,
                            private juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;
    void prepareToPlay(int, double) override {}
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override {}
    void releaseResources() override {}
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage&) override;
    void timerCallback() override;
    void refreshMidiInputs();
    void updateChord();

    juce::MidiKeyboardState keyboardState;
    NamedKeyboard keyboard;
    ChordDetector chordDetector;
    juce::Label chordLabel;
    juce::ComboBox midiInputBox;
    juce::TextButton refreshButton { "Atualizar MIDI" };
    juce::Array<int> heldNotes;
    juce::Array<juce::MidiDeviceInfo> midiDevices;
    std::unique_ptr<juce::MidiInput> midiInput;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
