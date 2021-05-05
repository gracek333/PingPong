//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TPingPong : public TForm
{
__published:	// IDE-managed Components
        TButton *newGameButton;
        TButton *nextRoundButton;
        TShape *background;
        TImage *ball;
        TLabel *titleLabel;
        TLabel *resultLabel;
        TLabel *amountOfPassesLabel;
        TImage *leftRacket;
        TImage *rightRacket;
        TTimer *shiftUpLeftRacket;
        TTimer *shiftDownLeftRacket;
        TTimer *moveBall;
        TTimer *shiftUpRightRacket;
        TTimer *shiftDownRightRacket;
        void __fastcall shiftUpLeftRacketTimer(TObject *Sender);
        void __fastcall shiftDownLeftRacketTimer(TObject *Sender);
        void __fastcall shiftDownRightRacketTimer(TObject *Sender);
        void __fastcall shiftUpRightRacketTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall moveBallTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPingPong(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPingPong *PingPong;
//---------------------------------------------------------------------------
#endif
 