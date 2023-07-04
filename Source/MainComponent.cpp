#include "../Include/MainComponent.h"
#include <iostream>
//
MainComponent::MainComponent(void) : Component("MainComponent"), MainLabel(0), play(0)
{
    setOpaque(true);
    MainLabel = new Label("First label", "FONT LOGO");
    addAndMakeVisible(MainLabel);
    MainLabel->setFont(Font(38, Font::bold));
    //
    title = new Label("title label", "Video name");
    addAndMakeVisible(title);
    title->setFont(Font(18, Font::bold));
    //
    play = new TextButton("Play button");
    addAndMakeVisible(play);
    play->setButtonText("|>");
    play->addListener(this);
    //
    back = new TextButton("back button");
    addAndMakeVisible(back);
    back->setButtonText("<<");
    back->addListener(this);
    //
    front = new TextButton("next button");
    addAndMakeVisible(front);
    front->setButtonText(">>");
    front->addListener(this);
    //file1 = new File("../Source/Videoo.mp4");
    //vid = new VideoComponent(true);
    //vid->load(f1);
    //
    setSize(500, 500);
    
}
//
MainComponent::~MainComponent(void)
{
    deleteAndZero(MainLabel);
    deleteAndZero(play);
    deleteAndZero(back);
    deleteAndZero(front);
    deleteAndZero(title);
    //deleteAndZero(vid);
    //delete(file1);
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(0, 3, 71));
}
//
void MainComponent::resized(void)
{
    MainLabel->setBounds(getWidth() / 2 - 50, getHeight() / 2 - 150, 100, 100);
    play->setBounds(getWidth() / 2 - 25, getHeight() / 2 + 150, 50, 50);
    back->setBounds(getWidth() / 2 - 75, getHeight() / 2 + 150, 50, 50);
    front->setBounds(getWidth() / 2 + 25, getHeight() / 2 + 150, 50, 50);
    title->setBounds(getWidth() / 2 - 250, getHeight() / 2 + 150, 100, 50);
}
//
void MainComponent::buttonClicked(Button* butt)
{
    if (butt == play) {
        MainLabel->setColour(Label::textColourId, juce::Colours::black);
    }
    else if (butt == back) {
        MainLabel->setColour(Label::textColourId, juce::Colours::white);
    }
    else {
        MainLabel->setColour(Label::textColourId, juce::Colours::red);

    }
}