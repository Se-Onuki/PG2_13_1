#include <Novice.h>

#include "Scene.hpp"
#include "SceneManager.hpp"

#include "Input/KeyBoard.hpp"
#include "Input/Controller.hpp"
#include "UI/String.hpp"

#include "Render/Camera.hpp"

const char kWindowTitle[] = "LC1A_05_オヌキセイヤ_評価課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, ScreenSize.x, ScreenSize.y);
	ImportTexture();

	SceneManager::GetInstance().AddScene("Title", new TitleScene_);
	SceneManager::GetInstance().AddScene("Game", new GameScene_);
	SceneManager::GetInstance().AddScene("Result", new ResultScene_);

	SceneManager::GetInstance().ChangeScene("Title");

	String::AddFont("Default", { 64,64 });

	SceneManager::GetInstance().fadeUI = Box(MiddleCentor, MiddleCentor);
	SceneManager::GetInstance().fadeUI.spriteBox.Init("", 1, 1, 1);
	SceneManager::GetInstance().fadeUI.spriteBox.color = 0xFFFFFF00;

	Camera::Update();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		Keyboard::Update();
		Mouse::Update();
		Controller::Update();

		///
		/// ↓更新処理ここから
		///


		SceneManager::GetInstance().Update();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		SceneManager::GetInstance().Draw();


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (Keyboard::IsTrigger(DIK_ESCAPE)) {
			break;
		}
	}


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
