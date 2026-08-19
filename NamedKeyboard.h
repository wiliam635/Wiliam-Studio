#pragma once
#include <JuceHeader.h>

class NamedKeyboard final : public juce::MidiKeyboardComponent
{
public:
    explicit NamedKeyboard(juce::MidiKeyboardState& state)
        : MidiKeyboardComponent(state, juce::MidiKeyboardComponent::horizontalKeyboard)
    {
        setAvailableRange(21, 108);
        setLowestVisibleKey(21);
        setScrollButtonsVisible(false);
        setColour(keyDownOverlayColourId, juce::Colour(0xff1976d2));
        setColour(mouseOverKeyOverlayColourId, juce::Colour(0x331976d2));
        setColour(textLabelColourId, juce::Colour(0xff15212a));
    }

    void setActiveColour(juce::Colour colour)
    {
        setColour(keyDownOverlayColourId, colour);
        setColour(mouseOverKeyOverlayColourId, colour.withAlpha(0.22f));
        repaint();
    }

    juce::String noteLabel(int note) const
    {
        static constexpr const char* names[] { "C", "C#", "D", "Eb", "E", "F",
                                               "F#", "G", "Ab", "A", "Bb", "B" };
        return names[juce::jlimit(0, 127, note) % 12];
    }

protected:
    void drawWhiteNoteLabel(juce::Graphics& g, int midiNoteNumber,
                            juce::Rectangle<float> area, bool isDown) override
    {
        juce::ignoreUnused(isDown);
        g.setColour(findColour(textLabelColourId));
        g.setFont(juce::FontOptions(10.0f));
        g.drawText(noteLabel(midiNoteNumber) + juce::String(midiNoteNumber / 12 - 1),
                   area.reduced(2.0f), juce::Justification::centredBottom, false);
    }
};
