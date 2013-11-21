#include <iostream>
#include <cstdlib>

using namespace std;

//kill until this point
const int amountOfSurvivors = 2;
//kills every Nth person
const int timesBeforeKilling = 3;
//amount of rebels living at start
const int rebelStartingCount = 41;




//this function calculates the distance, element wise, from the person we need to kill.
int distanceNextPersonToKill(int startSpot, int alivePeoplePassed, int amountBodiesPassed, bool *rebel)
{
    //if we passed by three alive people, end the count.
    if (alivePeoplePassed == timesBeforeKilling)
    {
        return 0;
    }
    else
    {
        //the modulus lets the increment count transition from 40 to 0. we then check the element.
        //if the rebel at elementToCheck is alive, add one to alivepeoplepassed and amountbodiespassed
        //if he is dead, we add one to the distance and call the function again.
        int elementToCheck = (startSpot + amountBodiesPassed) % rebelStartingCount;
        if(rebel[elementToCheck]  == true)
        {
            //returns the distance to the next person to kill.
            return 1 + distanceNextPersonToKill( startSpot, (alivePeoplePassed + 1), (amountBodiesPassed + 1), rebel);
        }
        else
        {
            //returns the distance to the next person to kill.
            return 1 + distanceNextPersonToKill( startSpot, alivePeoplePassed, (amountBodiesPassed + 1), rebel);
        }
    }
}

//this function will kill each rebel until there are only the amount of survivors we want left.
//we pass the rebel array by reference, and the startSpot is where we killed the last guy at.
void KillRebelsUntilSurvivors(int rebelCount, int survivorCount, bool *rebel, int startSpot)
{
    //if the remaining rebels are the last survivors, end the recursion and killing.
    if (rebelCount == survivorCount)
    {

    }
    else
    {
        //give the element of the next rebel to kill.
        int elementOfRebelKilled = (startSpot + distanceNextPersonToKill(startSpot, 0, 0, rebel) - 1) % rebelStartingCount;
        //kill the rebel
        rebel[elementOfRebelKilled] = false;

        //if we made a circuit, print out the survivors of that circuit
        if (elementOfRebelKilled < startSpot)
        {

            cout << "Rebels that are alive after a circuit: " << endl;
            for(int i = 0; i < (rebelStartingCount - 1); i++)
            {
                if (rebel[i] == 1)
                {
                    cout << i + 1 << endl;
                }

            }
        }


        //call the function again, but lower the amount of rebels in circle, and set the startSpot to where the last rebel died at.
        KillRebelsUntilSurvivors(rebelCount - 1, survivorCount, rebel, elementOfRebelKilled);
    }
}





int main()
{
    //initialize the rebel circle.
    bool rebel[rebelStartingCount - 1];

    //set these rebels to living. if rebel[i] is true, soldier is alive,
    //else he is dead
    for(int i = 0; i < (rebelStartingCount - 1); i++)
    {
        rebel[i] = true;
    }
    //start the killing
    KillRebelsUntilSurvivors(rebelStartingCount, amountOfSurvivors, rebel, 0);


    //prints out the last positions of the survivors
    cout << "Final positions of the soldiers:" << endl;
    for(int i = 0; i < (rebelStartingCount - 1); i++)
    {
        if (rebel[i] == 1)
        {
            cout << i + 1 << " is alive." << endl;
        }

    }



    system("pause");
    return 0;
}


