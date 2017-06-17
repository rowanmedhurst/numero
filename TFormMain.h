//---------------------------------------------------------------------------
#ifndef TFormMainH
#define TFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
const int LetterValues[26] = {
	1, 2, 3, 4, 5, 8, 3, 5, 1, 1, 2, 3, 4, 5, 7, 8, 1, 2, 3, 4, 6, 6, 6, 5, 1, 7
};
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:
	TEdit *EditName;
	TLabel *LabelValues;
	TLabel *Label1;
	TLabel *Label2;
	TSpeedButton *SpeedButtonSelect;
	TImage *ImageBG;
	TSpeedButton *SpeedButtonShowWorking;
	void __fastcall EditNameChange(TObject *Sender);
	void __fastcall SpeedButtonSelectClick(TObject *Sender);
	void __fastcall EditNameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall EditNameKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SpeedButtonShowWorkingClick(TObject *Sender);

private:
	int ReduceNumber(int Number, bool ForceIfMasterNumber);
	int ReduceNumberOneLevel(int Number);
	void GetNumbers(String Input, int &Compound, int &Single);
	void SelectionChangeHandler();

public:
	__fastcall TFormMain(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
