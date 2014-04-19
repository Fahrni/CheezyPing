/*	WINPLATDEF.H - One line description.
 *	Copyright (C) 2001 Rob Fahrni.  All rights reserved.
 *
 */
#ifndef _WINPLATDEF_H
#define _WINPLATDEF_H

#define	RELEASEIP(ip)	if (ip != NULL) { ip->Release(); ip = NULL; }
#define FREEBSTR(bs)	::SysFreeString(bs); bs = NULL;

#endif	//	_WINPLATDEF_H

