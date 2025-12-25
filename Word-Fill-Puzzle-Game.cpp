#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int Max=100;
string words[Max];
string hints[Max];
int totalwords=0;

void loadwords()
{
    ifstream file("words.txt");
    string w,h;
    while(file>>w)
    {
        getline(file,h);
        if(h.size()>0&&h[0]==' ')
        {
            h.erase(0,1);
        }
        words[totalwords]=w;
        hints[totalwords]=h;
        totalwords++;
        if(totalwords>=Max)
        {
            break;
        }

    }
    file.close();
}
void savescore(string name,int s,int r)
{
    ofstream file("scores.txt",ios::app);
    file<<name<<" "<<s<<"/"<<r<<endl;
}
void showscore()
{
    ifstream file("scores.txt");
    string line;
    cout<<"\n//////////////////////\n";
    cout<<"//    Past Scores     //\n";
    cout<<"////////////////////////\n";
    if(!file)
        cout<<"No Past scores found. You are the first one"<<endl;
    while(getline(file,line))
    {
        cout<<line<<endl;
    }
}
void banner()
{
        cout<<"/////////////////////////////\n";
        cout<<"//    Word Fill Puzzle     //\n";
        cout<<"//    (Five Round Game)    //\n";
        cout<<"/////////////////////////////\n";
}
string hidewords(string w)
{
    string t=w;
    for(int i=0;i<(int)w.size();i++)
    {
        if(i%2==0)
            t[i]='_';
    }
    return t;
}
void congrats_screen(int score)
{
    if(score==5)
    {
        cout<<"////////////////////////////////////////////\n";
        cout<<"//  Perfect! You crushed all five rounds  //\n";
        cout<<"////////////////////////////////////////////\n";
    }
    else if(score>=3)
    {
        cout<<"////////////////////////////////////////////\n";
        cout<<"//  Nice! Play again and score 5/5        //\n";
        cout<<"////////////////////////////////////////////\n";
    }
    else
    {
        cout<<"////////////////////////////////////////////\n";
        cout<<"//  Don't Worry you can do it. Play Again //\n";
        cout<<"////////////////////////////////////////////\n";
    }
}
void exitscreen()
{
    cout<<"///////////////////////////////////////////////////////\n";
    cout<<"//   This Game is Developed by Abdul Hameed Qaisar   //\n";
    cout<<"///////////////////////////////////////////////////////\n";
}
string tolower(string s)
{
    for(int i=0;i<(int)s.size();i++)
    {
        if(s[i]>='A'&&s[i]<='Z')
            s[i]=s[i]+32;
    }
    return s;
}

void startGame()
{
    string name;
    cout<<"///////////////////////////\n";
    cout<<"//      Starting         //\n";
    cout<<"//  Prepare Yourself!    //\n";
    cout<<"///////////////////////////\n";
    cout<<"Enter Your Name: ";
    cin.ignore();
    getline(cin,name);
    int score=0;
    int rounds=5;
    srand(time(0));

    for(int i=0;i<rounds;i++)
    {
        int idx=rand()%totalwords;
        string original=words[idx];
        string masked=hidewords(original);
        cout<<"\nRound "<<i+1<<" Of "<<rounds<<endl;
        cout<<"Word: "<<masked<<endl;
        cout<<"Hint: "<<hints[idx];
        string guess;
        cout<<"\nEnter Your Guess: ";
        cin>>guess;
        if(tolower(guess)==tolower(original))
        {
            cout<<"Correct"<<endl;
            score++;
        }
        else
            cout<<"Wrong! Correct word was "<<original;
    }
    cout<<"Your Score: "<<score<<"/"<<rounds<<endl;
    savescore(name,score,rounds);
    congrats_screen(score);

}

int main()
{
    loadwords();
    banner();
    int choice;
    do
    {
       cout<<"1. Play Game"<<endl;
       cout<<"2. View Past Scores"<<endl;
       cout<<"3. Exit Game"<<endl;
       cout<<"Enter Your Choice: ";
       if(!(cin>>choice))
       {
           cin.clear();
           cin.ignore(1000,'\n');
           cout<<"Invalid Choice!"<<endl;
           continue;
       }
       switch(choice)
       {
       case 1:
        startGame();
        break;
       case 2:
        showscore();
        break;
       case 3:
        exitscreen();
        break;
       }

    }while(choice!=3);
}
