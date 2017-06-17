//---------------------------------------------------------------------------
#ifndef TFormWorkingH
#define TFormWorkingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <vector>
using std::vector;
//---------------------------------------------------------------------------
class TFormWorking : public TForm
{
__published:
	TStatusBar *StatusBar1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;

private:
	String SetStrInStr(String Main, String Adding, int Pos);

public:
	__fastcall TFormWorking(TComponent* Owner);
	void ShowWorking(String Name, int Compound, const vector<int> &PartPos, const vector<int> &PartSum);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormWorking *FormWorking;
//---------------------------------------------------------------------------
#endif
