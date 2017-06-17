//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "TFormMain.h"
#include "TFormWorking.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
:
	TForm(Owner)
{
	DoubleBuffered = true;
	EditName->DoubleBuffered = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonSelectClick(TObject *Sender)
{
	if (SpeedButtonSelect->Tag == 0)
	{
		EditName->SelStart = 0;
		EditName->SelLength = EditName->Text.Length();
		SpeedButtonSelect->Tag = 1;
	}
	else
	{
		EditName->SelStart = 0;
        EditName->SelLength = 0;
		SpeedButtonSelect->Tag = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditNameChange(TObject *Sender)
{
	int compound, single;
	GetNumbers(EditName->Text, compound, single);
	LabelValues->Caption = String(compound) + " -> " + String(single);
}
//---------------------------------------------------------------------------
int TFormMain::ReduceNumber(int Number, bool ForceIfMasterNumber)
{
	if ((Number==11 || Number==22) && (!ForceIfMasterNumber)) {
		return Number;
	}

	while (1)
	{
		Number = ReduceNumberOneLevel(Number);

		if (Number < 10) {
			break;
		}
	}
	return Number;
}
//---------------------------------------------------------------------------
int TFormMain::ReduceNumberOneLevel(int Number)
{
	String s = String(Number);
	int sum = 0;

	for (int pos = 1; pos <= s.Length(); pos++)
	{
		char c = s[pos];
		sum += c - 48;
	}
	return sum;
}
//---------------------------------------------------------------------------
void TFormMain::GetNumbers(String Input, int &Compound, int &Single)
{
	std::vector<int> PartPos;
	std::vector<int> PartLength;
	std::vector<int> PartSum;

	Input = Input.UpperCase();

	// calculate the positions and sizes of the different parts of the name

	bool inPart = false;
	int partIdx = 0;

	for (int pos = 1; pos <= Input.Length(); pos++)
	{
		char c = Input[pos];

		if ((c >= 'A' && c <= 'Z') || (c == '-') || (c == 39) || (c >= '0' && c <= '9'))
		{
			if (!inPart)
			{
				inPart = true;
				PartPos.push_back(pos);
			}
		}
		else if (c == ' ')
		{
			if (inPart)
			{
				inPart = false;
				PartLength.push_back(pos - PartPos[partIdx]);
				partIdx++;
			}
		}
	}

	if (inPart)
	{
		PartLength.push_back(Input.Length() + 1 - PartPos[partIdx]);
	}
	assert(PartPos.size() == PartLength.size());

	// calculate the number values for each part of the name

	int numParts = PartPos.size();
	PartSum.resize(numParts);

	for (int part = 0; part < numParts; part++)
	{
		int pos = PartPos[part];
		PartSum[part] = 0;

		for (int p = pos; p <= pos + PartLength[part] - 1; p++)
		{
			char c = Input[p];

			if (c >= 'A' && c <= 'Z')
			{
				PartSum[part] += LetterValues[c - 65];
			}
			else if (c >= '0' && c <= '9')  // number support
			{
				PartSum[part] += c - 48;
			}
		}
	}


	// collapse the parts down and see if we have a compound number, if not, recalculate without collapsing

	int total = 0;

	for (int part = 0; part < numParts; part++)
	{
		total += ReduceNumber(PartSum[part], false);
	}

	if (total >= 10)  // good compound number
	{
		Compound = total;
	}
	else
	{
		total = 0;

		for (int part = 0; part < numParts; part++)
		{
			total += PartSum[part];
		}
		Compound = total;
	}

	// calculate the single number

	Single = ReduceNumber(Compound, true);

	FormWorking->ShowWorking(Input, Compound, PartPos, PartSum);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonShowWorkingClick(TObject *Sender)
{
	FormWorking->Visible = !FormWorking->Visible;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// note - the code bloat expands, purple gas is eating at your flesh
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditNameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	SelectionChangeHandler();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditNameKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	SelectionChangeHandler();
}
//---------------------------------------------------------------------------
void TFormMain::SelectionChangeHandler()
{
	if (EditName->Text != EditName->SelText)
		SpeedButtonSelect->Tag = 0;
	else
		SpeedButtonSelect->Tag = 1;
}
//---------------------------------------------------------------------------

