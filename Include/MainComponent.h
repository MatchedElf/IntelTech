#pragma once
//
#include "../JuceLibraryCode/JuceHeader.h"
//
class MainComponent : public Component, public Button::Listener
{
public:
    MainComponent(void);
    ~MainComponent(void) override;
    //
    void paint(Graphics&) override;
    void resized(void) override;
    void buttonClicked(Button*) override;
    //
private:
    Label* MainLabel;
    Label* title;
    TextButton* play;
    TextButton* back;
    TextButton* front;
    VideoComponent* vid;
    File* file1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};