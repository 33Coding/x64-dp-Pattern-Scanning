#include <iostream>
#include <Windows.h>

using namespace std;
bool ulimitZoom = false;
bool cameraNoclip = false;
bool ulimitRun = false;
bool waterWalk = false;
bool antiSlip = false;
bool multiJump = false;
bool airSwim = false;
bool landView = false;

HANDLE  hConsole;

void CreateConsole(){
	//http://www.cplusplus.com/forum/general/140021/
	// ---------------- CONSOLE ------------------//
	AllocConsole();                               //
	SetConsoleTitle("Hack Console");			  //
	DETACHED_PROCESS;							  //
	freopen("CONOUT$", "w", stdout);              //
	// -------------------------------------------//

	//while (!GetAsyncKeyState(VK_F1))
	//{
	//	//system("cls");
	//	//std::cout.clear();
	//	std::cout << "F" << std::endl;
	//	std::cout << "O" << std::endl;
	//	std::cout << "O" << std::endl;
	//}

	//FreeConsole();



	//10 = green
	//11 = cyan
	//12 = red
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);




}

void WirteOut(char msg[])
{
	std::cout << msg << std::endl;
}



int GetInput()
{
	int choice;
	cin >> choice;
	return choice;
}

void clear_screen(char fill = ' ') {
	COORD tl = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}


void init_console_size()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	COORD NewSBSize;
	int Status;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hOut, &SBInfo);
	NewSBSize.X = SBInfo.dwSize.X;
	NewSBSize.Y = SBInfo.dwSize.Y - 275;

	Status = SetConsoleScreenBufferSize(hOut, NewSBSize);
	if (Status == 0)
	{
		Status = GetLastError();
		cout << "SetConsoleScreenBufferSize() failed! Reason : " << Status << endl;
		exit(Status);
	}

	//GetConsoleScreenBufferInfo(hOut, &SBInfo);

	//cout << "Screen Buffer Size : ";
	//cout << SBInfo.dwSize.X << " x ";
	//cout << SBInfo.dwSize.Y << endl;

}

void init_console_output()
{
	SetConsoleTextAttribute(hConsole, 10);
	
	clear_screen();
	cout << "--------------------" << endl;
	if (ulimitZoom){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Unlimited Zoom";
	cout << endl;
	cout << "--------------------" << endl;
	if (cameraNoclip){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Camera Noclip";
	cout << endl;
	cout << "--------------------" << endl;
	if (ulimitRun){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Unlimited Run";
	cout << endl;
	cout << "--------------------" << endl;
	if (waterWalk){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Walk in Water";
	cout << endl;
	cout << "--------------------" << endl;
	if (antiSlip){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Anti Slip";
	cout << endl;
	cout << "--------------------" << endl;
	if (multiJump){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Unimited Multijump";
	cout << endl;
	cout << "--------------------" << endl;
	if (airSwim){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Swim in Air";
	cout << endl;
	cout << "--------------------" << endl;
	if (landView){
		SetConsoleTextAttribute(hConsole, 11);
		cout << "[ON] ";
		SetConsoleTextAttribute(hConsole, 10);
	}
	else{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[OFF]";
		SetConsoleTextAttribute(hConsole, 10);
	}
	cout << "Allways land Viewmode";
	cout << endl;
	cout << "--------------------" << endl;
}