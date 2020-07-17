
#include <string>
#include "PatternSearch.h"
#include <windows.h>
#include <psapi.h>
#ifdef _X86_
#define SEARCHPATTERN  0x88,0x47,0x00,0x0F,0x94,0xC0,0x88,0x47,0x00
/*
mov eax,[ebp+?]
setz al
mov [ebp+?],eax
*/
#define OFFSET 3
#define PATCH 0xB0,0x01,0x90
/*
mov al,1
nop
*/

#endif 

#ifdef _M_AMD64
#define SEARCHPATTERN  0x0f,0x94,0xc1,0x88,0x4f,0x00
/*
setz cl
mov [rdi+?],cl
*/
#define OFFSET 0
#define PATCH 0xB1,0x01,0x90
/*
mov cl,1
nop
*/

#endif 

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{


	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {

		char dummy[] = { PATCH };


		PatternSearch ps{ SEARCHPATTERN };//0x00 is wildcard
		std::vector<ptr_t> ptr_t;
		HANDLE hP = GetCurrentProcess();
		HMODULE hM = GetModuleHandleA("CK2game.exe");
		MODULEINFO mod;
		GetModuleInformation(hP, hM, &mod, sizeof(mod));
		if (ps.Search(0x00, mod.lpBaseOfDll, mod.SizeOfImage, ptr_t)) {
			SIZE_T t;
			WriteProcessMemory(hP, (void*)(ptr_t[0] + OFFSET), dummy, sizeof(dummy), &t);
		}
		break;

	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

