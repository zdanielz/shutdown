#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

void SystemShutdown(UINT nSDType)
{
	HANDLE           hToken;
	TOKEN_PRIVILEGES tkp;

	::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1; // set 1 privilege
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// get the shutdown privilege for this process
	::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	switch (nSDType)
	{
	case 0: ::ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0); break;
	case 1: ::ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0); break;
	case 2: ::ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0); break;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1; // set 1 privilege
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	cout << "введите время задержки в минутах:";
	float time;
	string ans;
	cin >> time;
	cout << endl << "подтвердите выключение системы (y/n) :";
	cin >> ans;
	if (ans == "y")
	{
		cout << "отключение системы через " << time << " минут" << endl;
		Sleep((time * 1000 * 60));
		SystemShutdown(1);
	}
	else {
		return 0;
	}
}