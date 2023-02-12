#pragma once
#include <string>
#include <unordered_map>

class Audio
{
public:
	Audio();
	Audio(const std::string &file_path) :audioHandle_(0), voiceHandle_(-1), volume_(1.0f) { Load(file_path); }
	virtual ~Audio();

	void Load(const std::string &file_path);

	void Release();

	void Reset();

	void Stop();

	bool IsPlay();

	void Start(const bool &loopFlag, const float &volume);
	void StartBGM(const bool &loopFlag, const float &volume);

	void SetVolume(const float &volume);

private:

	unsigned int audioHandle_;
	int voiceHandle_ = -1;
	float volume_;

};



class AudioManager
{
public:


	AudioManager(const AudioManager &) = delete;
	AudioManager &operator=(const AudioManager &) = delete;

	/// @brief インスタンスの取得
	/// @return インスタンスの実体
	inline static AudioManager &GetInstance() {
		static AudioManager instance;
		return instance;
	}

	inline Audio *operator[](const std::string &keyName) { return audioList[keyName]; }


	void Add(const std::string &keyName, const std::string &file_path);

private:
	std::unordered_map<std::string, Audio *>audioList;

	AudioManager();
	~AudioManager();

};