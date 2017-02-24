#pragma once
#include <Windows.h>
#include <Windowsx.h>
#include <gdiplus.h>
#include <stdlib.h>
#include <malloc.h>

#pragma comment(lib,"gdiplus.lib")

using namespace Gdiplus;

class ScreenCapture
{
public:
	void CaptureScreen();
	int PosB(int x, int y);
	int PosG(int x, int y);
	int PosR(int x, int y);

	//int GetEncoderClsid(const WCHAR * format, CLSID * pClsid);
	//void SaveCapture();
private:
	BYTE* screenData = 0;
	int width;
	int height;
};