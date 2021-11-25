/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel/CustomLookAndFeel.h"

//==============================================================================
/**
*/
class _8stringDiAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    _8stringDiAudioProcessorEditor (_8stringDiAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~_8stringDiAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _8stringDiAudioProcessor& audioProcessor;

    CustomLookAndFeel claf;

    TextButton naturalButton;
    TextButton perfectButton;

    TextButton mono1Button;
    TextButton mono2Button;
    TextButton stereoButton;

    Image background;

    AudioProcessorValueTreeState& valueTreeState;
    std::unique_ptr<ButtonAttachment> naturalAttachment;
    std::unique_ptr<ButtonAttachment> perfectAttachment;
    std::unique_ptr<ButtonAttachment> mono1Attachment;
    std::unique_ptr<ButtonAttachment> mono2Attachment;
    std::unique_ptr<ButtonAttachment> stereoAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_8stringDiAudioProcessorEditor)
};
