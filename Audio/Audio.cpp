#include "Audio/Audio.hpp"

#include <Novice.h>

Audio::Audio() :audioHandle_(0), voiceHandle_(-1), volume_(1.0f)
{
}

Audio::~Audio()
{
}

void Audio::Load(const std::string &file_path)
{
	audioHandle_ = Novice::LoadAudio(file_path.c_str());
}

void Audio::Release()
{
	//	audioHandle = Novice::LoadAudio
}

void Audio::Reset()
{
	//	audioHandle_ = Novice::Audi

}

void Audio::Stop()
{
	Novice::StopAudio(voiceHandle_);
}

bool Audio::IsPlay() {
	return (Novice::IsPlayingAudio(voiceHandle_) && voiceHandle_ != -1);
}

void Audio::Start(const bool &loopFlag, const float &volume)
{
	SetVolume(volume);
	voiceHandle_ = Novice::PlayAudio(audioHandle_, loopFlag, volume_);
}

void Audio::StartBGM(const bool &loopFlag, const float &volume)
{
	if (!IsPlay()) {
		Start(loopFlag, volume);
	}
}

void Audio::SetVolume(const float &volume)
{
	volume_ = volume;
}


AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {
	for (auto &element : audioList) {
		if (element.second) {
			delete element.second;
		}
	}
	audioList.clear();
}

void AudioManager::Add(const std::string &keyName, const std::string &file_path) {
	audioList[keyName] = new Audio(file_path);
}
