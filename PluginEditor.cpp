#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor& p) : AudioProcessorEditor (&p)
    , processorRef (p)
{
    juce::ignoreUnused (processorRef);

    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 600);

    // Add voice strips
    for (int i = 1; i <= 8; ++i) {
        auto strip = new VoiceStrip(processorRef.apvts, juce::String(i));
        addAndMakeVisible(strip);
        voiceStrips.add(strip);
    }
}

PluginEditor::~PluginEditor() 
{
    
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized() 
{

    auto area = getLocalBounds();  // Get the total area of the plugin editor
    auto stripHeight = area.getHeight() / voiceStrips.size();  // Divide the area equally for each strip

    for (auto* strip : voiceStrips) {
        strip->setBounds(area.removeFromTop(stripHeight));  // Set the bounds for each strip and remove that area
    }

}
