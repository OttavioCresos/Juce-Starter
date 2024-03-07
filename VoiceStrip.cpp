// VoiceStrip.cpp
#include "VoiceStrip.h"

VoiceStrip::VoiceStrip(juce::AudioProcessorValueTreeState& vts, const juce::String& voiceId)
    : stripId(voiceId), valueTreeState(vts) 
{
    // Power Button
    powerButton.setClickingTogglesState(true);
    addAndMakeVisible(powerButton);

    // Speed Knob
    speedKnob.setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(speedKnob);

    // Time Knob
    timeKnob.setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(timeKnob);

    // Width Knob
    widthKnob.setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(widthKnob);

    // Pan Knob
    panKnob.setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(panKnob);

    // Volume Knob
    volKnob.setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(volKnob);

    // Attachments to link sliders to parameters
    powerAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "power" + stripId, powerButton));
    speedAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "speed" + stripId, speedKnob));
    timeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "time" + stripId, timeKnob));
    widthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "width" + stripId, widthKnob));
    panAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "pan" + stripId, panKnob));
    volAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "vol" + stripId, volKnob));
}

VoiceStrip::~VoiceStrip()
{
    // Destructor implementation (if needed)
}

void VoiceStrip::paint(juce::Graphics& g)
{
    // Custom painting code here (if needed)
    g.fillAll(juce::Colours::grey); // Just a placeholder color
}

void VoiceStrip::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto controlHeight = area.getHeight() / 6;
    powerButton.setBounds(area.removeFromTop(controlHeight));
    speedKnob.setBounds(area.removeFromTop(controlHeight));
    timeKnob.setBounds(area.removeFromTop(controlHeight));
    widthKnob.setBounds(area.removeFromTop(controlHeight));
    panKnob.setBounds(area.removeFromTop(controlHeight));
    volKnob.setBounds(area);
}
