#ifndef ___LEAKS___
#define ___LEAKS___

#pragma warning (disable: 4100)
#include <stdlib.h>

#ifdef LEAK_CONTROL

	struct ALLOC_INFO 
	{
			void *				address;
			unsigned int	size;
			char					file[_MAX_PATH];
			unsigned int	line;
			ALLOC_INFO *	pNext;
	};

	void  RemoveTrack(void *p);
	void *AddTrack		(void *p,  unsigned int asize,  const char *fname, unsigned int lnum);
	void  DumpUnfreed();

	#define NEW(clase, params)			reinterpret_cast<clase *>(AddTrack(new clase params, sizeof(clase), __FILE__, __LINE__))
	#define DEL(p)								{ RemoveTrack(p); delete p; }
	#define NEW_ARRAY(clase, num)	  reinterpret_cast<clase *>(AddTrack(new clase[num], sizeof(clase) * num, __FILE__, __LINE__))
	#define DEL_ARRAY(p)					{ RemoveTrack(p); delete []p; }

	#define DUMP_LEAKS DumpUnfreed();

	extern ALLOC_INFO *g_LeakList;
#else
	#define NEW(clase, params)			new clase params
	#define DEL(p)								  delete p
	#define NEW_ARRAY(clase, num)		new clase[num]
	#define DEL_ARRAY(p)				    delete []p

	#define DUMP_LEAKS
#endif

#endif