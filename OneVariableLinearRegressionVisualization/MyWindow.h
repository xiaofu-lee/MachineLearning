#pragma once

#include "BaseWindow.h"

class MyWindow :
	public BaseWindow
{
public:
	MyWindow(HINSTANCE hInst, WCHAR* szTitle, WCHAR* szWindowClass);
	~MyWindow();
protected:
	void OnPaint(HDC hdc, PAINTSTRUCT ps);
	void OnKeyDown(WPARAM key);
	void OnKeyUp(WPARAM key);
	void ExitInstance();
};

