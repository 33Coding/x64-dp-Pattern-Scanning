#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <thread>
#include <string>
#include <fstream>
#include "Functions.h"

#include "Hooks.h"
#include "ConsoleFuncs.h"
#include "PatternFind.h"



char GameExe[] = "dp_x64.exe";


uintptr_t bhopAddy;
char bhopHackOp[] = "\x90\x90";//Cheat OpCode
char bhopOrigOp[] = "\xEB\x0F";//Original OpCode
char bhopSig[] = "\xEB\x0F\xC6\x05\xBD\x38\xD5\x01\x01\x44\x8B\xAC\x24\x80\x00\x00\x00\x48\x8B\xCD";//Signature
char bhopPat[] = "xxxxxxxxxxxxxxxxxxxx";//Pattern

uintptr_t mjmpAddy;
char mjmpHackOp[] = "\xC6\x86\x9E\xED\x02\x00\x00";//Cheat OpCode
char mjmpOrigOp[] = "\xC6\x86\x9E\xED\x02\x00\x01";//Original OpCode
char mjmpSig[] = "\xC6\x86\x9E\xED\x02\x00\x01\xC6\x86\x9D\xED\x02\x00\x00\xC6\x84\x24\x90\x02\x00\x00\x01\x80\x8E\xE8\xED\x02\x00\x08\x80\x8E\xEB\xED\x02\x00\x10\x89\x9E\xA0\xED\x02\x00\x41\x0F\x28\xCD";//Signature
char mjmpPat[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";//Pattern

uintptr_t limitAddy;
char limitHackOp[] = "\x90\x90\x90\x90\x90";//Cheat OpCode
byte limitOrigOp[5];//Original OpCode
char limitSig[] = "\xE8\x00\x00\x00\x00\x41\x0F\x2F\xC3\x76\x09\xC6";//Signature
char limitPat[] = "x???xxxxxxxx";//Pattern

uintptr_t czoomAddy;
char czoomHackOp[] = "\xEB\x08";//Cheat OpCode
byte czoomOrigOp[] = "\x76\x08";//Original OpCode
char czoomSig[] = "\x76\x08\xF3\x0F\x11\x89\xFF\xFF\x00\x00\xF3\xC3";//Signature
char czoomPat[] = "xxxxxx??xxxx";//Pattern

uintptr_t cnoclipAddy;
char cnoclipHackOp[] = "\xEB\x49";//Cheat OpCode
byte cnoclipOrigOp[] = "\x74\x49";//Original OpCode
char cnoclipSig[] = "\x74\x49\xF3\x0F\x10\x94\x24\xFF\xFF\x00\x00\xF3\x41\x0F\x5C\xD0\xF3\x0F\x10\x8C\x24\xFF\xFF\x00\x00\xF3\x0F\x5C\xCF\xF3\x0F\x10\x84\x24\xFF\xFF\x00\x00\xF3\x0F\x5C\xC6\xF3\x0F\x59\xC0\xF3\x0F\x59\xC9\xF3\x0F\x58\xC1\xF3\x0F\x59\xD2\xF3\x0F\x58\xC2";//Signature
char cnoclipPat[] = "xxxxxxx??xxxxxxxxxxxx??xxxxxxxxxxx??xxxxxxxxxxxxxxxxxxxxxxxxxx";//Pattern

uintptr_t runAddy;
char runHackOp[] = "\xEB\x07";//Cheat OpCode
byte runOrigOp[] = "\x7F\x07";//Original OpCode
char runSig[] = "\x7F\x07\x44\x88\xAF\xFF\xFF\x00\x00\x44\x89\x2D\xFF\xFF\xFF\xFF\xEB\x77\x85\xC0\x7E\x30";//Signature
char runPat[] = "xxxxx??xxxxx????xxxxxx";//Pattern

uintptr_t run2Addy;
char run2HackOp[] = "\xEB\x07";//Cheat OpCode
byte run2OrigOp[] = "\x74\x07";//Original OpCode
char run2Sig[] = "\x74\x07\xC6\x83\xFF\xFF\xFF\xFF\x00\xF6\x45\x00\x20\x74\x07\xC6\x83\xFF\xFF\xFF\x00\x00\x48\x8B\x8B\xFF\xFF\x00\x00\xE8\xFF\xFF\xFF\xFF\x84\xC0\x74\x1C";//Signature
char run2Pat[] = "xxxx????xxxxxxxxx???xxxxx??xxx????xxxx";//Pattern

uintptr_t wwalkAddy;
char wwalkHackOp[] = "\x90\x90";//Cheat OpCode
byte wwalkOrigOp[] = "\x75\x0B";//Original OpCode
char wwalkSig[] = "\x75\x0B\x44\x8B\xF3\xF3\x0F\x10\xFF\xFF\xFF\xFF\xFF\xF3\x44\x0F\x10\xFF\xFF\xFF\xFF\xFF\x8B\x05\xFF\xFF\xFF\xFF\x85\xC0\x75\xFF\x41";//Signature
char wwalkPat[] = "xxxxxxxx?????xxxx?????xx????xxx?x";//Pattern

uintptr_t slipAddy;
char slipHackOp[] = "\xE9\x49\x02\x00\x00\x90";//Cheat OpCode
byte slipOrigOp[] = "\x0F\x86\x48\x02\x00\x00";//Original OpCode
char slipSig[] = "\x0F\x86\xFF\xFF\x00\x00\x89\xB3\xFF\xFF\x00\x00\xE9\xFF\xFF\x00\x00\xF3\x0F\x10\xBB\xFF\x00\x00\x00\xF3\x44\x0F\x10\x8B\xFF\x00\x00\x00\xF3\x44\x0F\x10\x93\xFF\x00\x00\x00\x39\xB3\xFF\xFF\x00\x00";//Signature
char slipPat[] = "xx??xxxx??xxx??xxxxxx?xxxxxxxx?xxxxxxxx?xxxxx??xx";//Pattern


//SwimInAir
//E8 ? ? ? ? 44 8B E0 44 8B F3 41 0F 28 D5 48 8B D5 48 8B CE E8 ? ? ? ? 48 8B ? ? 48 8B CD FF 52 ?
//pre to   (like mjump)
//BB 02 00 00 00
uintptr_t swimAddy;
char swimHackOp[] = "\x45\x85\xF6\xBB\x02\x00\x00\x00\x90";//Cheat OpCode
byte swimOrigOp[9];//Original OpCode
char swimSig[] = "\x45\x85\xF6\x0F\x84\xFF\xFF\xFF\xFF\x48\x8B\x0D\xFF\xFF\xFF\xFF\xE8\xFF\xFF\xFF\xFF\x84\xC0\x0F\x84\xFF\xFF\xFF\xFF";//Signature
char swimPat[] = "xxxxx????xxx????x????xxxx????";//Pattern

//Allways land view
//		41 83 FE 02 0F 94 C2 39
//from  41 83 FE 02 0F 9F
//to	41 83 FE 02 0F 94
uintptr_t landVAddy;
char landVHackOp[] = "\x41\x83\xFE\x02\x0F\x9F";//Cheat OpCode
byte landVOrigOp[] = "\x41\x83\xFE\x02\x0F\x94";//Original OpCode
char landVSig[] = "\x41\x83\xFE\x02\x0F\x94\xC2\x39";//Signature
char landVPat[] = "xxxxxxxx";//Pattern

int key1 = 97;	//VK_NUMPAD1
int key2 = 98;	//VK_NUMPAD2
int key3 = 99;	//VK_NUMPAD3
int key4 = 100;	//VK_NUMPAD4
int key5 = 101;	//VK_NUMPAD5
int key6 = 102; //VK_NUMPAD6
int key7 = 103; //VK_NUMPAD7
int key8 = 104; //VK_NUMPAD8



bool locked = true;

void ScannAll()
{
	


	//TODO: Include Checking here
	//bhopAddy = FindPattern(GameExe, bhopSig, bhopPat);//test-hack
	mjmpAddy = FindPattern(GameExe, mjmpSig, mjmpPat);
	limitAddy = FindPattern(GameExe, limitSig, limitPat);
	byte* limitSrc = reinterpret_cast<byte*>(limitAddy);
	memcpy((LPVOID)limitOrigOp, limitSrc, 5);

	//Public Hacks
	czoomAddy = FindPattern(GameExe, czoomSig, czoomPat);
	cnoclipAddy = FindPattern(GameExe, cnoclipSig, cnoclipPat);
	runAddy = FindPattern(GameExe, runSig, runPat);
	run2Addy = FindPattern(GameExe, run2Sig, run2Pat);
	wwalkAddy = FindPattern(GameExe, wwalkSig, wwalkPat);
	slipAddy = FindPattern(GameExe, slipSig, slipPat);

	//Paid, LandSwim
	swimAddy = FindPattern(GameExe, swimSig, swimPat);
	byte* swimSrc = reinterpret_cast<byte*>(swimAddy);
	memcpy((LPVOID)swimOrigOp, swimSrc, 9);

	landVAddy = FindPattern(GameExe, landVSig, landVPat);

}





void scanKeyConfig()
{
	ifstream inFile;

	inFile.open("key.cfg");

	if (!inFile.fail())
	{
		string item;
		string prefix("#");

		int count = 1;

		while (!inFile.eof()){
			if (getline(inFile, item)){
				if (item.compare(0, prefix.size(), prefix)){
					char key[5];
					switch (count)
					{
					case 1:
						strcpy_s(key, item.c_str());
						key1 = strtol(key, NULL, 16);
						break;
					case 2:
						strcpy_s(key, item.c_str());
						key2 = strtol(key, NULL, 16);
						break;
					case 3:
						strcpy_s(key, item.c_str());
						key3 = strtol(key, NULL, 16);
						break;
					case 4:
						strcpy_s(key, item.c_str());
						key4 = strtol(key, NULL, 16);
						break;
					case 5:
						strcpy_s(key, item.c_str());
						key5 = strtol(key, NULL, 16);
						break;
					case 6:
						strcpy_s(key, item.c_str());
						key6 = strtol(key, NULL, 16);
						break;
					case 7:
						strcpy_s(key, item.c_str());
						key7 = strtol(key, NULL, 16);
						break;
					case 8:
						strcpy_s(key, item.c_str());
						key8 = strtol(key, NULL, 16);
						break;
					default:
						break;
					}
					count++;
				}
			}
		}
	}
}



void InitiateHooks()
{

	CreateConsole();
	//init_console_size();
	cout << "loading..." << endl;
	ScannAll();
	scanKeyConfig();

	//MsgBoxAddy(0xFFFFFFFF);
	//-------Bunnyhop

	//ammoAddy += 0; //offset, if needed

	//MsgBoxAddy(ammoAddy);

	bool bhop = false;


	bool num1 = false;//Unimited zoom
	bool num2 = false;//Camera Noclip
	bool num3 = false;//Unlimited Run
	bool num4 = false;//Water walk
	bool num5 = false;//Anti Slip
	bool num6 = false;//Unimited Multijump
	bool num7 = false;//Swim in Air
	bool num8 = false;//Allways land view mode

	init_console_output();
	cout << endl;
	SetConsoleTextAttribute(hConsole, 12);

	bool error = false;
	if (czoomAddy == 0xDEADBEEF){
		cout << "ERROR: Unimited Zoom" << endl;
		error = true;
	}
	if (cnoclipAddy == 0xDEADBEEF){
		cout << "ERROR: Camera Noclip" << endl;
		error = true;
	}
	if (run2Addy == 0xDEADBEEF || runAddy == 0xDEADBEEF){
		cout << "ERROR: Unimited Run" << endl;
		error = true;
	}
	if (wwalkAddy == 0xDEADBEEF){
		cout << "ERROR: Walk in Water" << endl;
		error = true;
	}
	if (slipAddy == 0xDEADBEEF){
		cout << "ERROR: Anti Slip" << endl;
		error = true;
	}
	if (limitAddy == 0xDEADBEEF || mjmpAddy == 0xDEADBEEF){
		cout << "ERROR: Unimited Multijump" << endl;
		error = true;
	}
	if (swimAddy == 0xDEADBEEF){
		cout << "ERROR: Swim in Air" << endl;
		error = true;
	}
	if (landVAddy == 0xDEADBEEF){
		cout << "ERROR: Allways land view" << endl;
		error = true;
	}



	
	for (;; Sleep(10))
	{
		
		
		if (GetAsyncKeyState(key1) && czoomAddy != 0xDEADBEEF && !locked)
		{
			num1 = !num1;
			ulimitZoom = num1;
			init_console_output();
			if (num1){
				WriteToMemmory(czoomAddy, czoomHackOp, 2);
			}
			else
			{
				WriteToMemmory(czoomAddy, czoomOrigOp, 2);
			}


			while (GetAsyncKeyState(key1)){}

		}
		else if (GetAsyncKeyState(key2) && cnoclipAddy != 0xDEADBEEF && !locked)
		{
			num2 = !num2;
			cameraNoclip = num2;
			init_console_output();
			if (num2){
				WriteToMemmory(cnoclipAddy, cnoclipHackOp, 2);
			}
			else
			{
				WriteToMemmory(cnoclipAddy, cnoclipOrigOp, 2);
			}


			while (GetAsyncKeyState(key2)){}

		}
		else if (GetAsyncKeyState(key3) && (run2Addy != 0xDEADBEEF || runAddy != 0xDEADBEEF) && !locked)
		{
			num3 = !num3;
			ulimitRun = num3;
			init_console_output();
			if (num3){
				WriteToMemmory(runAddy, runHackOp, 2);
				WriteToMemmory(run2Addy, run2HackOp, 2);
			}
			else
			{
				WriteToMemmory(runAddy, runOrigOp, 2);
				WriteToMemmory(run2Addy, run2OrigOp, 2);
			}

			while (GetAsyncKeyState(key3)){}

		}
		else if (GetAsyncKeyState(key4) && wwalkAddy != 0xDEADBEEF && !locked)
		{
			num4 = !num4;
			waterWalk = num4;
			init_console_output();
			if (num4){
				WriteToMemmory(wwalkAddy, wwalkHackOp, 2);
			}
			else
			{
				WriteToMemmory(wwalkAddy, wwalkOrigOp, 2);
			}

			while (GetAsyncKeyState(key4)){}

		}
		else if (GetAsyncKeyState(key5) && slipAddy != 0xDEADBEEF && !locked)
		{
			num5 = !num5;
			antiSlip = num5;
			init_console_output();
			if (num5){
				WriteToMemmory(slipAddy, slipHackOp, 6);
			}
			else
			{
				WriteToMemmory(slipAddy, slipOrigOp, 6);
			}

			while (GetAsyncKeyState(key5)){}

		}
		else if (GetAsyncKeyState(key6) && (limitAddy != 0xDEADBEEF || mjmpAddy != 0xDEADBEEF) && !locked)
		{

			num6 = !num6;
			multiJump = num6;
			init_console_output();
			if (num6){
				WriteToMemmory(mjmpAddy, mjmpHackOp, 7);
				WriteToMemmory(limitAddy, limitHackOp, 5);
			}
			else
			{
				WriteToMemmory(mjmpAddy, mjmpOrigOp, 7);
				WriteToMemmory(limitAddy, limitOrigOp, 5);
			}

			while (GetAsyncKeyState(key6)){}
		}
		else if (GetAsyncKeyState(key7) && swimAddy != 0xDEADBEEF && !locked)
		{
			num7 = !num7;
			airSwim = num7;
			init_console_output();
			if (num7){
				WriteToMemmory(swimAddy, swimHackOp, 9);
			}
			else
			{
				WriteToMemmory(swimAddy, swimOrigOp, 9);
			}

			while (GetAsyncKeyState(key7)){}
		}
		else if (GetAsyncKeyState(key8) && landVAddy != 0xDEADBEEF && !locked)
		{
			num8 = !num8;
			landView = num8;
			init_console_output();
			if (num8){
				WriteToMemmory(landVAddy, landVHackOp, 6);
			}
			else
			{
				WriteToMemmory(landVAddy, landVOrigOp, 6);
			}

			while (GetAsyncKeyState(key8)){}
		}
		else if (GetAsyncKeyState(VK_RCONTROL))
		{
			locked = !locked;

			while (GetAsyncKeyState(VK_RCONTROL)) {}
		}




	}





}





DWORD WINAPI Main_Thread(LPVOID lpParam)
{
	InitiateHooks();
	return S_OK;
}







//BOOL WINAPI DllMain(
//	HINSTANCE hinstDLL,
//	DWORD fdwReason,
//	LPVOID lpReserved
//	)
//{
//
//	
//	switch (fdwReason)
//	{		
//	case DLL_PROCESS_ATTACH:
//		//MsgBoxAddy(0xFFFFFFFF);
//		InitiateHooks();
//		//InitiateHooks();
//		break;
//	default:
//		//MsgBoxAddy(0x00000000);
//		break;
//
//	}
//}


BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD _reason,
	LPVOID lpReserved){

	if (_reason == DLL_PROCESS_ATTACH){
		CreateThread(0, 0x1000, &Main_Thread, 0, 0, NULL);
		/*std::thread t1(InitiateHooks);
		t1.detach();*/
		//InitiateHooks();
	}
	return true;









}