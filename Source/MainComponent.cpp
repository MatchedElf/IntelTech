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
    title = new Label("title label", "");
    addAndMakeVisible(title);
    title->setFont(Font(18, Font::bold));
    //
    play = new TextButton("Play button");
    addAndMakeVisible(play);
    play->setButtonText("|>");
    play->addListener(this);
    play->setEnabled(false);
    //
    play1 = new ImageButton("Play button");

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
    pop->addListener(this);
    //
    menu = new PopupMenu();
    menu->addItem(PopupMenu::Item("Item"));
    //
    logo = new ImageComponent("Play image");
    addAndMakeVisible(logo);
    logo->setImage(ImageCache::getFromFile(File::getCurrentWorkingDirectory().getChildFile("logop.png")));
    //
    chFile = new TextButton("Choose file");
    chFile->setButtonText("+");
    chFile->addListener(this);
    // 
    vid = new VideoComponent(true);
    addAndMakeVisible(vid);
    vid->setVisible(false);
    addAndMakeVisible(chFile);
    f1 = File::getCurrentWorkingDirectory().getChildFile("Videoo.mp4");
    //check = f1.exists();
    //auto url = URL(f1);
    //auto result = vid->load(url);
    //
    slid = new Slider(Slider::LinearHorizontal, Slider::TextBoxLeft);
    slid->setTextBoxStyle(Slider::TextBoxLeft, true, 50, 20);
    slid->setNumDecimalPlacesToDisplay(0);
    slid->addListener(this);
    slid->setEnabled(false);
    slid->setColour(Slider::thumbColourId, Colour::fromRGB(198, 89, 28));
    slid->setColour(Slider::textBoxOutlineColourId, Colour::fromFloatRGBA(0, 0, 0, 0));
    addAndMakeVisible(slid);
    //
    vol = new Slider(Slider::LinearVertical, Slider::TextBoxBelow);
    vol->setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    vol->setNumDecimalPlacesToDisplay(0);
    vol->addListener(this);
    vol->setEnabled(false);
    vol->setRange(0, 100, 1);
    vol->setValue(100);
    addAndMakeVisible(vol);
    //
    speed = new Slider(Slider::LinearHorizontal, Slider::TextBoxLeft);
    speed->setTextBoxStyle(Slider::TextBoxLeft, true, 50, 20);
    speed->setNumDecimalPlacesToDisplay(2);
    speed->addListener(this);
    speed->setEnabled(false);
    speed->setRange(0.25, 4, 0.25);
    speed->setValue(1);
    addAndMakeVisible(speed);

    //
    setSize(500, 500);
    //
    myLayout = new StretchableLayoutManager();
    myLayout->setItemLayout(0, 10, 100, 50);
    myLayout->setItemLayout(1, 10, 100, 50);
    myLayout->setItemLayout(2, 10, 100, 50);
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
    deleteAndZero(vol);
    deleteAndZero(speed);
    myChooser.reset();
    queue.clear();
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colour::fromRGB(0, 3, 71));
    ColourGradient bg(Colour::fromRGB(198, 89, 28), 0.0, 0.0, Colour::fromRGB(0, 3, 71), 300.0, 300.0, false);
    //bg.vertical(Colour::fromRGB(198, 89, 28), 0.0, Colour::fromRGB(0, 3, 71), 1.0);
    //bg.addColour(1.0, Colour::fromRGB(198, 89, 28));
    //bg = ColourGradient::vertical(Colour::fromRGB(198, 89, 28), -250.0, Colour::fromRGB(0, 3, 71), 500.0);
    bg = ColourGradient::vertical(Colour::fromRGB(198, 89, 28), -250.0, Colour::fromRGB(0, 0, 0), 500.0);
    g.setGradientFill(bg);
    g.fillAll();
}
//
void MainComponent::resized(void)
{
    long propW1 = proportionOfWidth(0.1);
    long propH1 = proportionOfHeight(0.1);
    long propH6 = proportionOfHeight(0.6);
    long propH8 = proportionOfHeight(0.8);
    long propW8 = proportionOfWidth(0.8);
    long centreW = getWidth() / 2;
    //long centreH = getHeight() / 2;
    //long height = getHeight();
    int dist = 20;
    //if (check == true) {
    //    double sec = vid->getVideoDuration();
    //    slid->setRange(0, sec, 1);
    //}

    //Component* comps[]{play, back, front};
    //if(check == true) title->setText("true", dontSendNotification);
    //else if(check == false) title->setText("false", dontSendNotification);
    //MainLabel->setBounds(getWidth() / 2 - 50, getHeight() / 2 - 150, 100, 100);
    chFile->setBounds(propW1 * 9 - propH1, 0, propH1, propH1);
    play->setBounds(centreW - propH1 / 2, propH8, propH1, propH1);
    back->setBounds(centreW - propH1 / 2 - propH1 - dist, propH8, propH1, propH1);
    front->setBounds(centreW + propH1 / 2 + dist, propH8, propH1, propH1);
    title->setBounds(propW1 - propH1, 0, 2 * propH1, propH1);
    logo->setBounds(centreW - 100, getHeight() / 2 - 150, 200, 200);
    pop->setBounds(propW1 * 9 - propH1, propH8, propH1, propH1);
    //slid->setValue(vid->getPlayPosition());
    slid->setBounds(propW1, propH1 * 7, propW8, propH1);
    vol->setBounds(propW1 * 9, propH1, propH1, propH6);
    speed->setBounds(centreW - 3 * propH1 - propH1 / 2 - 3 * dist, propH8, 2 * propH1, propH1);
    vid->setBounds(propW1, propH1, propW8, propH6);
    //myLayout->layOutComponents(comps, 3, 150, 350, proportionOfWidth(0.5), proportionOfHeight(0.1), false, true);
}
//
void MainComponent::buttonClicked(Button* butt)
{
    if (butt == play) {
        if (vid->isPlaying()) {
            this->stopTimer();
            vid->stop();
        }
        else {
            this->startTimer(1000);
            vid->play();
        }
    }
    else if ( (butt == back) && (curI > 0) ) {
        curI--;
        title->setText(queue[curI].getFileName(), dontSendNotification);
        vid->load(queue[curI]);
        VideoProcessing();
    }
    else if((butt == front) && (curI < (queue.size() - 1) ) ){
        curI++;
        title->setText(queue[curI].getFileName(), dontSendNotification);
        vid->load(queue[curI]);
        VideoProcessing();

    }
    else if (butt == chFile) {
        loadFile();
    }
    else if (butt == pop){
        MainLabel->setColour(Label::textColourId, juce::Colours::white);
        PopupMenu menu1;
        menu1.addItem(PopupMenu::Item("Item"));
        menu1.addItem(PopupMenu::Item("Item2"));
        menu1.showMenuAsync(PopupMenu::Options().withMinimumWidth(100)
            .withMaximumNumColumns(3)
            .withPreferredPopupDirection(PopupMenu::Options::PopupDirection(0))
            .withTargetComponent(pop));
    }
}
//
//void MainComponent::mouseDown(const MouseEvent& event)
//{
//    MainLabel->setColour(Label::textColourId, juce::Colours::white);
//    PopupMenu menu1;
//    menu1.addItem(PopupMenu::Item("Item"));
//    menu1.addItem(PopupMenu::Item("Item2"));
//    menu1.showMenuAsync(PopupMenu::Options().withMinimumWidth(100)
//        .withMaximumNumColumns(3)
//        .withPreferredPopupDirection(PopupMenu::Options::PopupDirection(0))
//        .withTargetComponent(pop));
//}

void MainComponent::VideoProcessing()
{
    check = true;
    //
    vid->setVisible(true);
    logo->setVisible(false);
    slid->setEnabled(true);
    play->setEnabled(true);
    vol->setEnabled(true);
    speed->setEnabled(true);
    //
    double sec = vid->getVideoDuration();
    slid->setRange(0, sec, 1);
    //
    resized();
}


void MainComponent::loadFile()
{
    myChooser = std::make_unique<FileChooser>("Please select the moose you want to load...",
        File::getSpecialLocation(File::currentExecutableFile).getChildFile("..//..//..//..//..//..//Resources"),
        "*.mp4");

    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

    myChooser->launchAsync(folderChooserFlags, [this](const FileChooser& chooser)
    {
        File choosedFile(chooser.getResult());
        if (choosedFile.getFullPathName().isEmpty()) {
            //check = false;
            //vid->setVisible(false);
            //logo->setVisible(true);
            return;
        }
        //loadMoose(mooseFile);
        auto url = URL(choosedFile);
        auto result = vid->load(url);
        title->setText(choosedFile.getFileName(), dontSendNotification);
        if (result.wasOk()) {
            queue.push_back(choosedFile);
            curI++;
            VideoProcessing();
        }
        else {
            //check = false;
            //vid->setVisible(false);
            //logo->setVisible(true);
            AlertWindow::showMessageBoxAsync(MessageBoxIconType::WarningIcon, "Couldn't load the file!", result.getErrorMessage());
        }
    });
}

void MainComponent::sliderValueChanged(Slider* s)
{
    if (s == slid) {
        vid->setPlayPosition(s->getValue());
    }
    else if (s == vol) {
        vid->setAudioVolume(s->getValue() / 100);
    }
    else if (s == speed) {
        vid->setPlaySpeed(s->getValue());
    }
}
//
void MainComponent::timerCallback()
{
    slid->setValue(vid->getPlayPosition());

}

