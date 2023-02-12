#pragma once
#include "Controller.hpp"

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>


#include "BaseData.hpp"

ControllerStruct Controller::controller = {};
ControllerStruct Controller::preController = {};



Controller::Controller()
{

}

void Controller::Input() {

	int x = 0, y = 0;

	if (
		XInputGetState(
			0,		// DWORD         dwUserIndex
			&Xstate) 	// XINPUT_STATE* pState

		== ERROR_SUCCESS) {
		controller.isXinput = true;
	}
	else {
		controller.isXinput = false;
	}

	if (controller.isXinput) {

		controller.leftStick.x = Clamp((float)Xstate.Gamepad.sThumbLX / 32767, -1, 1);
		controller.leftStick.y = Clamp((float)Xstate.Gamepad.sThumbLY / 32767, -1, 1);

		controller.rightStick.x = Clamp((float)Xstate.Gamepad.sThumbRX / 32767, -1, 1);
		controller.rightStick.y = Clamp((float)Xstate.Gamepad.sThumbRY / 32767, -1, 1);

		/*
		controller.leftStick.x = (Xstate.Gamepad.sThumbLX != -32768 ? Xstate.Gamepad.sThumbLX : -32767) / 32767;
		controller.leftStick.y = (Xstate.Gamepad.sThumbLY != -32768 ? Xstate.Gamepad.sThumbLY : -32767) / 32767;

		controller.rightStick.x = (Xstate.Gamepad.sThumbRX != -32768 ? Xstate.Gamepad.sThumbRX : -32767) / 32767;
		controller.rightStick.y = (Xstate.Gamepad.sThumbRY != -32768 ? Xstate.Gamepad.sThumbRY : -32767) / 32767;
		*/


		controller.L2 = Xstate.Gamepad.bLeftTrigger;
		controller.R2 = Xstate.Gamepad.bRightTrigger;

		controller.L1 = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		controller.R1 = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;


		controller.L3 = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		controller.R3 = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;


		controller.D_UP = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		controller.D_DOWN = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		controller.D_LEFT = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		controller.D_RIGHT = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;


		controller.A = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_A;
		controller.B = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_B;
		controller.X = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_X;
		controller.Y = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_Y;


		controller.Start = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		controller.Back = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	}


	else {
		Novice::GetAnalogInputLeft(0, &x, &y);
		controller.leftStick.x = Clamp((float)x / 32767, -1, 1);
		controller.leftStick.y = Clamp((float)-y / 32767, -1, 1);

		Novice::GetAnalogInputRight(0, &x, &y);
		controller.rightStick.x = Clamp((float)x / 32767, -1, 1);
		controller.rightStick.y = Clamp((float)-y / 32767, -1, 1);

		/*
		controller.leftStick.x = x != -32768 ? x : -32767;
		controller.leftStick.y = y != -32768 ? -y : 32767;

		Novice::GetAnalogInputRight(0, &x, &y);
		controller.rightStick.x = x != -32768 ? x : -32767;
		controller.rightStick.y = y != -32768 ? -y : 32767;
		*/


		controller.L2 = Novice::IsPressButton(0, kPadButton6) ? 255 : 0;
		controller.R2 = Novice::IsPressButton(0, kPadButton7) ? 255 : 0;

		controller.L1 = Novice::IsPressButton(0, kPadButton4);
		controller.R1 = Novice::IsPressButton(0, kPadButton5);


		controller.L3 = Novice::IsPressButton(0, kPadButton10);
		controller.R3 = Novice::IsPressButton(0, kPadButton11);


		controller.D_UP = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		controller.D_DOWN = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		controller.D_LEFT = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		controller.D_RIGHT = Xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;


		controller.A = Novice::IsPressButton(0, kPadButton2);
		controller.B = Novice::IsPressButton(0, kPadButton1);
		controller.X = Novice::IsPressButton(0, kPadButton3);
		controller.Y = Novice::IsPressButton(0, kPadButton0);


		controller.Start = Novice::IsPressButton(0, kPadButton9);
		controller.Back = Novice::IsPressButton(0, kPadButton8);
	}

	if (fabs(controller.leftStick.x) < 0.05f && fabs(controller.leftStick.y) < 0.05f) {
		controller.leftStick = { 0,0 };
	}

	if (fabs(controller.rightStick.x) < 0.05f && fabs(controller.rightStick.y) < 0.05f) {
		controller.rightStick = { 0,0 };
	}
}

void Controller::Update() {
	preController = controller;
	Input();
	controller.isConnect = Novice::GetNumberOfJoysticks();
	//Novice::ScreenPrintf(10, 50, "test");
}