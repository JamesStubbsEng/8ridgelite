/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth/GuitarSynth.h"

//==============================================================================
/**
*/
class _8stringDiAudioProcessor  : public juce::AudioProcessor, private HighResolutionTimer
{
public:
    //==============================================================================
    _8stringDiAudioProcessor();
    ~_8stringDiAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void hiResTimerCallback() override;
  
    double progress = 0.0;
    ProgressBar pBar;

private:
    //==============================================================================
    GuitarSynth synth;
    GuitarSynth synth2;

    AudioProcessorValueTreeState parameters;
    std::atomic<float>* naturalParameter = nullptr;
    std::atomic<float>* perfectParameter = nullptr;
    std::atomic<float>* stereoParameter = nullptr;
    std::atomic<float>* mono1Parameter = nullptr;
    std::atomic<float>* mono2Parameter = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_8stringDiAudioProcessor)
};
