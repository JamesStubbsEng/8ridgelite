/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_8stringDiAudioProcessor::_8stringDiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, Identifier("Bridgelite"),
                           {
                               std::make_unique<AudioParameterBool>("natural", "Natural", true),
                               std::make_unique<AudioParameterBool>("perfect", "Perfect", false),
                               std::make_unique<AudioParameterBool>("stereo", "Stereo", true),
                               std::make_unique<AudioParameterBool>("mono1", "Mono1", false),
                               std::make_unique<AudioParameterBool>("mono2", "Mono2", false),
                           }), pBar(progress)
#endif
{
    naturalParameter = parameters.getRawParameterValue("natural");
    perfectParameter = parameters.getRawParameterValue("perfect");
    stereoParameter = parameters.getRawParameterValue("stereo");
    mono1Parameter = parameters.getRawParameterValue("mono1");
    mono2Parameter = parameters.getRawParameterValue("mono2");
    startTimer(100);
}

_8stringDiAudioProcessor::~_8stringDiAudioProcessor()
{
}

//==============================================================================
const juce::String _8stringDiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool _8stringDiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _8stringDiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _8stringDiAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double _8stringDiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _8stringDiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _8stringDiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void _8stringDiAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String _8stringDiAudioProcessor::getProgramName (int index)
{
    return {};
}

void _8stringDiAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void _8stringDiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    synth2.setCurrentPlaybackSampleRate(sampleRate);
    
}

void _8stringDiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool _8stringDiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    auto numInput = layouts.getMainInputChannels();
    auto numOutput = layouts.getMainOutputChannels();
    
    
    if (numInput == 0 && numOutput == 2) return true; // stereo
    
    return false;
}
#endif

void _8stringDiAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (*perfectParameter)
        synth2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    else
        synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    if (*mono1Parameter)
    {
        auto leftChannelData = buffer.getWritePointer(0);
        auto rightChannelData = buffer.getWritePointer(1);
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            rightChannelData[sample] = leftChannelData[sample];
        }
    }

    else if (*mono2Parameter)
    {
        auto leftChannelData = buffer.getWritePointer(0);
        auto rightChannelData = buffer.getWritePointer(1);
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            leftChannelData[sample] = rightChannelData[sample];
        }
    }
     
}

//==============================================================================
bool _8stringDiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* _8stringDiAudioProcessor::createEditor()
{
    return new _8stringDiAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void _8stringDiAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void _8stringDiAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void _8stringDiAudioProcessor::hiResTimerCallback()
{
    stopTimer();
    synth.setupNatural(progress);
    synth2.setupPerfect(progress);

    //make an async call to the message thread to set the pBar visibility to false
    MessageManager::callAsync([&]()
    {
        pBar.setVisible(false);
    });
    
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _8stringDiAudioProcessor();
}
