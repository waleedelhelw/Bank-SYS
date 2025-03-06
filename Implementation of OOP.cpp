#include<iostream>
//#include"clsMainScreen.h"
#include"Screens/login screens/clsLoginScreen.h"
using namespace std;

int main()
{
	
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
	
	system("pause>0");

	
}