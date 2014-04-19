/*	PLATDEF.H - Platform specific types. Portability header.
 *	Copyright (C) 2001 Rob Fahrni.  All rights reserved.
 *
 */
#ifndef _PLATDEF_H
#define _PLATDEF_H

#if defined(WIN32)
	#include <windows.h>	//	Windows API defs.
	#include <tchar.h>

	//	Portable types.
	//
	#define String		LPTSTR
	#define ConstString	LPCTSTR
	#define Char		TCHAR
	#define Int			int
	#define UInt		unsigned int
	#define Long		long
	#define Boolean		bool	//	We're assuming C++ here!
	#define DWord		DWORD
	#define Void		void

	#define True		true
	#define False		false

	//	Library defines.
	//
	#define StrCpy		_tcscpy
	#define StrNCpy		_tcsncpy
	#define StrCat		_tcscat
	#define StrLen		_tcslen
	#define StrStr		_tcsstr
	#define Sprintf		_stprintf
	#define SprintfN	_sntprintf
	#define Memset		memset

	#define ItoA	_itoa
	#define AtoL	atol

	//	Defines for string sizes.
	//
	#define BIG_BUFFER		256
	#define	MONSTER_BUFFER	2048

#elif defined(MAC)
	//	Do Mac portable types here.
	//
	//	Portable types.
	//
	typedef String	char*;
	typedef Char	char;
	typedef Int		int;
	#define UInt	unsigned int
	typedef Long	long;
	typedef Boolean	bool;	//	We're assuming C++ here!

	#define True	true
	#define False	false

	//	Library defines.
	//
	#define StrCpy		strcpy
	#define StrNCpy		strncpy
	#define StrCat		strcat
	#define StrLen		strlen
	#define Sprintf		sprintf
	#define SprintfN	snprintf
	#define Memset		memset

	#define IN
	#define OUT
#elif defined(LINUX)
	//	Do Linux/Unix types here.
	//
	//	Portable types.
	//
	typedef String	char*;
	typedef Char	char;
	typedef Int		int;
	#define UInt	unsigned int
	typedef Long	long;
	typedef Boolean	bool;	//	We're assuming C++ here!

	#define True	true
	#define False	false

	//	Library defines.
	//
	#define StrCpy		strcpy
	#define StrNCpy		strncpy
	#define StrCat		strcat
	#define StrLen		strlen
	#define Sprintf		sprintf
	#define SprintfN	snprintf
	#define Memset		memset

	#define IN
	#define OUT
#else
	//	Specify platform before building.
	//
	#error No platform specified, see PlatDef.h for platforms.
#endif
#endif	//	_PLATDEF_H