#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

HANDLE retrieveProcessId(char *processName) {
    HANDLE hProcess = nullptr;
    PROCESSENTRY32 entry;
    entry.dwFlags = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(Process32First(snapshot,&entry) == 1)
        while(Process32Next(snapshot,&entry) == 1)
            if(_stricmp(entry.szExeFile, processName) == 0)
                hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,entry.th32ProcessID);
    CloseHandle(snapshot);
    return hProcess;
}

int main(int argc, char *argv[]) {
    char *dllPath = _strdup(R"(C:\Users\lou\CLionProjects\dofus_test\cmake-build-debug\dofus_test.dll)");

    char* processName = _strdup("Dofus.exe");
    void* pLoadLibrary = (void*)GetProcAddress(GetModuleHandle("kernel32"),"LoadLibraryA");
    HANDLE hProcess = nullptr;
    STARTUPINFOA startupInfo;
    ZeroMemory(&startupInfo,sizeof(startupInfo));

    std::cout << "Getting process ID of process \"" << processName << "\"...\n";
    if(!(hProcess = retrieveProcessId(processName))) {
        std::cout << "Process ID unknown. GetLastError() = " << GetLastError();
        return 0;
    }

    std::cout << "Allocating virtual memory...\n";
    void* pReservedSpace = VirtualAllocEx(hProcess,nullptr,strlen(dllPath),MEM_COMMIT,PAGE_EXECUTE_READWRITE);
    if(!pReservedSpace) {
        std::cout << "Could not allocate virtual memory. GetLastError() = " << GetLastError();
        return 0;
    }

    std::cout << "Writing process memory...\n";
    if(!WriteProcessMemory(hProcess,pReservedSpace,dllPath,strlen(dllPath),nullptr)) {
        std::cout << "Error while calling WriteProcessMemory(). GetLastError() = " << GetLastError();
        return 0;
    }

    std::cout << "Creating remote thread...\n";
    HANDLE hThread = CreateRemoteThread(hProcess,nullptr,0,(LPTHREAD_START_ROUTINE)pLoadLibrary,pReservedSpace,0,nullptr);
    if(!hThread) {
        std::cout << "Unable to create the remote thread. GetLastError() = " << GetLastError();
        return 0;
    }

    std::cout << "Thread created.\n";

    WaitForSingleObject(hThread,INFINITE);
    VirtualFreeEx(hProcess,pReservedSpace,strlen(dllPath),MEM_COMMIT);
    CloseHandle(hProcess);

    std::cout << "Done.";
    return 0;
}