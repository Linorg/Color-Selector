#include "ScreenCapture.h"
#include <tchar.h>

void ScreenCapture::CaptureScreen()
{
	// get the device context of the screen
	HDC hScreenDC = GetDC(GetDesktopWindow());

	// and a device context to put it in
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

	// set width and height
	width = GetDeviceCaps(hScreenDC, HORZRES);
	height = GetDeviceCaps(hScreenDC, VERTRES);

	// create bitmap
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

	// get a new bitmap
	HGDIOBJ hOldBitmap = SelectObject(hMemoryDC, hBitmap);

	// bit-block transfer of colors
	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

	// set bitmap
	SelectObject(hMemoryDC, hOldBitmap);

	// create BITMAPINFOHEADER struct (contains info on dimensions and color format)
	BITMAPINFOHEADER bmi = { 0 };
	// number of bytes required
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	// number of planes (must be 1)
	bmi.biPlanes = 1;
	// number of bits per pixel
	bmi.biBitCount = 32;
	// width and height of the bitmap in pixels, height is negative
	bmi.biWidth = width;
	bmi.biHeight = -height;
	// type of compression (bi_rgb is uncompressed)
	bmi.biCompression = BI_RGB;
	// size in bytes, set to 0 for bi_rgb
	bmi.biSizeImage = 0;

	if (screenData) 
		free(screenData);
	screenData = (BYTE*)malloc(4 * width * height);

	// copy bitmap bits into a buffer
	GetDIBits(hMemoryDC, hBitmap, 0, height, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	// clean up
	ReleaseDC(GetDesktopWindow(), hScreenDC);
	DeleteDC(hMemoryDC);
	DeleteObject(hBitmap);
}

int ScreenCapture::PosB(int x, int y)
{
	return screenData[4 * ((y*width) + x)];
}

int ScreenCapture::PosG(int x, int y)
{
	return screenData[4 * ((y*width) + x) + 1];
}

int ScreenCapture::PosR(int x, int y)
{
	return screenData[4 * ((y*width) + x) + 2];
}