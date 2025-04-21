#include<iostream>
#include<string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <cmath>
using namespace std;

enum enChoice{ Stone=1 , Paper=2 , Scissers=3 };
enum enWinner{ Player=1 , Computer=2 , Draw=3 };


struct stRoundInfo
{
  short RoundNumber=0;
  enChoice PlayerChoice;
  enChoice ComputerChoice;
  enWinner RoundWinner;
  string WinnerName;

};

struct stGameResult
{
  short TotaleRound=0;
  short PlayerWinnerTime=0;
  short ComputerWinnerTime=0;
  short DrawTime=0;
  enWinner WinnerGame;
  string WinnerName="";
};

int RandomNumber(int From , int To )
{
    int RandomeNumber= rand() % ( To-From+1 ) + From ;
    return RandomeNumber;
}

string WinnerName(enWinner Winner)
{
  string WinnerName[3]={"Player","Computer","Draw"};
  return WinnerName[Winner-1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
  if(RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
  {
    return enWinner::Draw;
  }
  switch (RoundInfo.PlayerChoice)
  {
  case enChoice::Stone:
    if(RoundInfo.ComputerChoice==Paper)
    {
      return enWinner::Computer;
    }
    break;
   case enChoice::Paper:
    if(RoundInfo.ComputerChoice==Scissers)
    {
      return enWinner::Computer;
    }
    break;
    case enChoice::Scissers:
    if(RoundInfo.ComputerChoice==Stone)
    {
      return enWinner::Computer;
    }
    break;
  }
  return enWinner::Player;
}

enChoice ReadPlayerChoice()
{
 short PlayerChoice=0;
 do
 {
  cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
  cin>>PlayerChoice;
 }while(PlayerChoice <1 || PlayerChoice >3);
 return (enChoice)PlayerChoice;
}

enChoice GetComputerChoice()
{
  short ComputerChoice = RandomNumber(1,3);
  return (enChoice)ComputerChoice;
}

short ReadRoundNumber()
{
  short RoundNumber=0;
  do
  {
    cout<<"How many Round Want To Play (1 To 10 )"<<endl;
    cin>>RoundNumber;
  }while( RoundNumber < 1 || RoundNumber > 10 );
  return RoundNumber;
}

string ChoiceName(enChoice Choice)
{
  string Choices[3]={"Stone","Paper","Scissers"};
  return Choices[Choice-1];
}

void SetScreenColorWinner(enWinner Winner)
{
  switch (Winner)
  {
  case enWinner::Player:
    system("color 2F");
    break;
  case enWinner::Computer:
    system("color 4F");
    cout<<"\a";
    break; 
  default:
    system("color 6F");
    break;
  }
}

void DisplayRoundInformation(stRoundInfo RoundInfo)
{
  cout<<"\n ________Round ["<<RoundInfo.RoundNumber<<"]_______________";
  cout<<"\n PlayerChoice = "<<
     ChoiceName(RoundInfo.PlayerChoice);
  cout<<"\n ComputerChoice = "<<
     ChoiceName(RoundInfo.ComputerChoice);
  cout<<"\n The Winner = "<<
        RoundInfo.WinnerName;
  cout<<"\n\n --------------------------------------------"<<endl;
  SetScreenColorWinner(RoundInfo.RoundWinner);
}

enWinner WhoWonTheGame(short PlayerWinningTimes ,short ComputerWinningTimes )
{
  if(PlayerWinningTimes > ComputerWinningTimes )
  {
    return enWinner::Player;
  }
  else if(ComputerWinningTimes > PlayerWinningTimes)
  {
    return enWinner::Computer;
  }
  else return enWinner::Draw;
}

stGameResult FillGameResult(short RoundNumber, short PlayerWinnigTimes ,
     short ComputerWinningTimes ,short DrawTimes)
     {
      stGameResult GameResult;
      GameResult.TotaleRound=RoundNumber;
      GameResult.PlayerWinnerTime=PlayerWinnigTimes;
      GameResult.ComputerWinnerTime=ComputerWinningTimes;
      GameResult.DrawTime=DrawTimes;
      GameResult.WinnerGame=WhoWonTheGame(PlayerWinnigTimes,ComputerWinningTimes);
      GameResult.WinnerName=WinnerName(GameResult.WinnerGame);
      return GameResult;
     }

stGameResult PlayGame(short HowManyGame)
{
  stRoundInfo RoundInfo;
 short PlayerWinningTime=0 , ComputerWinningTime=0 , DrawTimes=0;
 for(short GameRound=1 ; GameRound <= HowManyGame ; GameRound++ )
 {
  cout<<"\n_________Round["<<GameRound<<"] Bigen __________________";
  RoundInfo.RoundNumber=GameRound;
  RoundInfo.PlayerChoice=ReadPlayerChoice();
  RoundInfo.ComputerChoice=GetComputerChoice();
  RoundInfo.RoundWinner=WhoWonTheRound(RoundInfo);
  RoundInfo.WinnerName=WinnerName(RoundInfo.RoundWinner);


  if(RoundInfo.RoundWinner == enWinner::Player)
  {
    PlayerWinningTime++;
  }
  else  if(RoundInfo.RoundWinner == enWinner::Computer)
  {
    ComputerWinningTime++;
  }
  else 
  DrawTimes++;

  DisplayRoundInformation(RoundInfo);
 }
 
 return FillGameResult(RoundInfo.RoundNumber, PlayerWinningTime ,
   ComputerWinningTime , DrawTimes);

}

string Tabs(short NumberOfTabs)
{
  string t="";
  for(int i=1 ; i <= NumberOfTabs ; i++)
  {
    t = t+"\t" ;
    cout<< t ;
  }
  return t ;
}

void ShowGameOverScreen()
{
cout << Tabs(2) <<
"__________________________________________________________\n\n";
cout << Tabs(2) << " +++ G a m e O v e r +++\n";
cout << Tabs(2) <<
"__________________________________________________________\n\n";
}

void ShowFinalGameResult(stGameResult GameResult)
{
  cout<<Tabs(2)<<"________________ [GAME RESUlTS] ____________________\n\n";
  cout<<Tabs(2)<<"Round Played : "<<GameResult.TotaleRound<<endl;
  cout<<Tabs(2)<<"Player Winning Times : "<<GameResult.PlayerWinnerTime<<endl;
  cout<<Tabs(2)<<"Computer Winnig Times : "<<GameResult.ComputerWinnerTime<<endl;
  cout<<Tabs(2)<<"Draw Times  : "<<GameResult.DrawTime<<endl;
  cout<<Tabs(2)<<"The Winner : "<<GameResult.WinnerName<<endl;
  cout<<Tabs(2)<<"____________________________________________________\n\n";
  SetScreenColorWinner(GameResult.WinnerGame);
}

void ResetScreen()
{
system("cls");
system("color 0F");
}

void StartGame()
{
  char PlayAgain='Y';
  do
  {
    ResetScreen();
    stGameResult GameResult = PlayGame(ReadRoundNumber());
    ShowGameOverScreen();
    ShowFinalGameResult(GameResult);
    cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
    cin >> PlayAgain;
  }while( PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{


//Seeds the random number generator in C++, called only once
srand((unsigned)time(NULL));
StartGame();
return 0;

}
