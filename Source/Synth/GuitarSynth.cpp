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
	{
		addVoice(new SamplerVoice());
	}

	// set up our AudioFormatManager class as detailed in the API docs
	// we can now use WAV and AIFF files!
	audioFormatManager.registerBasicFormats();

	// now that we have our manager, lets read a simple file so we can pass it to our SamplerSound object.
	//File* file = new File("C:/Users/James/Desktop/8StringDI/guitar_samples/0_e1.wav");
	//ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(*file);
	//// allow our sound to be played on all notes
	//BigInteger allNotes;
	//allNotes.setRange(28, 28, true);
	//addSound(new SamplerSound(std::to_string(28), *reader, allNotes, 28, 0, 0.01, 10.0));


	

	// From BinaryData
	//WavAudioFormat formatManager;
	//MemoryInputStream* input = new MemoryInputStream(BinaryData::_0_e1_wav, BinaryData::_0_e1_wavSize, false);
	//AudioFormatReader* reader = formatManager.createReaderFor(input, false);
	//BigInteger allNotes;
	//allNotes.setBit(16);
	//addSound(new SamplerSound(std::to_string(16), *reader, allNotes, 16, 0, 0.01, 10.0));

	

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
		{
			allNotes.setRange(16, 28, true);
		}
		else
		{
			allNotes.setBit(k);
		}

		addSound(new SamplerSound(std::to_string(k), *reader, allNotes, k, 0.005, 0.01, 20.0));
		k++;

		//hardcode number of files
		progress += 1.0 / 122.0;
		
	}

	
  //  for (int i = 0; i < (BinaryData::namedResourceListSize-2)/2; ++i)
  //  {
  //      const char* binaryData = 0;
  //      int binaryDataSize = 0;

  //      binaryData = BinaryData::getNamedResource(BinaryData::namedResourceList[i], binaryDataSize);

		//MemoryInputStream* input = new MemoryInputStream(binaryData, binaryDataSize, false);
		////WavAudioFormat wavFormat;
		//FlacAudioFormat wavFormat;
		//AudioFormatReader* reader = wavFormat.createReaderFor(input, false);

		//BigInteger allNotes;
		//if (k == 28)
		//{
		//	allNotes.setRange(16, 28, true);
		//}
		//else
		//{
		//	allNotes.setBit(k);
		//}
		//
		//addSound(new SamplerSound(std::to_string(k), *reader, allNotes, k, 0.005, 0.01, 20.0));
		//k++;

		//progress += 1.0 / (double)(BinaryData::namedResourceListSize - 2);
		//DBG(progress);

		//delete reader;
  //  }




	
}

void GuitarSynth::setupPerfect(double& progress)
{
	// add voices to our sampler
	for (int i = 0; i < MAX_VOICES; i++)
	{
		addVoice(new SamplerVoice());
	}

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
		{
			allNotes.setRange(16, 28, true);
		}
		else
		{
			allNotes.setBit(k);
		}

		addSound(new SamplerSound(std::to_string(k), *reader, allNotes, k, 0.005, 0.01, 20.0));
		k++;

		//hardcode number of files
		progress += 1.0 / 122.0;
	}
	//for (int i = (BinaryData::namedResourceListSize-2) / 2; i < BinaryData::namedResourceListSize -2; ++i)
	//{
	//	const char* binaryData = 0;
	//	int binaryDataSize = 0;

	//	binaryData = BinaryData::getNamedResource(BinaryData::namedResourceList[i], binaryDataSize);

	//	MemoryInputStream* input = new MemoryInputStream(binaryData, binaryDataSize, false);
	//	//WavAudioFormat wavFormat;
	//	FlacAudioFormat wavFormat;
	//	AudioFormatReader* reader = wavFormat.createReaderFor(input, false);

	//	BigInteger allNotes;
	//	if (k == 28)
	//	{
	//		allNotes.setRange(16, 28, true);
	//	}
	//	else
	//	{
	//		allNotes.setBit(k);
	//	}

	//	addSound(new SamplerSound(std::to_string(k), *reader, allNotes, k, 0.005, 0.01, 20.0));
	//	k++;

	//	progress += 1.0 / (double)(BinaryData::namedResourceListSize - 2);
	//	DBG(progress);

	//	delete reader;
	//}





}