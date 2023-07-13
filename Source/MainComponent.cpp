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
    //
    pop = new TextButton("Popup menu");
    addAndMakeVisible(pop);
    pop->setButtonText("...");
    pop->addMouseListener(this, false);
    //
    menu = new PopupMenu();
    menu->addItem(PopupMenu::Item("Item"));
    //
    logo = new ImageComponent("Play image");
    addAndMakeVisible(logo);
    logo->setImage(ImageCache::getFromFile(File::getCurrentWorkingDirectory().getChildFile("logop.png")));
    //
    chFile = new TextButton("Choose file");
    addAndMakeVisible(chFile);
    chFile->setButtonText("+");
    chFile->addListener(this);
    // 
    vid = new VideoComponent(true);
    addAndMakeVisible(vid);
    f1 = File::getCurrentWorkingDirectory().getChildFile("Videoo.mp4");
    check = f1.exists();
    //auto url = URL(f1);
    //auto result = vid->load(url);
    //
    slid = new Slider(Slider::LinearHorizontal, Slider::TextBoxLeft);
    slid->setTextBoxStyle(Slider::TextBoxLeft, true, 50, 20);
    slid->setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(slid);

    setSize(500, 500);
    myLayout = new StretchableLayoutManager();
    myLayout->setItemLayout(0, 10, 100, 50);
    myLayout->setItemLayout(1, 10, 100, 50);
}
//
MainComponent::~MainComponent(void)
{
    deleteAndZero(MainLabel);
    deleteAndZero(play);
    deleteAndZero(back);
    deleteAndZero(front);
    deleteAndZero(title);
    deleteAndZero(menu);
    deleteAndZero(logo);
    deleteAndZero(vid);
    deleteAndZero(pop);
    deleteAndZero(chFile);
    deleteAndZero(myLayout);
    deleteAndZero(slid);
    myChooser.reset();
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(0, 3, 71));
    ColourGradient bg(Colour::fromRGB(198, 89, 28), 0.0, 0.0, Colour::fromRGB(0, 3, 71), 300.0, 300.0, false);
    //bg.vertical(Colour::fromRGB(198, 89, 28), 0.0, Colour::fromRGB(0, 3, 71), 1.0);
    //bg.addColour(1.0, Colour::fromRGB(198, 89, 28));
    bg = ColourGradient::vertical(Colour::fromRGB(198, 89, 28), -250.0, Colour::fromRGB(0, 3, 71), 500.0);
    g.setGradientFill(bg);
    g.fillAll();
}
//
void MainComponent::resized(void)
{
    Component* comps[]{play, back};
    if(check == true) title->setText("true", dontSendNotification);
    else if(check == false) title->setText("false", dontSendNotification);
    //MainLabel->setBounds(getWidth() / 2 - 50, getHeight() / 2 - 150, 100, 100);
    chFile->setBounds(getWidth() / 2 - 250, 100, 50, 50);
    play->setBounds(getWidth() / 2 - 25, getHeight() / 2 + 150, 50, 50);
    back->setBounds(getWidth() / 2 - 75, getHeight() / 2 + 150, 50, 50);
    front->setBounds(getWidth() / 2 + 25, getHeight() / 2 + 150, 50, 50);
    title->setBounds(getWidth() / 2 - 250, getHeight() / 2 + 150, 100, 50);
    logo->setBounds(getWidth() / 2 - 100, getHeight() / 2 - 150, 200, 200);
    pop->setBounds(getWidth() / 2 + 125, getHeight() / 2 + 150, 50, 50);
    slid->setBounds(getWidth() / 2 - 250, getHeight() / 2 + 100, 375, 50);
    vid->setBounds(getWidth() / 2 - 100, getHeight() / 2 - 150, 200, 200);
    //myLayout->layOutComponents(comps, 2, 150, 350, getWidth(), getHeight(), false, true);
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
    else if(butt == front){
        MainLabel->setColour(Label::textColourId, juce::Colours::red);

    }
    else if (butt == chFile) {
        loadFile();
    }
}

void MainComponent::mouseDown(const MouseEvent& event)
{
    MainLabel->setColour(Label::textColourId, juce::Colours::white);
    PopupMenu menu1;
    menu1.addItem(PopupMenu::Item("Item"));
    menu1.addItem(PopupMenu::Item("Item2"));
    menu1.showMenuAsync(PopupMenu::Options().withMinimumWidth(100)
        .withMaximumNumColumns(3)
        .withPreferredPopupDirection(PopupMenu::Options::PopupDirection(0))
        .withTargetComponent(pop));
}

void MainComponent::VideoProcessing(const URL& url, Result result)
{
    if (result.wasOk()) {
        vid->play();
        resized();
    }
    else {
        AlertWindow::showMessageBoxAsync(MessageBoxIconType::WarningIcon, "Couldn't load the file!", result.getErrorMessage());
    }
}


void MainComponent::loadFile()
{
    myChooser = std::make_unique<FileChooser>("Please select the moose you want to load...",
        File::getSpecialLocation(File::userHomeDirectory),
        "*.mp4");

    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

    myChooser->launchAsync(folderChooserFlags, [this](const FileChooser& chooser)
    {
        File choosedFile(chooser.getResult());
        title->setText(choosedFile.getFileName(), dontSendNotification);

        //loadMoose(mooseFile);
        auto url = URL(choosedFile);
        auto result = vid->load(url);
        VideoProcessing(url, result);
    });
}

