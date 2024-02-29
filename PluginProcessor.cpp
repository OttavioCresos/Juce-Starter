#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                     #if ! JucePlugin_IsSynth
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     #endif
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                    ),
      apvts(*this, nullptr, "Parameters", createParameterLayout())
{
    // Other initialization code can go here...
}


PluginProcessor::~PluginProcessor()
{

}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = 1;
    // auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto depth = apvts.getRawParameterValue("G")->load();
    auto baseDelay = apvts.getRawParameterValue("M0")->load();
    auto modWidth = apvts.getRawParameterValue("MW")->load();
    auto lfoFreq = apvts.getRawParameterValue("fLFO")->load();
    auto offsetDegrees = apvts.getRawParameterValue("offDeg")->load();

    auto sampleRate = getSampleRate();
    auto baseDelaySamples = (baseDelay / 1000.0) * sampleRate;
    auto modWidthSamples = (modWidth / 1000.0) * sampleRate;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // calculate lfo modulation for current sample
            auto lfoPhase = (std::sin(2.0 * juce::MathConstants<double>::pi * lfoFreq * sample / sampleRate + juce::degreesToRadians(offsetDegrees)) + 1.0) / 2.0;
            auto modDelay = baseDelaySamples + modWidthSamples * lfoPhase;

            // ensure modulated delay is within buffer size
            int delaySamples = static_cast<int>(modDelay);
            int readPosition = sample - delaySamples;

            float delayedSample = 0.0f;
            if (readPosition >= 0)
            {
                delayedSample = channelData[readPosition];
            }

            // apply delay
            channelData[sample] = juce::jlimit(-1.0f, 1.0f, (channelData[sample] * (1 - depth)) + (delayedSample * depth));
        }

        juce::ignoreUnused (channelData);
        // ..do something to the data...
    }
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    // Here we will add our parameters
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // Adding parameters to the layout
    layout.add(std::make_unique<juce::AudioParameterFloat>("G", "Depth", 0.0f, 1.0f, 0.7f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("M0", "Base Delay", 5.0f, 30.0f, 25.0f)); // ms
    layout.add(std::make_unique<juce::AudioParameterFloat>("MW", "Modulation Width", 0.5f, 3.0f, 0.5f)); // ms
    layout.add(std::make_unique<juce::AudioParameterFloat>("fLFO", "LFO Frequency", 0.1f, 5.0f, 1.5f)); // Hz
    layout.add(std::make_unique<juce::AudioParameterFloat>("offDeg", "Offset Degrees", 0.0f, 360.0f, 145.0f)); 

    return layout;
}

//==============================================================================
// This creates a new instance of the plugin's editor..
juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
