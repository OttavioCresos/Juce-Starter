#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor& p) : AudioProcessorEditor (&p)
    , processorRef (p)
{
    juce::ignoreUnused (processorRef);
    
    // Initialize each slider
    depthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(depthSlider);

    baseDelaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    baseDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(baseDelaySlider);

    modulationWidthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    modulationWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(modulationWidthSlider);

    lfoFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lfoFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(lfoFrequencySlider);

    offsetDegreesSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    offsetDegreesSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(offsetDegreesSlider);

    // Attach each slider to a parameter
    depthSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processorRef.apvts, "G", depthSlider));
    baseDelaySliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processorRef.apvts, "M0", baseDelaySlider));
    modulationWidthSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processorRef.apvts, "MW", modulationWidthSlider));
    lfoFrequencySliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processorRef.apvts, "fLFO", lfoFrequencySlider));
    offsetDegreesSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(processorRef.apvts, "offDeg", offsetDegreesSlider));
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
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
    // Define a margin or starting point for your layout
    int startX = 10;
    int startY = 10;
    int sliderWidth = 100;
    int sliderHeight = 100;
    int gap = 10;

// Position the other sliders based on the startX, startY, sliderWidth, sliderHeight, and gap...
    depthSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    baseDelaySlider.setBounds(startX + sliderWidth + gap, startY, sliderWidth, sliderHeight);
    modulationWidthSlider.setBounds(startX + 2 * (sliderWidth + gap), startY, sliderWidth, sliderHeight);
    lfoFrequencySlider.setBounds(startX, startY + sliderHeight + gap, sliderWidth, sliderHeight);
    offsetDegreesSlider.setBounds(startX + sliderWidth + gap, startY + sliderHeight + gap, sliderWidth, sliderHeight);


}
