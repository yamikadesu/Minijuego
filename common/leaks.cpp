#include "stdafx.h"
#ifdef LEAK_CONTROL
#pragma warning (disable: 4996)
#include "leaks.h"
#include <string.h>

ALLOC_INFO *g_LeakList;

void *AddTrack(void *addr,  unsigned int asize,  const char *fname, unsigned int lnum)
{
	ASSERT(addr);

	ALLOC_INFO *info;

	info = (ALLOC_INFO *)malloc(sizeof(ALLOC_INFO));
	info->address = addr;
	strncpy(info->file, fname, _MAX_PATH-1);
	info->line = lnum;
	info->size = asize;
	info->pNext = g_LeakList;
	g_LeakList = info;

	return addr;
};

void RemoveTrack(void *addr)
{
	ALLOC_INFO *pLastItem = 0;
	ALLOC_INFO *pCurrItem = g_LeakList;
	while (pCurrItem)
	{
		if(pCurrItem->address == addr)
		{
			if (pLastItem)
				pLastItem->pNext = pCurrItem->pNext;
			else
				g_LeakList = pCurrItem->pNext;
			free (pCurrItem);
			break;
		}else
		{
			pLastItem = pCurrItem;
			pCurrItem = pCurrItem->pNext;
		}
	}
};
#endif

