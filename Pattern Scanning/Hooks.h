/*
__declspec(naked) void startFly()
{
	__asm MOV ECX, [ESI + 0x3C]
}

__declspec(naked) void stopFly()
{
	
}


/*
__asm MOV ECX, [ESI + 0x3C]
__asm MOV YaxisRegister, ESI
__asm MOV[ESI + 0x08], EDX
__asm jmp[FlyingJmpBack]





dp_x64.exe+67E222 - C6 81 90070000 01     - mov byte ptr [rcx+00000790],01

*/