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
        TShape *backgroundShape;
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
private:	// User declarations
public:		// User declarations
        __fastcall TPingPong(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPingPong *PingPong;
//---------------------------------------------------------------------------
#endif
 