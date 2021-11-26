/*
  ==============================================================================

    GuitarSynth.cpp
    Created: 2 Oct 2020 11:51:35pm
    Author:  James

  ==============================================================================
*/

#include "GuitarSynth.h"
#define MAX_VOICES 16

void GuitarSynth::setupNatural(double& progress)
{
	// add voices to our sampler
	for (int i = 0; i < MAX_VOICES; i++)
		addVoice(new SamplerVoice());

	audioFormatManager.registerBasicFormats();

	Array<File> files;
	File folder(File::getSpecialLocation(File::SpecialLocationType::commonApplicationDataDirectory).getChildFile("Haventone").getChildFile("Bridgelite").getChildFile("Natural"));
	folder.findChildFiles(files, File::findFiles, false);

	bool putFoldersFirst = false;
	File::NaturalFileComparator sorter(putFoldersFirst);
	files.sort(sorter);

	int k = 28;

	for (File file : files)
	{
		DBG(file.getFileName());
		ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(file);
		BigInteger allNotes;
		if (k == 28)
			allNotes.setRange(16, 28, true);
		else
			allNotes.setBit(k);

		addSound(new SamplerSound(std::to_string(k), *reader, allNotes, k, 0.005, 0.01, 20.0));
		k++;

		//hardcode number of files
		progress += 1.0 / 122.0;
	}
}

void GuitarSynth::setupPerfect(double& progress)
{
	// add voices to our sampler
	for (int i = 0; i < MAX_VOICES; i++)
		addVoice(new SamplerVoice());

	audioFormatManager.registerBasicFormats();

	Array<File> files;
	File folder(File::getSpecialLocation(File::SpecialLocationType::commonApplicationDataDirectory).getChildFile("Haventone").getChildFile("Bridgelite").getChildFile("Tuned"));
	folder.findChildFiles(files, File::findFiles, false);

	bool putFoldersFirst = false;
	File::NaturalFileComparator sorter(putFoldersFirst);
	files.sort(sorter);

	int k = 28;

	for (File file : files)
	{
		DBG(file.getFileName());
		ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(file);
		BigInteger allNotes;
		if (k == 28)
			allNotes.setRange(16, 28, true);
		else
			allNotes.setBit(k);

		addSound(new SamplerSound(std::to_string(k), *reader, allNotes, k, 0.005, 0.01, 20.0));
		k++;

		//hardcode number of files
		progress += 1.0 / 122.0;
	}
}
