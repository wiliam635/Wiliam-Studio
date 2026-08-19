#include "MainComponent.h"

MainComponent::MainComponent() : keyboard(keyboardState)
{
    setAudioChannels(0, 2);
    addAndMakeVisible(keyboard);
    addAndMakeVisible(chordLabel);
    chordLabel.setText("—", juce::dontSendNotification);
    chordLabel.setFont(juce::FontOptions(32.0f, juce::Font::bold));
    chordLabel.setColour(juce::Label::textColourId, juce::Colour(0xff27e6ef));
    addAndMakeVisible(midiInputBox);
    addAndMakeVisible(refreshButton);
    refreshButton.onClick = [this] { refreshMidiInputs(); };
    refreshMidiInputs();
    startTimerHz(30);
    setSize(1100, 360);
}

MainComponent::~MainComponent()
{
    stopTimer();
    midiInput.reset();
    shutdownAudio();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff110d26));
    g.setColour(juce::Colour(0xff9c94bd));
    g.setFont(juce::FontOptions(12.0f));
    g.drawText("ACORDE DETECTADO", 24, 22, 220, 20, juce::Justification::left);
    g.drawText("ENTRADA MIDI", 24, 108, 220, 20, juce::Justification::left);
}

void MainComponent::resized()
{
    chordLabel.setBounds(24, 44, 260, 52);
    midiInputBox.setBounds(24, 132, 250, 34);
    refreshButton.setBounds(284, 132, 140, 34);
    keyboard.setBounds(24, 205, getWidth() - 48, 125);
}

void MainComponent::refreshMidiInputs()
{
    midiInputBox.clear();
    midiDevices = juce::MidiInput::getAvailableDevices();
    for (int i = 0; i < midiDevices.size(); ++i)
        midiInputBox.addItem(midiDevices[i].name, i + 1);
    midiInputBox.onChange = [this]
    {
        midiInput.reset();
        const int index = midiInputBox.getSelectedItemIndex();
        if (juce::isPositiveAndBelow(index, midiDevices.size()))
        {
            midiInput = juce::MidiInput::openDevice(midiDevices[index].identifier, this);
            if (midiInput != nullptr) midiInput->start();
        }
    };
    if (midiInputBox.getNumItems() > 0) midiInputBox.setSelectedItemIndex(0);
}

void MainComponent::handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
{
    juce::MessageManager::callAsync([this, message]
    {
        keyboardState.processNextMidiEvent(message);
        if (message.isNoteOn()) heldNotes.addIfNotAlreadyThere(message.getNoteNumber());
        if (message.isNoteOff()) heldNotes.removeFirstMatchingValue(message.getNoteNumber());
        updateChord();
    });
}

void MainComponent::updateChord()
{
    const auto result = chordDetector.detect(heldNotes);
    chordLabel.setText(result.valid ? result.name : "—", juce::dontSendNotification);
}

void MainComponent::timerCallback()
{
    // O MidiKeyboardComponent observa diretamente o MidiKeyboardState e repinta
    // as teclas quando o estado recebe eventos MIDI.
    keyboard.repaint();
}
