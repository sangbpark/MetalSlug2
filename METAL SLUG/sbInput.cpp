#include "sbInput.h"

namespace sb
{
	// vecotr�� ���ø� �㳪 Ŭ���� ���� �������� Input ���̰�
	// �ʱ�ȭ
	std::vector<Input::Key> Input::mKeys = {};

	// �ƽ�Ű�ڵ� ����
	// ASCLL[26]  END ���ڴ� 26 �迭 ũ�⸦ Ȯ���ϱ� ����
	// sbInput enum�� �������� �־� ��
	int ASCII[(int)eKeyCode::End/*== 26*/] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M','0','1','2','3',
		'4','5','6','7','8','9',VK_ESCAPE,VK_LEFT,
		VK_UP, VK_RIGHT,VK_DOWN
	};

	void Input::Initailize() // ���� �迭�� �ʱ� ������ ���� 
	{
		for (size_t i = 0
			; i < (int)eKeyCode::End /*26*/
			; i++)
		{
			Key key = {}; 
			key.code = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key); // key ���� mkeys �迭�� ����
		}
	}

	void Input::Update()
	{
		for (size_t i = 0
			; i < (int)eKeyCode::End /*26*/
			; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000/*��������*/)
			{
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

				mKeys[i].bPressed = true;
			}
			else
			{
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Up;
				else
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;
			}
		}
	}
}