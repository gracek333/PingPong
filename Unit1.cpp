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
    int amountOfPasses = 0;
    int pointsOfLeftRacket = 0;
    int pointsOfRightRacket = 0;
    AnsiString whoPassedAsLast = "rightRacket";

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
        ball->Left <= leftRacket->Left+leftRacket->Width-8)
    {
        ball->Left=leftRacket->Left+leftRacket->Width;
        x =- x;
        amountOfPasses++;
        whoPassedAsLast = "leftRacket";
    }
    if (ball->Top+ball->Height/2 >= rightRacket->Top &&
        ball->Top+ball->Height/2 <= rightRacket->Top+rightRacket->Height&&
        ball->Left+ball->Width >= rightRacket->Left+8)
    {
        ball->Left=rightRacket->Left-ball->Width;
        x =- x;
        amountOfPasses++;
        whoPassedAsLast = "rightRacket";
    }

    if (ball->Left >= rightRacket->Left+rightRacket->Width || ball->Left+ball->Width <= leftRacket->Left+leftRacket->Width)
    {
        moveBall->Enabled = false;
        ball->Visible = false;
        
        if (whoPassedAsLast == "leftRacket")
        {
            titleLabel->Caption = "< Punkt dla gracza";
            pointsOfLeftRacket++;
        }
        else
        {
            titleLabel->Caption = "Punkt dla gracza >";
            pointsOfRightRacket++;
        }
        titleLabel->Left = background->Width/2-titleLabel->Width/2;
        titleLabel->Visible = true;

        resultLabel->Left = background->Width/2-resultLabel->Width/2;
        resultLabel->Caption = IntToStr(pointsOfLeftRacket)+":"+IntToStr(pointsOfRightRacket);
        resultLabel->Visible = true;

        amountOfPassesLabel->Left = background->Width/2-amountOfPassesLabel->Width/2;
        amountOfPassesLabel->Caption = "Iloœæ odbiæ: " + IntToStr(amountOfPasses);
        amountOfPassesLabel->Visible = true;

        nextRoundButton->Left = background->Width/2-nextRoundButton->Width/2;
        nextRoundButton->Visible = true;

        newGameButton->Left = background->Width/2-newGameButton->Width/2;
        newGameButton->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::newGameButtonClick(TObject *Sender)
{
    ball->Left = background->Width/2;
    ball->Top = background->Height/2;

    leftRacket->Top = background->Height/2-leftRacket->Height/2;
    rightRacket->Top = background->Height/2-rightRacket->Height/2;
    rightRacket->Left = background->Width-70-rightRacket->Width;

    ball->Visible = true;
    moveBall->Enabled = true;
    x = -5; y = -5;
    amountOfPasses = 0;
    newGameButton->Visible = false;
    titleLabel->Visible = false;
    amountOfPassesLabel->Visible = false;
    nextRoundButton->Visible = false;
    resultLabel->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::nextRoundButtonClick(TObject *Sender)
{
    ball->Left = background->Width/2;
    ball->Top = background->Height/2;
    amountOfPasses = 0;
    ball->Visible =  true;
    if (whoPassedAsLast == "leftRacket")
    {
        x = -5; y = -5;
        whoPassedAsLast = "rightRacket";
    }
    else
    {
        x = 5; y = 5;
        whoPassedAsLast = "leftRacket";
    }

    titleLabel->Visible = false;
    resultLabel->Visible = false;
    amountOfPassesLabel->Visible = false;
    nextRoundButton->Visible = false;
    newGameButton->Visible = false;
    moveBall->Enabled = true;
}
//---------------------------------------------------------------------------

