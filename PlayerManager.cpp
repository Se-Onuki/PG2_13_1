#include "PlayerManager.hpp"

#include<math.h>
#include<cmath>

#include "Input/Controller.hpp"
#include "Easing.hpp"

#include "Render/Camera.hpp"

void PlayerManager::Init()
{
	player = Player{ MiddleCentor,{ 24, 24 },1 };

	player.facing = { 1,0 };


	player.GetSpriteBox().Init("./Resources/Texture/TestTexture/Circle.png", 32, 32, 1);

	player.GetSpriteBox().color = 0xFFFFFFFF;

	player.SetHP(1.f);
}

void PlayerManager::Input() {
	player.Input();
}
void PlayerManager::Update() {
	player.Update();
}

void PlayerManager::Damage() {
	Camera::Shake({ 16,16 }, 4);
}


void PlayerManager::Draw() const
{
	player.Draw();
}

