#pragma once
#include "Object/Entity/Player/Player.hpp"
#include "UI/UI.hpp"
#include "UI/String.hpp"

#include "UI/String.hpp"
#include "UI/UI.hpp"
class PlayerManager
{
public:

	PlayerManager(const PlayerManager &) = delete;
	PlayerManager &operator=(const PlayerManager &) = delete;

	/// @brief �C���X�^���X�̎擾
	/// @return �C���X�^���X�̎���
	inline static PlayerManager &GetInstance() {
		static PlayerManager instance;
		return instance;
	}
	/// <summary>
	/// + �����o�ϐ��̐ݒ�
	/// </summary>
	/// <param name="player">�o�^����v���C���[�z��</param>
	void Init();

	/// <summary>
	/// - ���͏���
	/// </summary>
	void Input();

	/// <summary>
	/// - ���t���[���̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// - �_���[�W
	/// </summary>
	void Damage();

	/// @brief - �`��
	void Draw() const;

	inline Player &GetPlayer() { return player; };
private:

	PlayerManager() { Init(); };
	~PlayerManager() {
	}
	Player player;
	bool isReturn;
};

