#include "PlatDef.h"
#include "WinPlatDef.h"

#include "CZPing.h"

#include <stdio.h>
#include <WinINet.h>

#include <string>			//	stl string support.

//	String constants.
//
#define STR_HelpFlag		"-h\0"
#define STR_SiteNameFlag	"-s\0"
#define STR_SiteURLFlag		"-u\0"
#define STR_SiteToPingFlag	"-p\0"

#define LEN_HelpFlag		2
#define LEN_SiteNameFlag	2
#define LEN_SiteURLFlag		2
#define LEN_SiteToPingFlag	2

//#define SKIP_THE_PING_PART 1
#ifndef SKIP_THE_PING_PART
	#define PingSite(stp, lstp, sn, lsn, url, lurl, eb, leb)	WeblogsDotComPing(stp, lstp, sn, lsn, url, lurl, eb, leb)
#else
	#define PingSite(stp, lstp, sn, lsn, url, lurl, eb, leb)	// moot, test mode.
#endif	//	SKIP_THE_PING_PART

static void displayBanner(void)
	{
	printf("-----------------------------------------------------\n");
	printf(" CheezyPing, version 0.25\n");
	printf(" Copyright 2001-2003 Rob Fahrni, all rights reserved.\n");
	printf(" http://rob.crabapples.net/\n");
	printf("-----------------------------------------------------\n\n");
	}	//	displayBanner

static void displayUsage(void)
	{
	printf("+ Usage: czp -s\"My Site Name\" -u\"http://www.myurl.xyz\" -p\"http://rpc.weblogs.com/RPC2\"\n");
	printf("\tWhere...\n");
	printf("\t-s == REQUIRED: Text name for site. NOT the URL\n");
	printf("\t-u == REQUIRED: URL for the site\n");
	printf("\t-p == OPTIONAL: Site to ping, defaults to %s\n", SITE_WeblogsDotCom);
	}	//	displayUsage

static void displaySiteInfo(
	IN String SiteName,
	IN String SiteURL,
	IN String SiteToPing)
	{
	//	Tell the user what we're doing.
	//
	printf("Updating...\n");
	printf("\tSite Name: %s\n", SiteName);
	printf("\tSite URL: %s\n", SiteURL);
	printf("\tSite to Ping: %s\n", SiteToPing);
	}	//	displaySiteInfo

static void copyAndStrip(
	IN		UInt	FlagLen,
	IN		String	Source,
	IN		UInt	SourceLen,
	IN OUT	String	Target,
	IN		UInt	TargetLen)
	{
	if ((FlagLen > 0) &&
		(Source != NULL && SourceLen > 0) &&
		(Target != NULL && TargetLen > 0))
		{
		UInt CopySize = (SourceLen - FlagLen);
		if (CopySize < TargetLen)
			{
			Memset(Target, 0, TargetLen);
			StrNCpy(Target, &Source[FlagLen], CopySize);
			}
		}
	}	//	copyAndStrip

#define IS_FLAG(s, f, l)	StrStr(s, f) != NULL && StrLen(s) <= l
static Boolean parseArgs(
	IN		String*	Arguments,
	IN		Int		NumArgs,
	IN OUT	String	SiteToPing, 
	IN		UInt	SiteToPingLen,
	IN OUT	String	SiteName, 
	IN		UInt	SiteNameLen,
	IN OUT	String	SiteURL,
	IN		UInt	SiteURLLen)
	{
	Boolean Ok(False);

	if (NumArgs > 0 && SiteName != NULL && SiteURL != NULL)
		{
		//	Clean up the args we received, set SiteToPing to the default value.
		//
		Memset(SiteName, 0, SiteNameLen);
		Memset(SiteURL, 0, SiteURLLen);
		Memset(SiteToPing, 0, SiteToPingLen);

		if (SiteToPing != NULL)
			{
			//	Pre-load the SiteToPing with weblogs.com.
			//
			StrCpy(SiteToPing, SITE_WeblogsDotCom);
			}

		for (int x(NumArgs/*-1*/); 
			 x >= 0; 
			 x--)
			{
			//	Look for one of our flags in the string.
			//
			if (Arguments[x] != NULL)
				{
				if (IS_FLAG(Arguments[x], STR_SiteNameFlag, SiteNameLen))
					{
					copyAndStrip(LEN_SiteNameFlag,
								Arguments[x], StrLen(Arguments[x]),
								SiteName, SiteNameLen);
					}
				else if (IS_FLAG(Arguments[x], STR_SiteURLFlag, SiteURLLen))
					{
					copyAndStrip(LEN_SiteURLFlag,
								Arguments[x], StrLen(Arguments[x]),
								SiteURL, SiteURLLen);
					}
				else if (IS_FLAG(Arguments[x], STR_SiteToPingFlag, SiteToPingLen))
					{
					copyAndStrip(LEN_SiteToPingFlag,
								Arguments[x], StrLen(Arguments[x]),
								SiteToPing, SiteToPingLen);
					}
				}
			}
		}

	return Ok;
	}

#define STR_SpaceReplacement	"%20\0"
#define STR_Space				" \0"

static Boolean fixupSpacesInSiteURL(
	IN OUT	String	SiteURL,
	IN		Int		SiteURLLen)
	{
	Boolean fOk(False);
	
	//	Make sure we should continue.
	//
	if (SiteURL != NULL && SiteURLLen > 0)
		{
		Boolean fDoCopy(False);
		
		//	I'm coping out and using an STL string here. It's so much nicer to use
		//	when you need to do replacements on a buffer.
		//
		std::string replaceBuff(SiteURL);
		int loc(std::string::npos);
		while ((loc = replaceBuff.find(STR_Space)) != std::string::npos)
			{
			//	Replace on character at offset loc with STR_SpaceReplacement.
			//	This changes the space character to the "%20".
			//
			replaceBuff.replace(loc, 1, STR_SpaceReplacement);
			
			//	Yes this assignment is happening over and over, but we've got
			//	to do it somewhere. Right?
			//
			fDoCopy = True;
			}
		
		//	Now that replacement has taken place jam it back into the
		//	SiteURL string, IF IT'S LARGE ENOUGH!
		//
		if (replaceBuff.size() < SiteURLLen && fDoCopy == True)
			{
			//	Cram it back in, otherwise we're returning the same string
			//	we got and it may be goofy.
			//
			StrNCpy(SiteURL, replaceBuff.c_str(), replaceBuff.size());
			}
		}

	return fOk;
	}	//	fixupSpacesInSiteURL

static Boolean wantsHelp(
	IN String*	Arguments,
	IN Int		NumArgs)
	{
	Boolean needHelp(False);

	for (int x(NumArgs-1); 
		 x > 0 && needHelp == False; 
		 x--)
		{
		//	Look for -h in the string.
		//
		if (Arguments[x] != NULL &&
			StrStr(Arguments[x], STR_HelpFlag) != NULL)
			{
			//	We've found the -h (Help) flag, time to bail.
			//
			needHelp = True;
			}
		}

	return needHelp;
	}

void main(
	IN Int		NumArgs,	//	Number of args.
	IN String*	Arguments)	//	Args array.
	{
	displayBanner();
	
	if (NumArgs < 2 || wantsHelp(Arguments, NumArgs) == True)
		{
		displayUsage();
		}
	else
		{
		Char SiteToPing[MAX_PATH];
		Char SiteName[MAX_PATH];
		Char SiteURL[MAX_PATH];

		//	Get the arguments
		//
		parseArgs(Arguments, NumArgs, 
				  SiteToPing, MAX_PATH, 
				  SiteName, MAX_PATH,
				  SiteURL, MAX_PATH);

		//	If all the arguments seem to be filled in properly then we
		//	can get on with pinging the site, otherwise show the
		//	help.
		//
		if (SiteName[0] != NULL && 
			SiteURL[0] != NULL && 
			SiteToPing[0] != NULL)
			{
			//	Display some information to the user about what's going on here!
			//
			displaySiteInfo(SiteName, SiteURL, SiteToPing);

			//	Fixup the path to the .HTM file if there's a space in the name
			//
			fixupSpacesInSiteURL(SiteURL, MAX_PATH);

			//	PingSite can return us a result if we give it a buffer
			//	to work with.
			//
			//	We're realy calling WeblogsDotComPing, PinSite is a macro
			//	wrapped around it so we can test this code without actually
			//	doing a ping.
			//
			Char	ResultBuffer[MONSTER_BUFFER];
			Long	ResultBufferLen(MONSTER_BUFFER);
			
			//	Finally get around to pinging the site.
			//
			PingSite(SiteToPing, StrLen(SiteToPing), 
					 SiteName, StrLen(SiteName), 
					 SiteURL, StrLen(SiteURL), 
					 ResultBuffer, &ResultBufferLen);

			//	Regardless of the error we inform the user of our result string.
			//	It could be an error code.
			//
			printf(ResultBuffer);
			}
		else
			{
			displayUsage();
			}
		}
	}	//	main
