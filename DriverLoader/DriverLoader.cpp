// DriverLoader.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>

WCHAR serviceName[] = L"TestDriver";
WCHAR path[] = L"C:\\driver\\TestDriver.sys";
using namespace std;
int main()
{
	
	SC_HANDLE hScm;
	SC_HANDLE hService;
	SERVICE_STATUS svcStatus;
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwBytesNeeded;

	hScm =OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hScm)
	{
		printf("Can not open Service Control manager! \n");//서비스제어 관리자는 시스템 부팅시 시작되며 서비스 구성 및 서비스 제어 프로그램이 원격 컴퓨터에 조작할 수 있도록 하는것
		return 0;
	}
	hService = OpenService(hScm, serviceName, SERVICE_ALL_ACCESS);
	if (!hService)
	{
		cout << "Does not exist Service!\n";
		
	}
	else {
		
		if (!ControlService(hService, SERVICE_CONTROL_STOP, &svcStatus))
		{
			cout << "Failed Control Service\n";
		}
		if (!DeleteService(hService))
		{

			cout << "Failed DeleteService!\n";
		}
	}

	
	hService = CreateService(hScm, serviceName, serviceName, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,path, NULL, NULL, NULL, NULL, NULL);
	if (!hService)
	{
		cout << "Dont Create Service!\n"<<GetLastError();
	}

	hService = OpenService(hScm, serviceName, SERVICE_ALL_ACCESS);
	if (!hService)
	{
		cout << "Dont Open Service!\n";
		return 0;
	}

	if (!StartService(hService, 0, NULL))
	{

		cout << "Can not Start Service\n";
		return 0;
	}
	cout << "success!";

}

