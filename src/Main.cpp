#include <Windows.h>
#include "Texture.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Texture PRESENT_TEXTURE;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	LPCSTR CLASS_NAME = "Sample Window Class";
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND l_winodw = CreateWindowEx(0, CLASS_NAME, "Learn to Program Windows", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (l_winodw == NULL)
	{
		return 0;
	}

	ShowWindow(l_winodw, nCmdShow);

	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);


		{
			BITMAP structBitmapHeader;
			memset(&structBitmapHeader, 0, sizeof(BITMAP));

			HGDIOBJ hBitmap = GetCurrentObject(hdc, OBJ_BITMAP);
			GetObject(hBitmap, sizeof(BITMAP), &structBitmapHeader);

			if (structBitmapHeader.bmWidth != PRESENT_TEXTURE.WIDTH || structBitmapHeader.bmHeight != PRESENT_TEXTURE.HEIGHT)
			{
				Texture_free(&PRESENT_TEXTURE);
				Texture_alloc(&PRESENT_TEXTURE, structBitmapHeader.bmWidth, structBitmapHeader.bmHeight);
				Vector3f l_color = { 255, 0, 0 };
				Texture_fill(&PRESENT_TEXTURE, &l_color);

				for (int i = 1000; i < 40000; i++)
				{
					PRESENT_TEXTURE.Pixels[i] = { 0, 255, 0 };
				}
				for (int i = 40000; i < 60000; i++)
				{
					PRESENT_TEXTURE.Pixels[i] = { 0, 255, 255 };
				}
			}
		}

		HDC l_map_hdc = CreateCompatibleDC(hdc);
		HBITMAP l_map = CreateCompatibleBitmap(hdc, PRESENT_TEXTURE.WIDTH, PRESENT_TEXTURE.HEIGHT);
		SelectObject(l_map_hdc, l_map);


		{
			BITMAP structBitmapHeader;
			memset(&structBitmapHeader, 0, sizeof(BITMAP));

			HGDIOBJ hBitmap = GetCurrentObject(l_map_hdc, OBJ_BITMAP);
			GetObject(hBitmap, sizeof(BITMAP), &structBitmapHeader);
			int zd = 0;
		}

		//Set bitmap header
		{
			BITMAPINFOHEADER bmih;
			bmih.biSize = sizeof(BITMAPINFOHEADER);
			bmih.biBitCount = 8 * sizeof(Vector3f);
			bmih.biClrImportant = 0;
			bmih.biClrUsed = 0;
			bmih.biCompression = BI_RGB;
			bmih.biHeight = -PRESENT_TEXTURE.HEIGHT;
			bmih.biWidth = PRESENT_TEXTURE.WIDTH;
			bmih.biPlanes = 1;
			bmih.biSizeImage = Texture_getByteSize(&PRESENT_TEXTURE);
			bmih.biXPelsPerMeter = 0;
			bmih.biYPelsPerMeter = 0;
			
			BITMAPINFO bmpInfo;
			bmpInfo.bmiHeader = bmih;
			bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);

			// SetDIBitsToDevice(l_map_hdc, )

			if (!SetDIBits(l_map_hdc,
				l_map,
				0,
				PRESENT_TEXTURE.HEIGHT,
				PRESENT_TEXTURE.Pixels,
				&bmpInfo,
				DIB_RGB_COLORS))
			{
				int zd = 0;
			};
		}


		{
			if (!BitBlt(hdc, 0, 0, PRESENT_TEXTURE.WIDTH, PRESENT_TEXTURE.HEIGHT, l_map_hdc, 0, 0, SRCCOPY))
			{
				int zd = 0;
			};
		}



		DeleteDC(l_map_hdc);
		DeleteObject(l_map);




		// memcpy(structBitmapHeader.bmBits, PRESENT_TEXTURE.Pixels, sizeof(Vector3f) * (PRESENT_TEXTURE.WIDTH * PRESENT_TEXTURE.HEIGHT));

		// structBitmapHeader.bmBitsPixel

		// All painting occurs here, between BeginPaint and EndPaint.

		// FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};