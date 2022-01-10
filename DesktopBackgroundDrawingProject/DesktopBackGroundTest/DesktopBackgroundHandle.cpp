#include "DesktopBackgroundHandle.h"
#include <tchar.h>

DesktopBackgroundHandle::DesktopBackgroundHandle():
	m_handle(NULL)
{
	FindManagementHandle();
}

DesktopBackgroundHandle::~DesktopBackgroundHandle()
{
	//The background desktop window handle is present from the beginning and will not be removed.
}

DesktopBackgroundHandle::operator HWND()
{
	return getHandle();
}

HWND DesktopBackgroundHandle::getHandle()
{
	return m_handle;
}

BOOL DesktopBackgroundHandle::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	//Find a handle with class name "SHELLDLL_DefView".
	HWND shellDll_DefViewHandle = FindWindowEx(hwnd, NULL, _T("SHELLDLL_DefView"), NULL);

	if (shellDll_DefViewHandle != NULL) {
		//If a handle is found

		HWND* pResult = (HWND*)lParam;

		//Get the parent handle of the "SHELLDLL_DefView" handle
		*pResult = hwnd;

		//processing interruption
		return FALSE;
	}

	//processing continuation
	return TRUE;
}

void DesktopBackgroundHandle::FindManagementHandle()
{
	//The handle that is one handle before the desired handle when viewed in handle order.
	HWND frontOrderHandle = NULL;

	//Find the handle in loop processing.
	EnumWindows(EnumWindowsProc, (LPARAM)&frontOrderHandle);

	//The "WorkerW" handle after the parent handle of the "SHELLDLL_DefView" handle is the handle for the desktop background.
	m_handle = FindWindowEx(NULL, frontOrderHandle, _T("WorkerW"), NULL);
}
