//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPingPong *PingPong;
//---------------------------------------------------------------------------
__fastcall TPingPong::TPingPong(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::shiftUpLeftRacketTimer(TObject *Sender)
{
    if (leftRacket->Top > 10) leftRacket->Top -= 20;        
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::shiftDownLeftRacketTimer(TObject *Sender)
{
    if (leftRacket->Top+leftRacket->Height < background->Height-10) leftRacket->Top += 20;        
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::shiftDownRightRacketTimer(TObject *Sender)
{
    if (rightRacket->Top+rightRacket->Height < background->Height-10) rightRacket->Top += 20;        
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::shiftUpRightRacketTimer(TObject *Sender)
{
    if (rightRacket->Top > 10) rightRacket->Top -= 20;        
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) shiftUpRightRacket->Enabled = true;
    if (Key == 0x41) shiftUpLeftRacket->Enabled = true;
    if (Key == VK_DOWN) shiftDownRightRacket->Enabled = true;
    if (Key == 0x5A) shiftDownLeftRacket->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) shiftUpRightRacket->Enabled = false;
    if (Key == 0x41) shiftUpLeftRacket->Enabled = false;
    if (Key == VK_DOWN) shiftDownRightRacket->Enabled = false;
    if (Key == 0x5A) shiftDownLeftRacket->Enabled = false;
}
//---------------------------------------------------------------------------

