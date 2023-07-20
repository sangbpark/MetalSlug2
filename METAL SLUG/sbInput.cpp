#include "sbInput.h"

namespace sb
{
	// vecotr에 탬플릿 허나 클래스 전역 변수여서 Input 붙이고
	// 초기화
	std::vector<Input::Key> Input::mKeys = {};

	// 아스키코드 생성
	// ASCLL[26]  END 숫자는 26 배열 크기를 확인하기 위해
	// sbInput enum에 마지막에 넣어 줌
	int ASCII[(int)eKeyCode::End/*== 26*/] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M','0','1','2','3',
		'4','5','6','7','8','9',VK_ESCAPE,VK_LEFT,
		VK_UP, VK_RIGHT,VK_DOWN
	};

	void Input::Initailize() // 위에 배열의 초기 내용을 설정 
	{
		for (size_t i = 0
			; i < (int)eKeyCode::End /*26*/
			; i++)
		{
			Key key = {}; 
			key.code = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key); // key 값을 mkeys 배열에 넣음
		}
	}

	void Input::Update()
	{
		for (size_t i = 0
			; i < (int)eKeyCode::End /*26*/
			; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000/*눌렸을때*/)
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