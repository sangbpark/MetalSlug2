#pragma once
#include "Commoninclude.h"

namespace sb
{
	// enum 숫자를 글자로 결국 숫자임
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,ZERO,ONE,TWO,THREE,
		FOUR,FIVE,SIX,SEVEM,EIGHT,NINE,ESC, LEFT,
		UP, RIGHT, DOWN,
		End,
	};
	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode code;
			eKeyState state;
			bool bPressed;
		};
		static void Initailize();
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Down;
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Up;
		}
		__forceinline static bool GetKey(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Pressed;
		}


	private:
		static std::vector<Key> mKeys;
	};
}

