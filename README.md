# Cplusplus-Voice-Tic-Tac-Toe
Voice controlled Tic Tac Toe game in C++

## About this repo
This repo is to create a fun voice-controlled graphical Tic Tac Toe game in C++ using the CTurtle library. The graphics are based on Jesse Walker's repo [here](https://github.com/walkerje/C-Turtle). To play the game, say a number between 1 and 9 into your microphone. You may want to start with the silent version first [here](https://github.com/markhliu/CPP-graphical-Tic-Tac-Toe). You need a free Microsoft Azure subscription for the voice part to work. You also need to install the Microsoft Cognitive Service Speech package in Visual Studio 2019. 

## Apply for a Microsoft Azure subscription key
First, you should install Visual Studio 2019 and the associated C/C++ support on your computer. Go to the site https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-160 for detailed instructions. 

We’ll use the Microsoft Azure Cognitive Service for both text to speech and speech recognition. You’ll need a subscription for that and it’s free for our purpose. The detailed instructions are here https://docs.microsoft.com/en-us/azure/cognitive-services/speech-service/overview#try-the-speech-service-for-free. You need both a Microsoft account and an Azure account. Log into the Azure portal and create the Azure resource to obtain your subscription key. Your subscription key is a long string of letters and numbers. You also need a region code based on where you live: examples are “eastus”, “westus” and so on.

You should first learn how speech recognition and text to speech work in C++ using Azure based on instructions [here](https://github.com/Azure-Samples/cognitive-services-speech-sdk/).   

## Play the voice controlled Tic Tac Toe
To play the voice controlled Tic Tac Toe, put the file helloworld.cpp, along with files CImg.h and CTurtle.hpp (both downloaded from Jesse Walker's repo), and files stdafx.cpp, stdafx.h, and targetver.h (downloaded from https://github.com/Azure-Samples/cognitive-services-speech-sdk/tree/master/quickstart/cpp/windows/from-microphone/helloworld) in the same folder and compile it.

You can see a video demo [here](https://github.com/Azure-Samples/cognitive-services-speech-sdk/).   
