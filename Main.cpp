#include <JuceHeader.h>
#include "MainComponent.h"

class WiliamStudioApplication final : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Wiliam Studio"; }
    const juce::String getApplicationVersion() override { return "0.1.0"; }
    void initialise(const juce::String&) override { mainWindow = std::make_unique<Window>(); }
    void shutdown() override { mainWindow.reset(); }
    class Window final : public juce::DocumentWindow
    {
    public:
        Window() : DocumentWindow("Wiliam Studio", juce::Colours::black, allButtons)
        { setUsingNativeTitleBar(true); setContentOwned(new MainComponent(), true); centreWithSize(1100, 360); setVisible(true); }
        void closeButtonPressed() override { juce::JUCEApplication::getInstance()->systemRequestedQuit(); }
    };
private: std::unique_ptr<Window> mainWindow;
};
START_JUCE_APPLICATION(WiliamStudioApplication)
