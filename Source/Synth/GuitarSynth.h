/*
  ==============================================================================

    GuitarSynth.h
    Created: 2 Oct 2020 11:51:35pm
    Author:  James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GuitarSynth : public juce::Synthesiser
{
public:
	void setupNatural(double& progress);
	void setupPerfect(double& progress);
private:
	// manager object that finds an appropriate way to decode various audio files.  Used with SampleSound objects.
	juce::AudioFormatManager audioFormatManager;
};
