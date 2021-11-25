/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_8stringDiAudioProcessorEditor::_8stringDiAudioProcessorEditor (_8stringDiAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    background = ImageCache::getFromMemory(BinaryData::_123_background1_png, BinaryData::_123_background1_pngSize);

    claf.setColour(Slider::thumbColourId, Colour::greyLevel(0.95f));
    claf.setColour(Slider::textBoxOutlineColourId, Colours::black);
    claf.setColour(Slider::rotarySliderFillColourId, Colours::black);
    claf.setColour(Slider::rotarySliderOutlineColourId, Colours::black);

    claf.setColour(TextButton::buttonColourId, Colours::black);
    claf.setColour(TextButton::textColourOffId, Colours::white);

    claf.setColour(TextButton::buttonOnColourId, claf.findColour(TextButton::textColourOffId));
    claf.setColour(TextButton::textColourOnId, claf.findColour(TextButton::buttonColourId));

    naturalButton.setButtonText("Natural");
    naturalButton.setRadioGroupId(42);
    naturalButton.setClickingTogglesState(true);
    naturalButton.setConnectedEdges(Button::ConnectedOnRight);
    naturalButton.setLookAndFeel(&claf);
    naturalAttachment.reset(new ButtonAttachment(valueTreeState, "natural", naturalButton));
    addAndMakeVisible(naturalButton);

    perfectButton.setButtonText("Perfect");
    perfectButton.setRadioGroupId(42);
    perfectButton.setClickingTogglesState(true);
    perfectButton.setConnectedEdges(Button::ConnectedOnLeft);
    perfectButton.setLookAndFeel(&claf);
    perfectAttachment.reset(new ButtonAttachment(valueTreeState, "perfect", perfectButton));
    addAndMakeVisible(perfectButton);

    stereoButton.setButtonText("Stereo");
    stereoButton.setRadioGroupId(32);
    stereoButton.setClickingTogglesState(true);
    stereoButton.setConnectedEdges(Button::ConnectedOnRight);
    stereoButton.setLookAndFeel(&claf);
    stereoAttachment.reset(new ButtonAttachment(valueTreeState, "stereo", stereoButton));
    addAndMakeVisible(stereoButton);

    mono1Button.setButtonText("Mono1");
    mono1Button.setRadioGroupId(32);
    mono1Button.setClickingTogglesState(true);
    mono1Button.setConnectedEdges(Button::ConnectedOnRight + Button::ConnectedOnLeft);
    mono1Button.setLookAndFeel(&claf);
    mono1Attachment.reset(new ButtonAttachment(valueTreeState, "mono1", mono1Button));
    addAndMakeVisible(mono1Button);

    mono2Button.setButtonText("Mono2");
    mono2Button.setRadioGroupId(32);
    mono2Button.setClickingTogglesState(true);
    mono2Button.setConnectedEdges(Button::ConnectedOnLeft);
    mono2Button.setLookAndFeel(&claf);
    mono2Attachment.reset(new ButtonAttachment(valueTreeState, "mono2", mono2Button));
    addAndMakeVisible(mono2Button);

    if (audioProcessor.progress < 1.0)
        addAndMakeVisible(audioProcessor.pBar);
    
    setSize (500, 500);
}

_8stringDiAudioProcessorEditor::~_8stringDiAudioProcessorEditor()
{

}

//==============================================================================
void _8stringDiAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(background, 0, 0, 500, 500, 0, 0, 2084, 2084, false);
}

void _8stringDiAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20, 20);
    auto width = area.getWidth();
    auto height = area.getHeight();
    auto bottom = area.removeFromBottom(height / 9);
    perfectButton.setBounds(bottom.removeFromRight(width / 4));
    naturalButton.setBounds(bottom.removeFromRight(width / 4));
    
    auto top = area.removeFromTop(height / 9);
    
    mono2Button.setBounds(top.removeFromRight(width / 6));
    mono1Button.setBounds(top.removeFromRight(width / 6));
    stereoButton.setBounds(top.removeFromRight(width / 6));

    if (audioProcessor.progress < 1.0)
        audioProcessor.pBar.centreWithSize(100, 40);
}


