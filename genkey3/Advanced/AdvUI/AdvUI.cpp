// AdvUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "V2_Editions.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char	DvcID[33];
	unsigned int	uiAdvncd;
	unsigned int	uiStndrd;
	printf_s("Please enter the last 8 letters from the Device ID : ");
	scanf_s("%9s", DvcID, (unsigned)9);
	uiAdvncd = SviFF_Edition::cV2_Editions::Advanced(DvcID, 8);
	uiStndrd = SviFF_Edition::cV2_Editions::Standard(DvcID, 8);

	printf_s("Advanced Key Value: 0x%8X \n", uiAdvncd);
	printf_s("Standard Key Value: 0x%8X \n", uiStndrd);
	scanf_s("%s", DvcID, 8);
	return 0;
}

