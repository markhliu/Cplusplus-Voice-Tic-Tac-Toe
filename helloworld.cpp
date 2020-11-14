#include "stdafx.h"
#include <iostream>
#include<sstream>
#include <speechapi_cxx.h>
#include <sapi.h>
#include <string>
#include <stdio.h>
#include "CTurtle.hpp"


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;


namespace ct = cturtle;



int center[9][2] = { {-200, -200}, {0, -200}, {200, -200},{-200, 0},  {0, 0},  {200, 0},{-200, 200},  {0, 200},  {200, 200} };
string turn[2] = { "x","o" };
string cl[9] = { "1","2","3","4","5","6","7","8","9" };

ct::TurtleScreen scr(600, 600);
ct::Turtle turtle(scr);


int board(ct::Turtle& turtle) {


    for (int i = -100; i <= 100; i += 200) {

        turtle.penup();
        turtle.goTo(i, -300);
        turtle.pendown();
        turtle.goTo(i, 300);
        turtle.penup();
        turtle.goTo(-300, i);
        turtle.pendown();
        turtle.goTo(300, i);
        turtle.penup();
    };

    for (int i = 0; i < 9; i++) {

        turtle.goTo(center[i][0] - 80, center[i][1] - 80);

        turtle.write(to_string(i + 1));
    };

    return 0;
}


int mark_cell(int cell) {


    try
    {

        scr.update();
        if (turn[0] == "x") {
            turtle.pencolor({ "gray" });
            turtle.penup();
            turtle.goTo(center[cell - 1][0] - 75, center[cell - 1][1] - 75);
            turtle.pendown();
            turtle.goTo(center[cell - 1][0] + 75, center[cell - 1][1] + 75);
            turtle.penup();
            turtle.goTo(center[cell - 1][0] + 75, center[cell - 1][1] - 75);
            turtle.pendown();
            turtle.goTo(center[cell - 1][0] - 75, center[cell - 1][1] + 75);
            turtle.penup();
            turn[0] = "o";
            turn[1] = "x";

        }
        else {
            turtle.penup();
            turtle.goTo(center[cell - 1][0], center[cell - 1][1]);
            turtle.circle(80, 360, { "gray" });
            turn[0] = "x";
            turn[1] = "o";
        }


    }
    catch (exception e)
    {
        cout << e.what();
    }




    return 0;
}

bool check_win() {
    bool flag = false;
    if (cl[0] == turn[0] && cl[0] == cl[1] && cl[0] == cl[2]) flag = true;
    if (cl[3] == turn[0] && cl[3] == cl[4] && cl[3] == cl[5]) flag = true;
    if (cl[6] == turn[0] && cl[6] == cl[7] && cl[6] == cl[8]) flag = true;
    if (cl[0] == turn[0] && cl[0] == cl[3] && cl[0] == cl[6]) flag = true;
    if (cl[0] == turn[0] && cl[0] == cl[4] && cl[0] == cl[8]) flag = true;
    if (cl[2] == turn[0] && cl[2] == cl[4] && cl[2] == cl[6]) flag = true;
    if (cl[1] == turn[0] && cl[1] == cl[4] && cl[1] == cl[7]) flag = true;
    if (cl[2] == turn[0] && cl[2] == cl[5] && cl[2] == cl[8]) flag = true;
    return flag;
}

bool check_tie() {
    bool flag = false;
    if (cl[0] != "1" && cl[1] != "2" && cl[2] != "3" && cl[3] != "4" && cl[4] != "5" &&
        cl[5] != "6" && cl[6] != "7" && cl[7] != "8" && cl[8] != "9") flag = true;
    return flag;
}

int tosay(wstring input)
{
    ISpVoice* pVoice = NULL;

    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (SUCCEEDED(hr))
    {
        hr = pVoice->Speak((L"<voice required='Gender = Female;'>" + input).c_str(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    ::CoUninitialize();
    return 0;
}
string recognizeSpeech()
{
    auto config = SpeechConfig::FromSubscription("e9ec52754de5449baefe4f7340991743", "eastus");
    auto recognizer = SpeechRecognizer::FromConfig(config);

    cout << "Say something...\n";
    try {
        auto result = recognizer->RecognizeOnceAsync().get();
        return result->Text;
    }
    catch (exception e) {
        return " ";
    }
}




int main()
{

    wstring input, turns;


    scr.bgcolor({ "azure" });
    turtle.width(3);
    turtle.hideturtle();

    board(turtle);
    string inp;
    do {
        cout << "What's your move "<<"player " << turn[0]<<"?\n";
        wstring turns(turn[0].begin(), turn[0].end());
        
        tosay(L"Wht's your move, player "+turns);
        inp = recognizeSpeech();
        inp.erase(inp.size() - 1);
        cout << "you just said " << inp<< endl;
        wstring input(inp.begin(), inp.end());
        tosay(L"you just said " + input);

        if (inp == "1" | inp == "2" | inp == "3" | inp == "4" | inp == "5" | inp == "6" | inp == "7" | inp == "8" | inp == "9") {
            stringstream geek(inp);
            int idx;
            geek >> idx;
            if (cl[idx - 1] == inp) {
                mark_cell(idx);
                cl[idx - 1] = turn[0];
                if (check_win() == true) { cout << "Congrats, you have won this game, player " << turn[1] << endl; 
                tosay(L"Congrats, you have won this game, player " + turns);break; 
                }
                else if (check_tie() == true) { cout << "game over, it's a tie" << endl;
                tosay(L"Game over, it's a tie");
                break; }
            }
            else { cout << "invalid move" << endl; 
            tosay(L"invalid move ");
            };

        }
        else
        {
            cout << "please use use a number between 1 to 9 " << endl;
            tosay(L"Please use a number between 1 and 9");
        }
    } while (inp != "Stop listening");




    scr.update();



    scr.exitonclick();
    return 0;
}







