#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

void writeFile(vector<string> &myWord)
{
    ifstream myFile("data.txt");
    if(myFile.is_open()){
        string word;
        while(myFile>>word){
            myWord.push_back(word);
        }
    }
}

int checkWin(vector<string> player,vector<string> bot)
{
    string wordWin[8][3]={{"AS","FAT","PAN"},{"SPIT","AS","SO"},{"IF","IN","SPIT"},{"FOP","FAT","IF"},
                            {"SPIT","FAT","NOT"},{"PAN","NOT","IN"},{"SO","NOT","FOP"},{"PAN","FOP","SPIT"}};
    if(player.size()>=3){
        int win=0;
        for(int i=0;i<8;i++){
            win=0;
            for(int j=0;j<player.size();j++){
                if(player[j]==wordWin[i][0] || player[j]==wordWin[i][1] || player[j]==wordWin[i][2]){
                  win++;
                  if(win>=3){
                    return 10;
                  }
                }
            }
        }
    }
    if(bot.size()>=3){
        int win=0;
        for(int i=0;i<8;i++){
            win=0;
            for(int j=0;j<bot.size();j++){
                if(bot[j]==wordWin[i][0] || bot[j]==wordWin[i][1] || bot[j]==wordWin[i][2]){
                  win++;
                  if(win>=3){
                    return -10;
                  }
                }
            }
        }
    }
    if(player.size()+bot.size()>8) return 1;
    return 0;
}

void show(vector<string> myWord,vector<string> player,vector<string> bot)
{
    cout<<"\t----- SPIT NOT SO -----\n"<<endl;
    for(int i=0;i<myWord.size();i++){
        cout<<myWord[i]<<" ";
    }
     cout<<"\n"<<endl;
     cout<<"BOT\t:\t";
    for(int i=0;i<bot.size();i++){
        cout<<bot[i]<<" ";
    }
     cout<<"\n"<<endl;
     cout<<"PLAYER\t:\t";
    for(int i=0;i<player.size();i++){
        cout<<player[i]<<" ";
    }
     cout<<"\n"<<endl;

}

int miniMax(vector<string> myWord,vector<string> player,vector<string> bot,int type,int level)
{
    int maxValue,minValue;
    int winner=checkWin(player,bot);
    if(winner == -10)
        return level+winner;
    else if (winner == 10)
        return winner-level;
    if(type==-10){
        string word="x";
        minValue = 1000;
        for(int i=0;i<myWord.size();i++){
            string wordPup=myWord[i];
            bot.push_back(myWord[i]);
            myWord.erase(myWord.begin()+i);
            int value=miniMax(myWord,player,bot,10,level+1);
            if(minValue>=value){
                minValue=value;
                word=wordPup;
            }
            level-1;
            myWord.insert(myWord.begin()+i,wordPup);
            bot.pop_back();
        }
        if(word=="x") return 0;
        return minValue;
    }
    else if(type==10){
        string word="x";
        maxValue = -1000;
        for(int i=0;i<myWord.size();i++){
            string wordPup=myWord[i];
            player.push_back(myWord[i]);
            myWord.erase(myWord.begin()+i);
            int value=miniMax(myWord,player,bot,-10,level+1);
            if(maxValue<=value){
                maxValue=value;
                word=wordPup;
            }
            level-1;
            myWord.insert(myWord.begin()+i,wordPup);
            player.pop_back();
        }
        if(word=="x") return 0;
        return maxValue;
    }

}

void botplay(vector<string> &myWord,vector<string> &player,vector<string> &bot)
{
    int level=0;
    string word;
    int minValue=10000;
    for(int i=0;i<myWord.size();i++){
            string wordPup=myWord[i];
            bot.push_back(myWord[i]);
            myWord.erase(myWord.begin()+i);
            int value=miniMax(myWord,player,bot,10,level+1);
            if(minValue>value){
                minValue=value;
                word=wordPup;
            }
            myWord.insert(myWord.begin()+i,wordPup);
            bot.pop_back();
        }
    bot.push_back(word);
    for(int i=0;i<myWord.size();i++){
        if(myWord[i]==word){
            myWord.erase(myWord.begin()+i);
        }
    }
}

void playerPlay(vector<string> &myWord,vector<string> &player,vector<string> &bot)
{
    string word;
    int index,temp=0;
    cout<<"INPUT STRING : ";
    cin>>word;
    for(int i=0;i<myWord.size();i++){
        if(myWord[i]==word){
            index=i;
            temp++;
        }
    }
    if(temp!=0){
        player.push_back(word);
        myWord.erase(myWord.begin()+index);
    }
    else{
        playerPlay(myWord,player,bot);
    }
}

void showWin(vector<string> play)
{
    string wordWin[8][3]={{"AS","FAT","PAN"},{"SPIT","AS","SO"},{"IF","IN","SPIT"},{"FOP","FAT","IF"},
                        {"SPIT","FAT","NOT"},{"PAN","NOT","IN"},{"SO","NOT","FOP"},{"SPIT","FOP","PAN"}};
    if(play.size()>=3){
        int win=0;
        for(int i=0;i<8;i++){
            win=0;
            for(int j=0;j<play.size();j++){
                if(play[j]==wordWin[i][0] || play[j]==wordWin[i][1] || play[j]==wordWin[i][2]){
                  win++;
                  if(win>=3){
                    for(int k=0;k<3;k++){
                        cout<<"\t"<<wordWin[i][k];
                    }
                  }
                }
            }
        }
    }
}

int main()
{
    vector<string> myWord,player,bot;
    int start;
    writeFile(myWord);
    cout<<"\t----- SPIT NOT SO -----\n"<<endl;
    cout<<"\tPlay 1st or 2nd : ";
    cin>>start;
    for(int i=0;i<9&&checkWin(player,bot)==0;i++){
        if((i+start)%2==0){
            botplay(myWord,player,bot);
        }
        else{
            system("cls");
            show(myWord,player,bot);
            playerPlay(myWord,player,bot);
        }
        switch(checkWin(player,bot))
        {
        case 1:
            system("cls");
            show(myWord,player,bot);
            cout<<"\tA DRAW. HOW DROLL.\n";
            break;
        case -10:
            system("cls");
            show(myWord,player,bot);
            cout<<"BOT WIN!!!";
            showWin(bot);
            cout<<endl;
            break;
        case 10:
            system("cls");
            show(myWord,player,bot);
            cout<<"You win. Inconceivable!!!";
            showWin(player);
            cout<<endl;
            break;
        }
    }
    return 0;
}
