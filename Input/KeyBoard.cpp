#include "KeyBoard.hpp"

#include "./Render/Resource.hpp"


char Keyboard::keys[256] = {  };
char Keyboard::preKeys[256] = {  };

IntVector2 Mouse::mouse = {  }, Mouse::preMouse = Mouse::mouse;

void Mouse::Update() {
	preMouse = mouse;
	Novice::GetMousePosition(&mouse.x, &mouse.y);
	mouse = GetMouse();
}


Keyboard::Keyboard()
{
}


Mouse::Mouse()
{
}