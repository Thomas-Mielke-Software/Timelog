#include "stdafx.h"
#include "resource.h"

// statics:
static char szBuffer[80]; // print buffer for EnumResourceTypes  
static DWORD cbWritten;   // number of bytes written to res. info. file 
static int cbString;      // length of string in sprintf 

// Prototypen:
// Declare callback functions. 
static int __stdcall EnumTypesFunc( 
	HANDLE hModule, 
	LPTSTR lpType, 
	LONG lParam); 

static int __stdcall EnumNamesFunc( 
	HANDLE hModule, 
	LPCTSTR lpType, 
	LPTSTR lpName, 
	LONG lParam); 

static int __stdcall EnumLangsFunc( 
	HANDLE hModule, 
	LPCTSTR lpType, 
	LPCTSTR lpName, 
	WORD wLang, 
	LONG lParam); 


void GetProgramVersion(HMODULE hExe, VS_FIXEDFILEINFO *vs)
{
	if (hExe != NULL)
	{
		EnumResourceTypes(hExe,              // module handle 
			(ENUMRESTYPEPROC)EnumTypesFunc,  // callback function 
			(LONG)vs);                       // extra parameter 
	}

}
 

// --- die callbacks -----

//    FUNCTION: EnumTypesFunc(HANDLE, LPSTR, LONG) 
// 
//    PURPOSE:  Resource type callback 
 
static int __stdcall EnumTypesFunc( 
    HANDLE hModule,   // module handle 
    LPTSTR lpType,    // address of resource type 
    LONG lParam)      // extra parameter, could be 
                      // used for error checking 
{ 
	BOOL bFound = FALSE;
 
    // Write the resource type to a resource information file. 
    // The type may be a string or an unsigned decimal 
    // integer, so test before printing. 
 
    if ((ULONG)lpType & 0xFFFF0000) 
	{ 
		if (!strcmp(lpType, "RT_VERSION")) bFound = TRUE;
    } 
    else 
	{ 
 		if ((USHORT)lpType == (USHORT)RT_VERSION) bFound = TRUE;
    } 
 
	if (bFound)
	{
		// Find the names of all resources of type lpType. 
		EnumResourceNames((HINSTANCE) hModule, 
			lpType, 
			(ENUMRESNAMEPROC)EnumNamesFunc, 
			lParam); 
	    return FALSE; // stop!
	}
	
    return TRUE; 
} 
 
//    FUNCTION: EnumNamesFunc(HANDLE, LPSTR, LPSTR, LONG) 
// 
//    PURPOSE:  Resource name callback 
 
static int __stdcall EnumNamesFunc( 
    HANDLE hModule,   // module handle 
    LPCTSTR lpType,   // address of resource type 
    LPTSTR lpName,    // address of resource name 
    LONG lParam)      // extra parameter, could be 
                      // used for error checking 
{ 
	BOOL bFound = FALSE;
 
     // Write the resource name to a resource information file. 
     // The name may be a string or an unsigned decimal 
     // integer, so test before printing. 
 
    if ((ULONG)lpName & 0xFFFF0000) 
	{ 
		if (!strcmp(lpName, "VS_VERSION_INFO")) bFound = TRUE;
    } 
    else 
	{ 
  		if ((USHORT)lpName == VS_VERSION_INFO) bFound = TRUE;
    } 
 
 
     // Find the the 1st languages of resources of type 
     // lpType and name lpName. 
 
	if (bFound)
	{
		EnumResourceLanguages((HINSTANCE) hModule, 
			lpType, 
			lpName, 
			(ENUMRESLANGPROC)EnumLangsFunc, 
			lParam); 
		return FALSE; 
	}
	
    return TRUE; 
} 
 
//    FUNCTION: EnumLangsFunc(HANDLE, LPSTR, LPSTR, WORD, LONG) 
// 
//    PURPOSE:  Resource language callback 
 
static int __stdcall EnumLangsFunc( 
    HANDLE hModule,  // module handle 
    LPCTSTR lpType,  // address of resource type 
    LPCTSTR lpName,  // address of resource name 
    WORD wLang,      // resource language 
    LONG lParam)     // extra parameter, could be 
{ 
    HANDLE hResInfo; 
 
    hResInfo = FindResourceEx((HINSTANCE)hModule, lpType, lpName, wLang); 
	
	if (hResInfo)
	{
		HGLOBAL hGlobal = LoadResource((HINSTANCE)hModule, (HRSRC)hResInfo);
		if (hGlobal)
		{
			WORD *p = (WORD *)LockResource(hGlobal);
			if (p)
			{
				// wLength
				// Specifies the length of the VS_VERSION_INFO structure. 
				// This length does not include any padding that aligns the 
				// subsequent version structure on a 32-bit boundary. 
				p++;
				
				// wValueLength
				// Specifies the length of the Value member. This value is zero 
				// if there is no Value member associated with the current version 
				// structure. 
				ASSERT(*p == sizeof(VS_FIXEDFILEINFO));
				p++;

				// bText
				// Specifies the type of data in the version resource. This member 
				// is 1 if the version resource contains text data and 0 if the 
				// version resource contains binary data. 
				ASSERT(*p == 0);
				p++;
				
				// szKey
				// Contains "VS_VERSION_INFO". 
				p += strlen("VS_VERSION_INFO");	// wide chars!

				// Padding1
				// Contains as many zero bytes as necessary to align the Value 
				// member on the _next_ 32-bit boundary. 
				p += 2 - (((DWORD)p & 0x0003) >> 1/*da WORD*/);
							
				memcpy((VS_FIXEDFILEINFO *)lParam, (VS_FIXEDFILEINFO *)p, sizeof(VS_FIXEDFILEINFO));
				return FALSE;	// stop!
			}
		}
	}
	
	return TRUE; // weiter!
} 











