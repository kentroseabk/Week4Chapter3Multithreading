// Week4Chapter3Multithreading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    Challenge: 

    Firstly, read ahead into the next chapter's challenges to understand the 
        overarching Multithreading challenge. 
    Follow the provided videos in this chapter, recreating the hello world example code, 
         reviewing how threading can be used in the maze game. 
    Attempt the small challenges shown along the way to familiarise yourself with threading, 
        before moving into the next chapter
*/

/*
    Notes:

    I simplified the program by removing the duplicated update function and instead 
        spun up more threads using the UpdateCharacter function.
    Allowed the program user to change how many threads they wanted to spin up
        so they can see how it affects the character.
*/

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

bool DidQuit = false;
bool ShouldDecrementLives = false;
const int SLEEP_TIME = 5000;

struct Character
{
    float position = 0.0f;
    int score = 0;
    int lives = 1;

    void DisplayStats()
    {
        cout << "Lives: " << lives << endl;
    }
};

Character player;

void UpdateCharacter()
{
    //while (!DidQuit)
    {
        //if (ShouldDecrementLives)
        {
            if (player.lives > 0)
            {
                this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
                //std::this_thread::yield();
                --player.lives;
            }
        }
    }
}

void ProcessInput()
{
    while (!DidQuit)
    {
        cout << "'a' to decrement player lives" << endl;
        cout << "'d' to display player stats" << endl;
        cout << "'q' to quit" << endl;

        char userInput;
        cin >> userInput;

        switch (userInput)
        {
        case 'a':
            ShouldDecrementLives = true;
            break;
        case 'd':
            player.DisplayStats();
            break;
        case 'q':
            DidQuit = true;
            break;
        default:
            break;
        }
    }
}

void CreateUpdateThreads(thread characterUpdateThreads[], const int numberOfUpdateThreads)
{
    for (int i = 0; i < numberOfUpdateThreads; ++i)
    {
        characterUpdateThreads[i] = thread(UpdateCharacter);
    }
}

void JoinUpdateThreads(thread characterUpdateThreads[], const int numberOfUpdateThreads)
{
    for (int i = 0; i < numberOfUpdateThreads; ++i)
    {
        characterUpdateThreads[i].join();
    }
}

uint32_t GetTime()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

int main()
{
    uint32_t start = GetTime();

    constexpr int numberOfUpdateThreads = 5;

    thread characterUpdateThreads[numberOfUpdateThreads];

    //thread inputHandler(ProcessInput);

    player.DisplayStats();

    CreateUpdateThreads(characterUpdateThreads, numberOfUpdateThreads);

    //inputHandler.join();
    cout << "Pre-JoinUpdateThreads" << endl;
    JoinUpdateThreads(characterUpdateThreads, numberOfUpdateThreads);
    cout << "Post-JoinUpdateThreads" << endl;

    player.DisplayStats();

    uint32_t end = GetTime();

    cout << "Created " << numberOfUpdateThreads << " threads, each w/ a sleep time of " << SLEEP_TIME / (float)1000 << " second/s." << endl;
    cout << "Total time: " << (end - start) / (float)1000 << " seconds.";

    return 0;
}