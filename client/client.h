// client.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.

#pragma once

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

bool Initialize(void);
bool Connect(const char *pcUid, int* pnLineId);
void Disconnect(int nLineId);

bool SendTestCommand(int nLineId, char* pucData, size_t ulLength);
void TestLoop(int nLineId);
