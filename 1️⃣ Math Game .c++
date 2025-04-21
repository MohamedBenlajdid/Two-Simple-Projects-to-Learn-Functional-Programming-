#include<iostream>
#include<string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <cmath>

using namespace std;

enum enLevelGame{Easy=1,Med=2,Hard=3,Mix=4};
enum enOperationType{Add=1,Sub=2,Mul=3,Div=4,MixOp=5};

struct stQuestion
{
    int Number1=0;
    int Number2=0;
    int PlayerAnswer ;
    int CorrectAnswer ;
    enLevelGame Level ;
    enOperationType OpType ;
    bool ResultAnswer = false ;
};

struct stQuizz
{
   stQuestion QuestionsList[100] ;
   int NumberOfQuestion ;
   int RightAnswer = 0 ;
   int WrongAnswer = 0 ;
   enLevelGame Level ;
   enOperationType OpType ;
   bool IsPass ;
};

short ReadHowManyRounds()
{
 short GameRounds = 1;
 do
 {
 cout << "How Many Rounds 1 to 10 ? \n";
 cin >> GameRounds;
 } while (GameRounds < 1 || GameRounds >10);
 return GameRounds;
}

int RandomNumber(int From, int To)
{
//Function to generate a random number
int randNum = rand() % (To - From + 1) + From;
return randNum;
}

enLevelGame ReadLevelGame()
{
    short LevelNumber=1;
    do
    {
        cout<<"What Level You Want : [1]:Easy ,[2]:Medium ,[3]:Hard ,[4]:Mix ";
        cin>>LevelNumber ;
    }while( LevelNumber < 1 || LevelNumber > 4 );
    return (enLevelGame) LevelNumber ;
}

enOperationType ReadOpType()
{
    short OpType = 1 ;
    do
    {
        cout<<"OperationType Want : [1]:Add ,[2]:Substruct ,[3]:Multiply ,[4]:Division ,[5]:Mix";
        cin>>OpType;
    }while( OpType < 1 || OpType > 5 );
    return (enOperationType) OpType ;
}

int SimpleCalculator(int Number1, int Number2, enOperationType
OpType)
{
switch (OpType)
{
case enOperationType::Add:
return Number1 + Number2;
case enOperationType::Sub:
return Number1 - Number2;
case enOperationType::Mul:
return Number1 * Number2;
case enOperationType::Div:
return Number1 / Number2;
default:
return Number1 + Number2;
}
}

enOperationType GetRandomOpType()
{
    int OpType = RandomNumber(1,4);
    return (enOperationType) OpType ;
}

stQuestion GenerateQuestion(enLevelGame Level , enOperationType OpType)
{
    stQuestion Question ;
   if(Level == enLevelGame::Mix )
   {
      Level = (enLevelGame) RandomNumber(1,3);
   }
   if( OpType == enOperationType::MixOp )
   {
     OpType = GetRandomOpType();
   }

   Question.OpType = OpType ;

   switch(Level)
   {
    case enLevelGame::Easy:
    Question.Number1=RandomNumber(1,10);
    Question.Number2=RandomNumber(1,10);

    Question.CorrectAnswer=SimpleCalculator(Question.Number1 ,
    Question.Number2 , Question.OpType );
    Question.Level = Level ;
    return Question ;
    case enLevelGame ::Med:
    Question.Number1=RandomNumber(10,50);
    Question.Number2=RandomNumber(10,50);

    Question.CorrectAnswer=SimpleCalculator(Question.Number1 ,
    Question.Number2 , Question.OpType );
    Question.Level = Level ;
    return Question ;
    case enLevelGame::Hard:
    Question.Number1=RandomNumber(50,100);
    Question.Number2=RandomNumber(50,100);

    Question.CorrectAnswer=SimpleCalculator(Question.Number1 ,
    Question.Number2 , Question.OpType );
    Question.Level = Level ;
    return Question ;
   }
   return Question ;
}

void GenerateQuizz(stQuizz& Quizz)
{
    for(short Question=0 ; Question < Quizz.NumberOfQuestion ; Question++)
    {
        Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.Level ,
        Quizz.OpType );
    }
}

int ReadPlayerAnswer()
{
    int PlayerAnswer = 0 ;
    cin>>PlayerAnswer;
    return PlayerAnswer ;
}

bool CorrectAnswerPlayer(stQuizz& Quizz , short QuestionNumber)
{
   if(Quizz.QuestionsList[QuestionNumber].PlayerAnswer ==
    Quizz.QuestionsList[QuestionNumber].CorrectAnswer)
   {
    cout<<"Correct Answer :-) ."<<endl;
    Quizz.RightAnswer ++;
    return Quizz.QuestionsList[QuestionNumber].ResultAnswer = true ;
   }
   else
   {
    cout<<"You're Wrong :-( . "<<endl;
    cout<<"The Right Answer is "<<Quizz.QuestionsList[QuestionNumber].CorrectAnswer<<endl;
    Quizz.WrongAnswer++ ;
    return Quizz.QuestionsList[QuestionNumber].ResultAnswer = false ;
   }

}

string GetOpTypeSymbol(enOperationType OpType)
{
switch (OpType)
{
case enOperationType::Add:
return "+";
case enOperationType::Sub:
return "-";
case enOperationType::Mul:
return "x";
case enOperationType::Div:
return "/";
default:
return "Mix";
}
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
cout << "\n";
cout << "Question [" << QuestionNumber + 1 << "/" <<
Quizz.NumberOfQuestion << "] \n\n";
cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";
cout <<
GetOpTypeSymbol(Quizz.QuestionsList[QuestionNumber].OpType);
cout << "\n_________" << endl;
}

bool IsPass(bool Pass)
{
    if(Pass)
    {
        cout<<"Passed ."<<endl;
        return 1;
    }
    else 
    {
        cout<<"Failed . "<<endl;
        return 0;
    }
}

bool ResultAnswer(int PlayerAnswer ,int CorrectAnswer)
{
  return ( PlayerAnswer == CorrectAnswer );
}

string GetLevelOfQuizz(enLevelGame Level)
{
   switch (Level)
{
case enLevelGame::Easy:
return "Easy";
case enLevelGame::Med:
return "Medium";
case enLevelGame::Hard:
return "Hard";
case enLevelGame::Mix:
return "Mix";
default:
return "Mix";
} 
}

void SetWinnerScreenColor(bool IsRight)
{
 switch (IsRight)
 {
 case true :
 system("color 2F"); //turn screen to Green
 break;
 case false :
 system("color 4F"); //turn screen to Red
 cout << "\a";
 break;
 }
}


void AskAndCorrectTheQuestion(stQuizz& Quizz)
{
    for(int Question=0 ; Question < Quizz.NumberOfQuestion ; Question ++)
   {
    PrintTheQuestion(Quizz,Question);
    
     Quizz.QuestionsList[Question].PlayerAnswer = ReadPlayerAnswer() ;
  
    Quizz.QuestionsList[Question].CorrectAnswer = 
    CorrectAnswerPlayer(Quizz , Question);
    SetWinnerScreenColor(Quizz.QuestionsList[Question].ResultAnswer) ;
    
   }

    Quizz.IsPass = (Quizz.RightAnswer >= Quizz.WrongAnswer );
    

}

void PrintResutQuizz(stQuizz& Quizz)
{
    cout<<"-----------------------------------------\n\n";
    cout<<"Number Of Questions : "<<Quizz.NumberOfQuestion<<endl;
    cout<<"Level Of Questions : "<<GetLevelOfQuizz(Quizz.Level)<<endl;
    cout<<"Operation Of Questions : "<<GetOpTypeSymbol(Quizz.OpType)<<endl;
    cout<<"Right Answer : "<<Quizz.RightAnswer<<endl;
    cout<<"Wrong Answer : "<<Quizz.WrongAnswer<<endl;
    cout<<"You're Pass ? "<<IsPass(Quizz.IsPass)<<endl;
}


void PlayMathGame()
{
   stQuizz Quizz ;
   Quizz.NumberOfQuestion = ReadHowManyRounds();
   Quizz.Level=ReadLevelGame();
   Quizz.OpType=ReadOpType();
   GenerateQuizz(Quizz);
   AskAndCorrectTheQuestion(Quizz);
   PrintResutQuizz(Quizz);

}



void ResetScreen()
{
system("cls");
system("color 0F");
}

void StartGame()
{

char PlayAgain = 'Y';
do
{
ResetScreen();
PlayMathGame();
cout << endl << "Do you want to play again? Y/N? ";
cin >> PlayAgain;
} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
//Seeds the random number generator in C++, called only once
srand((unsigned)time(NULL));
StartGame();
return 0;
}