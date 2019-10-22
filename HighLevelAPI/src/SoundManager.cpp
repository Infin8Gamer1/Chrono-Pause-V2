/**
	* Author: David Wong
	* Created: 6 December 2018
	* Project: CS230 Lab 8
**/

// Includes //
#include "stdafx.h"
#include "SoundManager.h"

#include <fmod.h>			// Low Level System
#include <fmod_errors.h>	// FMOD errors

// Global Functions //
void FMOD_ASSERT(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "[ERROR]: " << FMOD_ErrorString(result) << std::endl;
	}
}

// Public Member Functions //

SoundManager::SoundManager()
	: BetaObject("SoundManager"), musicVolume(1), effectsVolume(1), audioFilePath("Audio/"), bankFilePath("Banks/"), eventPrefix("event:/"),
	numSounds(0), numBanks(0), musicChannel(nullptr), effectsChannelGroup(nullptr), system(nullptr), studioSystem(nullptr)

{
	// Create the FMOD system
	// Make sure that the system actually got created
	FMOD_RESULT result = FMOD::Studio::System::create(&studioSystem);
	FMOD_ASSERT(result);

	// Initialize FMOD
	result = studioSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
	FMOD_ASSERT(result);

	// Get the low level system to create the sound channel group called "SoundEffects"
	result = studioSystem->getLowLevelSystem(&system);
	result = system->createChannelGroup("SoundEffects", &effectsChannelGroup);
	FMOD_ASSERT(result);
}

SoundManager::~SoundManager()
{
	// Free the sound system
	studioSystem->release();
}

void SoundManager::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	// Literarily update the audio system
	studioSystem->update();
}

void SoundManager::Shutdown()
{
	// Release all the sounds in the list
	for (unsigned i = 0; i < numSounds; ++i)
	{
		soundList[i]->release();
		soundList[i] = nullptr;
	}

	// Release all of the banks in the list
	for (unsigned i = 0; i < numBanks; ++i)
	{
		bankList[i]->unload();
		soundList[i] = nullptr;
	}

	numBanks = 0;
	numSounds = 0;
}

void SoundManager::AddEffect(const std::string& fileName)
{
	AddSound(fileName, FMOD_DEFAULT);
}

void SoundManager::AddMusic(const std::string& fileName)
{
	AddSound(fileName, FMOD_DEFAULT | FMOD_LOOP_NORMAL);
}

void SoundManager::AddBank(const std::string& fileName)
{
	std::string fullFilePath = "Assets/" + audioFilePath + bankFilePath + fileName;
	// Create the bank pointer
	FMOD::Studio::Bank* newBank;
	FMOD_RESULT result = studioSystem->loadBankFile(fullFilePath.c_str(), FMOD_DEFAULT, &newBank);
	FMOD_ASSERT(result);
	// Add the bank to the list
	//	-> But first check if capped the amont of banks we can hold
	//	-> If so, then release the new bank we made and don't add it to the list
	if (numBanks >= maxNumBanks)
	{
		newBank->unload();
		return;
	}

	if(newBank)
		bankList[numBanks++] = newBank;
}

FMOD::Channel* SoundManager::PlaySound(const std::string& name_)
{
	char currentSoundName[100];
	FMOD_MODE currentMode = FMOD_DEFAULT;
	// Loop through all of the sounds and find the one we want to play
	for (unsigned i = 0; i < sizeof(soundList) / sizeof(soundList[0]); ++i)
	{
		FMOD_RESULT result = soundList[i]->getName(currentSoundName, 100);
		FMOD_ASSERT(result);
		// Check whether the strings are not equal to each other, if they are not then skip interacting with the sound
		if (strcmp(currentSoundName, name_.c_str()))
			continue;

		// If the strings are equal, then find the sound's mode
		soundList[i]->getMode(&currentMode);
		// Check if the sound we are played is being streamed
		// If so, play it as a piece of music
		if (currentMode == FMOD_CREATESTREAM)
		{
			// Play the music
			return PlayMusic(soundList[i]);
		}
		// Otherwise, play as a regular sound effect
		else
		{
			return PlayEffect(soundList[i]);
		}
	}

	// At this point, we couldn't find a channel with an equivalent sound object
	return nullptr;
}

FMOD::Studio::EventInstance* SoundManager::PlayEvent(const std::string& name_)
{
	// Create the full event name
	std::string fullEventName = eventPrefix + name_;
	FMOD::Studio::EventDescription* eventDesc = nullptr;
	FMOD::Studio::EventInstance* eventInstance = nullptr;
	// Create the event's description
	FMOD_RESULT result = studioSystem->getEvent(fullEventName.c_str(), &eventDesc);
	FMOD_ASSERT(result);
	// Create the actual event
	result = eventDesc->createInstance(&eventInstance);
	FMOD_ASSERT(result);
	// Start the instance.
	result = eventInstance->start();
	FMOD_ASSERT(result);
	eventInstance->release();
	FMOD_ASSERT(result);
	// Return the instance
	return eventInstance;
}

void SoundManager::SetMusicVolume(float volume)
{
	// Set the music volume
	musicVolume = volume;
}

void SoundManager::SetEffectsVolume(float volume)
{
	// Set the sound effects volume
	effectsVolume = volume;
}

// Accessors //
float SoundManager::GetMusicVolume() const
{
	return musicVolume;
}

float SoundManager::GetEffectsVolume() const
{
	return effectsVolume;
}

// Private Member Functions //
FMOD::Channel* SoundManager::PlayEffect(FMOD::Sound* sound) const
{
	// Create the actual FMOD channel
	FMOD::Channel* channel = nullptr;
	// Play the sound in the channel
	FMOD_RESULT result = system->playSound(sound, effectsChannelGroup, false, &channel);
	FMOD_ASSERT(result);
	// Return the channel
	return channel;
}

FMOD::Channel* SoundManager::PlayMusic(FMOD::Sound* sound)
{
	// Check that the music channel exists first
	if (musicChannel != nullptr)
	{
		// Then stop all music playing on that channel
		musicChannel->stop();
		FMOD_RESULT result = system->playSound(sound, NULL, false, &musicChannel);
		FMOD_ASSERT(result);
	}

	// Return the music channel
	return musicChannel;
}

void SoundManager::AddSound(const std::string& fileName, FMOD_MODE mode)
{
	// Create the full path to a sound file
	std::string fullPathFile = "Assets/" + audioFilePath + fileName;
	// Create the sound
	FMOD::Sound* sound = nullptr;
	FMOD_RESULT result = system->createSound(fullPathFile.c_str(), mode, nullptr, &sound);
	FMOD_ASSERT(result);
	// If we don't have any more space for sounds, then ignore this new one we created
	if (numSounds >= maxNumSounds)
	{
		result = sound->release();
		FMOD_ASSERT(result);
		return;
	}
	// Put the sound in the sound bank if it exists
	if (sound)
		soundList[numSounds++] = sound;
}