#include "ChordDetector.h"

juce::String ChordDetector::noteName(int pitchClass)
{
    static constexpr const char* names[] { "C", "C#", "D", "Eb", "E", "F",
                                           "F#", "G", "Ab", "A", "Bb", "B" };
    return names[(pitchClass % 12 + 12) % 12];
}

ChordDetector::Result ChordDetector::detect(const juce::Array<int>& heldNotes) const
{
    Result result;
    result.notes = heldNotes;
    if (heldNotes.isEmpty()) return result;

    juce::Array<int> pitchClasses;
    for (auto note : heldNotes)
        if (! pitchClasses.contains(note % 12)) pitchClasses.add(note % 12);

    struct Pattern { const char* suffix; std::initializer_list<int> intervals; };
    static const Pattern patterns[] {
        { "maj9", { 0, 2, 4, 7, 11 } }, { "9", { 0, 2, 4, 7, 10 } },
        { "m9", { 0, 2, 3, 7, 10 } }, { "maj7", { 0, 4, 7, 11 } },
        { "m7", { 0, 3, 7, 10 } },
        { "7", { 0, 4, 7, 10 } }, { "m7(b5)", { 0, 3, 6, 10 } },
        { "m6", { 0, 3, 7, 9 } }, { "6", { 0, 4, 7, 9 } },
        { "add9", { 0, 2, 4, 7 } }, { "m(add9)", { 0, 2, 3, 7 } },
        { "m", { 0, 3, 7 } }, { "", { 0, 4, 7 } },
        { "dim", { 0, 3, 6 } }, { "aug", { 0, 4, 8 } },
        { "sus4", { 0, 5, 7 } }, { "sus2", { 0, 2, 7 } }
    };

    for (auto root : pitchClasses)
    {
        for (const auto& pattern : patterns)
        {
            if (pitchClasses.size() != static_cast<int>(pattern.intervals.size())) continue;
            bool matches = true;
            for (auto interval : pattern.intervals)
                if (! pitchClasses.contains((root + interval) % 12)) matches = false;
            if (matches)
            {
                result.root = noteName(root);
                result.bass = noteName(heldNotes.getFirst() % 12);
                result.name = result.root + pattern.suffix;
                if (heldNotes.getFirst() % 12 != root) result.name += "/" + result.bass;
                result.valid = true;
                return result;
            }
        }
    }
    return result;
}
