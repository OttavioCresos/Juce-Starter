#pragma once
#include <juce_audio_processors/juce_audio_processors.h>


//==============================================================================
class PluginProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PluginProcessor();
    ~PluginProcessor() override;

    //==============================================================================
    void prepareToPlay (double, int) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override
    {
        #if JucePlugin_IsMidiEffect
            juce::ignoreUnused (layouts);
            return true;
        #else
            // This is the place where you check if the layout is supported.
            // In this template code we only support mono or stereo.
            // Some plugin hosts, such as certain GarageBand versions, will only
            // load plugins that support stereo bus layouts.
            if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
                && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
                    return false;

            // This checks if the input layout matches the output layout
        #if ! JucePlugin_IsSynth
            if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
                return false;
        #endif
            return true;
        #endif
    }

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    bool hasEditor() const override                         { return true; }
    juce::AudioProcessorEditor* createEditor() override;

    //==============================================================================
    const juce::String getName() const override             { return JucePlugin_Name; }

    bool acceptsMidi() const override
    {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool producesMidi() const override
    {
        #if JucePlugin_ProducesMidiOutput
            return true;
        #else
            return false;
        #endif
    }

    bool isMidiEffect() const override
    {
        #if JucePlugin_IsMidiEffect
            return true;
        #else
            return false;
        #endif
    }

    double getTailLengthSeconds() const override                 { return 0.0; }

    //==============================================================================
    int getNumPrograms() override                                { return 1; }
    int getCurrentProgram() override                             { return 0; }
    void setCurrentProgram (int) override                        {}
    
    //==============================================================================
    const juce::String getProgramName (int) override             { return {}; }
    void changeProgramName (int, const juce::String&) override   {}

    //==============================================================================
    void getStateInformation (juce::MemoryBlock&) override;
    void setStateInformation (const void*, int) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
