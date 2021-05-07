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
    int previousAmountOfPasses = 0;
    int pointsOfLeftRacket = 0;
    int pointsOfRightRacket = 0;
    AnsiString whoPassedAsLast = "rightRacket";
    bool speedUpBall = false;

//---------------------------------------------------------------------------
__fastcall TPingPong::TPingPong(TComponent* Owner)
        : TForm(Owner)
{
    AnsiString welcome = "Witaj w grze PingPong.";
    AnsiString controlFirstSentence = "Lewy gracz steruje wciskaj¹c klawisze A oraz Z.";
    AnsiString controlSecondSentence = "Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.";
    AnsiString additivesFirstSentence = "Dla urozmaicenia zabawy:";
    AnsiString additivesSecondSentence = "Kiedy odbijesz pi³kê na œrodku rakietki, wówczas zmienisz jej k¹t odbicia i pi³ka przyœpieszy.";
    AnsiString additivesThirdSentence = "Im d³u¿ej odbijasz, tym pi³ka szybciej siê przemieszcza.";
    AnsiString additivesFourthSentence = "Mo¿esz dowolnie zmieniaæ pole gry.";

    ShowMessage(welcome + sLineBreak + sLineBreak + controlFirstSentence + sLineBreak +
                controlSecondSentence + sLineBreak + sLineBreak + additivesFirstSentence + sLineBreak +
                additivesSecondSentence + sLineBreak + additivesThirdSentence + sLineBreak +
                additivesFourthSentence);
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
            if (ball->Top+ball->Height/2 >= leftRacket->Top+leftRacket->Height/2 - 35 &&
                ball->Top+ball->Height/2 <= leftRacket->Top+leftRacket->Height/2 + 35)
            {
                ball->Left=leftRacket->Left+leftRacket->Width;
                if (speedUpBall)
                {
                    x =- x;
                }
                else
                {
                    x =- 2*x;
                }
                speedUpBall = true;
            }
            else
            {
                ball->Left=leftRacket->Left+leftRacket->Width;
                if (speedUpBall)
                {
                    x =- x/2;
                    speedUpBall = false;
                }
                else
                {
                    x =- x;
                }
            }
                amountOfPasses++;
                whoPassedAsLast = "leftRacket";
        }

    if (ball->Top+ball->Height/2 >= rightRacket->Top &&
        ball->Top+ball->Height/2 <= rightRacket->Top+rightRacket->Height&&
        ball->Left+ball->Width >= rightRacket->Left+8)
    {
        if (ball->Top+ball->Height/2 >= rightRacket->Top+rightRacket->Height/2 - 35 &&
        ball->Top+ball->Height/2 <= rightRacket->Top+rightRacket->Height/2 + 35)
        {
            ball->Left=rightRacket->Left-ball->Width;
            if (speedUpBall)
            {
                x =- x;
            }
            else
            {
                x =- 2*x;
            }
            speedUpBall = true;
        }
        else
        {
            ball->Left=rightRacket->Left-ball->Width;
            if (speedUpBall)
            {
                x =- x/2;
                speedUpBall = false;
            }
            else
            {
                x =- x;
            }
        }
        amountOfPasses++;
        whoPassedAsLast = "rightRacket";
    }

    if (amountOfPasses > 0 && amountOfPasses%3==0 && amountOfPasses != previousAmountOfPasses && !speedUpBall)
    {
        x = 1.5*x;
        y = 1.5*y;
        previousAmountOfPasses = amountOfPasses;
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
    if ((pointsOfLeftRacket == 0 && pointsOfRightRacket == 0) ||
    //((pointsOfLeftRacket>0||pointsOfRightRacket>0) &&
    (Application -> MessageBox("Czy na pewno chcesz zacz¹æ od nowa?","PotwierdŸ",
    MB_YESNO | MB_ICONQUESTION) == IDYES))
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
    previousAmountOfPasses = 0;
    speedUpBall = false;
    newGameButton->Visible = false;
    titleLabel->Visible = false;
    amountOfPassesLabel->Visible = false;
    nextRoundButton->Visible = false;
    resultLabel->Visible = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::nextRoundButtonClick(TObject *Sender)
{
    ball->Left = background->Width/2;
    ball->Top = background->Height/2;
    amountOfPasses = 0;
    previousAmountOfPasses = 0;
    speedUpBall = false;
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

    leftRacket->Top = background->Height/2-leftRacket->Height/2;
    rightRacket->Top = background->Height/2-rightRacket->Height/2;
    rightRacket->Left = background->Width-70-rightRacket->Width;
    titleLabel->Visible = false;
    resultLabel->Visible = false;
    amountOfPassesLabel->Visible = false;
    nextRoundButton->Visible = false;
    newGameButton->Visible = false;
    moveBall->Enabled = true;
}
//---------------------------------------------------------------------------

