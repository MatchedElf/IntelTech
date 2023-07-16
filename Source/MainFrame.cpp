#include "../JuceLibraryCode/JuceHeader.h"
#include "../Include/MainFrame.h"
#include "../Include/Application.h"
//
MainFrame::MainFrame(const String& name)
   : DocumentWindow(name, /*Desktop::getInstance().getDefaultLookAndFeel()
      .findColour(ResizableWindow::backgroundColourId),*/ juce::Colours::purple,
      DocumentWindow::allButtons)
{
   setUsingNativeTitleBar(true);
   setResizable(true, false);
   setResizeLimits(500, 400, 10000, 10000);
   setIcon(ImageCache::getFromFile(File::getCurrentWorkingDirectory().getChildFile("logop128.ico")));
   //
   //setContentOwned (new MainComponent(), false);
   setVisible(true);
   //
   MC = new MainComponent();
   //
   //Image img = ImageCache::getFromFile(File("../Source/logo32.ico"));
   //icon = new SystemTrayIconComponent();
   setContentOwned(MC, true);
   setFullScreen(true);

}