#include<windows.h>

void HandleOutput(HANDLE hPipeRead);
DWORD WINAPI RedirThread(LPVOID lpvThreadParam);

HANDLE hChildProcess=NULL;
HANDLE hStdIn=NULL;
BOOL   bRunThread=TRUE;

int main(int argc,char *argv[]){
    HANDLE hOutputReadTemp,hOutputRead,hOutputWrite;
    HANDLE hInputWriteTemp,hInputRead,hInputWrite;
    HANDLE hErrorWrite;
    HANDLE hThread;
    DWORD ThreadId;
    SECURITY_ATTRIBUTES sa;

    sa.nLength=sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor=NULL;
    sa.bInheritHandle=TRUE;

    DWORD i;
    CHAR cmd[32767];
    cmd[0]='\0';
    strcat(cmd,"app.exe");
    for(i=1;i<argc;i++){
        strcat(cmd," ");
        strcat(cmd,argv[i]);
    }

    CreatePipe(&hOutputReadTemp,&hOutputWrite,&sa,0);
    DuplicateHandle(GetCurrentProcess(),hOutputWrite,GetCurrentProcess(),&hErrorWrite,0,TRUE,DUPLICATE_SAME_ACCESS);
    CreatePipe(&hInputRead,&hInputWriteTemp,&sa,0);
    DuplicateHandle(GetCurrentProcess(),hOutputReadTemp,GetCurrentProcess(),&hOutputRead,0,FALSE,DUPLICATE_SAME_ACCESS);
    DuplicateHandle(GetCurrentProcess(),hInputWriteTemp,GetCurrentProcess(),&hInputWrite,0,FALSE,DUPLICATE_SAME_ACCESS);
    CloseHandle(hOutputReadTemp);
    CloseHandle(hInputWriteTemp);

    hStdIn=GetStdHandle(STD_INPUT_HANDLE);


    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb=sizeof(STARTUPINFO);
    si.dwFlags=STARTF_USESTDHANDLES;
    si.hStdOutput=hOutputWrite;
    si.hStdInput=hInputRead;
    si.hStdError=hErrorWrite;

    CreateProcess(NULL,cmd,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);

    hChildProcess=pi.hProcess;

    CloseHandle(pi.hThread);

    CloseHandle(hOutputWrite);
    CloseHandle(hInputRead);
    CloseHandle(hErrorWrite);

    hThread=CreateThread(NULL,0,RedirThread,(LPVOID)hInputWrite,0,&ThreadId);

    HandleOutput(hOutputRead);

    CloseHandle(hStdIn);

    bRunThread=FALSE;

    WaitForSingleObject(hThread,INFINITE);
    CloseHandle(hOutputRead);
    CloseHandle(hInputWrite);

    return 0;
}

void HandleOutput(HANDLE hPipeRead){

    CHAR lpBuffer[256];
    DWORD nRead;
    DWORD nWrote;

    while (TRUE) {

        if(!ReadFile(hPipeRead,lpBuffer,sizeof(lpBuffer),&nRead,NULL)||!nRead)
            if(GetLastError()==ERROR_BROKEN_PIPE)
                break;
        WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),lpBuffer,nRead,&nWrote,NULL);
    }
}

DWORD WINAPI RedirThread(LPVOID lpvThreadParam){
    CHAR buff[256];
    DWORD nRead,nWrote;
    HANDLE hPipeWrite=(HANDLE)lpvThreadParam;

    while(bRunThread){
        ReadConsole(hStdIn,buff,1,&nRead,NULL);

        buff[nRead]='\0';

        if(!WriteFile(hPipeWrite,buff,nRead,&nWrote,NULL)){
            if(GetLastError()==ERROR_NO_DATA)
                break;
        }
    }
    return 1;
}
