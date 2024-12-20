#ifndef ANIMDEMOINPUT_H
#define ANIMDEMOINPUT_H

namespace Axiom
{
	bool keyPState = false;
	bool keyOState = false;
	bool keyRState = false;
	bool keySState = false;
	bool keyHState = false;
	bool keyLState = false;
	bool keyLeftState = false;
	bool keyRightState = false;

	void AnimDemoInput()
	{
		if ((GetKeyState('P') & 0x8000) && !keyPState)
		{
			keyPState = true;

			AnimControllerNodeMan::Play();
			Trace::out("Playing animation\n");
		}
		
		if ((GetKeyState('O') & 0x8000) && !keyOState)
		{
			keyOState = true;

			AnimControllerNodeMan::Pause();
			Trace::out("Paused animation\n");
		}

		if ((GetKeyState('R') & 0x8000) && !keyRState)
		{
			keyRState = true;

			AnimControllerNodeMan::PlayRunAnim();
			Trace::out("Playing run animation\n");
		}

		if ((GetKeyState('S') & 0x8000) && !keySState)
		{
			keySState = true;

			AnimControllerNodeMan::PlaySideStepAnim();
			Trace::out("Playing side step animation\n");
		}

		if ((GetKeyState('H') & 0x8000) && !keyHState)
		{
			keyHState = true;

			AnimControllerNodeMan::PlayHitBackAnim();
			Trace::out("Playing hit back animation\n");
		}

		if ((GetKeyState('L') & 0x8000) && !keyLState)
		{
			keyLState = true;

			AnimControllerNodeMan::PlayHitLeftAnim();
			Trace::out("Playing hit left animation\n");
		}

		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			AnimControllerNodeMan::DecreaseSpeed();
			Trace::out("Decreasing animation speed\n");
		}

		if (GetKeyState(VK_UP) & 0x8000)
		{
			AnimControllerNodeMan::IncreaseSpeed();
			Trace::out("Increasing animation speed\n");
		}

		if ((GetKeyState(VK_LEFT) & 0x8000) && !keyLeftState)
		{
			keyLeftState = true;
			AnimControllerNodeMan::MoveBackward();
			Trace::out("Animate reverse\n");
		}

		if ((GetKeyState(VK_RIGHT) & 0x8000) && !keyRightState)
		{
			keyRightState = true;
			AnimControllerNodeMan::MoveForward();
			Trace::out("Animate forward\n");
		}
	}
}

#endif // ANIMDEMOINPUT_H
