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
    void mouseDown(const MouseEvent& event);
    //
private:
    bool check;
    Label* MainLabel;
    Label* title;
    TextButton* play;
    TextButton* back;
    TextButton* front;
    TextButton* pop;
    TextButton* chFile;
    VideoComponent* vid;
    PopupMenu* menu;
    ImageComponent* logo;
    File* f1;
    StretchableLayoutManager* myLayout;
    Slider* slid;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};