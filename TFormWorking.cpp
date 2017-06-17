//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TFormWorking.h"
#include "TFormMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWorking *FormWorking;
//---------------------------------------------------------------------------
__fastcall TFormWorking::TFormWorking(TComponent* Owner)
:
	TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormWorking::ShowWorking(String Name, int Compound, const vector<int> &PartPos, const vector<int> &PartSum)
{
	Label1->Caption = Name;
	String cap2;

	for (int i = 1; i <= Name.Length(); i++)
	{
		char c = Name[i];

		if (c >= 'A' && c <= 'Z')
		{
			cap2 += LetterValues[c - 65];
		}
		else if (c >= '0' && c <= '9')
		{
			cap2 += String(c - 48);
		}
		else
		{
			cap2 += c;
		}
	}
	Label2->Caption = cap2;

	//----
	String cap3;

	for (DWORD i = 0; i < PartSum.size(); i++)
	{
		cap3 = SetStrInStr(cap3, String(PartSum[i]), PartPos[i]);
	}
	Label3->Caption = cap3;

	//----
	Label4->Caption = Compound;
}
//---------------------------------------------------------------------------
String TFormWorking::SetStrInStr(String Main, String Adding, int Pos)
{
	int newMinimumLength = Pos + Adding.Length() - 1;

	if (newMinimumLength > Main.Length())
	{
		Main += String::StringOfChar(' ', newMinimumLength - Main.Length());
	}
	for (int i = 1; i <= Adding.Length(); i++)
	{
		Main[Pos+i-1] = Adding[i];
	}
	return Main;
}
//---------------------------------------------------------------------------

