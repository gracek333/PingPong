//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPingPong *PingPong;

    int x = -5;
    int y = -5;

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

void __fastcall TPingPong::moveBallTimer(TObject *Sender)
{
    ball->Left += x;
    ball->Top += y;

    if (ball->Top-5 <= background->Top) y =- y;
    if (ball->Top+ball->Height+5 >= background->Height) y =- y;

    if (ball->Top+ball->Height/2 >= leftRacket->Top &&
        ball->Top+ball->Height/2 <= leftRacket->Top+leftRacket->Height &&
        ball->Left <= leftRacket->Left+leftRacket->Width)
    {
        ball->Left=leftRacket->Left+leftRacket->Width;
        x =- x;
    }
    if (ball->Top+ball->Height/2 >= rightRacket->Top &&
        ball->Top+ball->Height/2 <= rightRacket->Top+rightRacket->Height&&
        ball->Left+ball->Width > rightRacket->Left)
    {
        ball->Left=rightRacket->Left-ball->Width;
        x =- x;
    }

    if (ball->Left >= rightRacket->Left+rightRacket->Width || ball->Left+ball->Width <= leftRacket->Left+leftRacket->Width)
    {
        moveBall->Enabled = false;
        ball->Visible = false;
    }
}
//---------------------------------------------------------------------------

