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

	/// @brief インスタンスの取得
	/// @return インスタンスの実体
	inline static PlayerManager &GetInstance() {
		static PlayerManager instance;
		return instance;
	}
	/// <summary>
	/// + メンバ変数の設定
	/// </summary>
	/// <param name="player">登録するプレイヤー配列</param>
	void Init();

	/// <summary>
	/// - 入力処理
	/// </summary>
	void Input();

	/// <summary>
	/// - 毎フレームの更新
	/// </summary>
	void Update();

	/// <summary>
	/// - ダメージ
	/// </summary>
	void Damage();

	/// @brief - 描画
	void Draw() const;

	inline Player &GetPlayer() { return player; };
private:

	PlayerManager() { Init(); };
	~PlayerManager() {
	}
	Player player;
	bool isReturn;
};

