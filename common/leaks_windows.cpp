#include "stdafx.h"
#ifdef LEAK_CONTROL
#ifdef _WIN32
#include <windows.h>
#include "leaks.h"
#include <stdio.h>

void DumpUnfreed()
{
	DWORD totalSize = 0;
	char buf[1024];

	if(!g_LeakList)
		return;

	ALLOC_INFO *pCurrItem = g_LeakList;
	while (pCurrItem)
	{
		sprintf(buf, "%s(%d): ADDRESS %d\t%d unfreed\n", pCurrItem->file, pCurrItem->line, (int)pCurrItem->address, pCurrItem->size);
		OutputDebugStringA(buf);
		totalSize += pCurrItem->size;
		pCurrItem = pCurrItem->pNext;
	}
	sprintf(buf, "-----------------------------------------------------------\n");
	OutputDebugStringA(buf);
	sprintf(buf, "Total Unfreed: %d bytes\n", totalSize);
	OutputDebugStringA(buf);
};
#endif
#endif