#pragma once

#include <Windows.h>

class DesktopBackgroundHandle {
public:
	DesktopBackgroundHandle();
	~DesktopBackgroundHandle();

	/// <summary>
	/// Implicit cast to HWN
	/// Return the value of "getHandle()"
	/// </summary>
	operator HWND();

	/// <summary>
	/// Get the handle of the background desktop window
	/// </summary>
	/// <returns></returns>
	HWND getHandle();

private:
	/// <summary>
	/// Callback functions for "EnumWindows"
	/// </summary>
	/// <param name="hwnd"></param>
	/// <param name="lParam">The value specified by the lParam argument of "EnumWindows"</param>
	/// <returns>TRUE:To continue processing, FALSE:To suspend processing</returns>
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	/// <summary>
	/// Find the handle of the background desktop window
	/// </summary>
	/// <returns></returns>
	void FindManagementHandle();

private:
	//This handle is for the background of the desktop window
	HWND m_handle;
};