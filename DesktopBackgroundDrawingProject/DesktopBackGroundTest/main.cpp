//必要なライブラリを読み込むVC++コンパイラへの命令
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib,"winmm.lib")

#include <time.h>
#include <random>
#include <iostream>
#include "DesktopBackgroundHandle.h"
#include "FPSManager.h"
#include "Timer.h"


int main(int argc, char* argv[]) {

	FPSManager fpsManager(60,2);
	Timer oneSecondTimer;

	std::cout << "start application" << std::endl;

	srand(time(NULL));

	DesktopBackgroundHandle handle;

	HDC dc = GetDCEx(handle, NULL, 0x403);

	int curr = rand();

	float th0 = 0.01f;
	float th1 = 0.0337f;
	float th2 = 0.00732f;
	float th3 = 0.02231f;
	float th4 = 0.013f;
	float th5 = 0.0354f;
	float th6 = 0.02544f;

	SetProcessDPIAware();

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	COLORREF bg_color = RGB(0, 0, 0);
	HBRUSH bg_brush = CreateSolidBrush(bg_color);
	HPEN bg_pen = CreatePen(PS_SOLID, 2, bg_color);

	SelectObject(dc, bg_brush);
	SelectObject(dc, bg_pen);

	Rectangle(dc, 0, 0, screen_width, screen_height);

	fpsManager.init();
	oneSecondTimer.start();

	while (true) {

		int x0 = (int)(screen_width / 2 * (1 + sin(curr * th0)));
		int x1 = (int)(screen_width / 2 * (1 + cos(curr * th1)));

		int y0 = (int)(screen_height / 2 * (1 + sin(curr * th2)));
		int y1 = (int)(screen_height / 2 * (1 + cos(curr * th3)));

		COLORREF color = RGB((int)(128 * (1 + sin(curr * th4))),
			(int)(128 * (1 + sin(curr * th5))),
			(int)(128 * (1 + sin(curr * th6))));


		HPEN pen = CreatePen(PS_SOLID, 2, color);
		SelectObject(dc, pen);

		MoveToEx(dc, x0, y0, NULL);
		LineTo(dc, x1, y1);

		curr++;

		if ((curr & ((1 << 10) - 1)) == 0) {
			SelectObject(dc, bg_brush);
			SelectObject(dc, bg_pen);
			Rectangle(dc, 0, 0, screen_width, screen_height);
		}
		DeleteObject(pen);
		
		oneSecondTimer.update();
		if (oneSecondTimer.isTimeOverSecond(1)) {
			//system("cls");
			std::cout << "FPS:" << fpsManager.getRealFPS() << std::endl;
			oneSecondTimer.reset();
			//oneSecondTimer.start();
		}

		fpsManager.update();
	}
	DeleteObject(bg_brush);
	DeleteObject(bg_pen);

	//最後にデバイスコンテキストを破棄する
	ReleaseDC(handle, dc);

	return 0;
}
