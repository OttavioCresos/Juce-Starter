// VoiceStrip.h
#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_extra/juce_gui_extra.h>


class VoiceStrip : public juce::Component
{
public:
    VoiceStrip(juce::AudioProcessorValueTreeState& vts, const juce::String& voiceId);
    ~VoiceStrip() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::String stripId;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::ToggleButton powerButton;
    juce::Slider speedKnob, timeKnob, widthKnob, panKnob, volKnob;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachment, timeAttachment, widthAttachment, panAttachment, volAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VoiceStrip)
};
