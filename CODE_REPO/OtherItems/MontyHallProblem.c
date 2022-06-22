#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define GAMES 10000
// This is a simulation of the monty hall problem upto N doors.

// The problem is this ,suppose you go to your friends house and there is a
// game , in which there are N doors , behind each door there is a item.
// 1 lucky door contains a lavish car, other doors contain a sheep.
// Whatever door you choose you win the item behind it.
// After you choose a door the host opens another door that contains a sheep,
// (this is always possible for N > 2 doors)
// and gives you a choice to whether you want to change your choice or stick to it
// What is the best way to win to change or not to change your choice.

void printArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main()
{
    int N; // Number of doors
    printf("Enter the number of doors:");
    scanf("%d", &N);
    srand(time(NULL));
    int Win = 0;
    int Loss = 0;
    int Switch = 0;
    int SwitchWin[N - 1];
    int SwitchLoss[N - 1];
    for (int i = 1; i <= N - 1; i++)
    {
        SwitchLoss[i - 1] = 0;
        SwitchWin[i - 1] = 0;
    }
    for (int i = 1; i <= GAMES; i++)
    {
        Switch = 0;
        int LuckyChoice = rand() % (N) + 1;
        int YourChoice = rand() % (N) + 1;
        int Arr[N];
        int State[N];
        for (int i = 1; i <= N; i++)
        {
            Arr[i - 1] = 0;
            State[i - 1] = 0; // All doors are closed initially
        }
        Arr[LuckyChoice - 1] = 1;
        int OpenDoor = 0;
        for (int i = 1; i <= N - 2; i++)
        {
            OpenDoor = rand() % (N) + 1; // Open a door with sheep
            while (OpenDoor == YourChoice || State[OpenDoor - 1] == 1 || OpenDoor == LuckyChoice)
            {
                OpenDoor = rand() % (N) + 1; // Switch
            }
            State[OpenDoor - 1] = 1; // this door is opened.
            int temp = YourChoice;
            YourChoice = rand() % (N) + 1;
            while (State[YourChoice - 1] == 1)
            {
                YourChoice = rand() % (N) + 1; // Switch
            }
            if (temp != YourChoice)
            {
                Switch++; // You switched
            }
        }
        if (LuckyChoice == YourChoice)
        {
            Win++;
            SwitchWin[Switch]++;
        }
        else
        {
            Loss++;
            SwitchLoss[Switch]++;
        }
    }
    printf("WIN:%d and LOSS:%d\n", Win, Loss);
    printArray(SwitchWin, N - 1);  // print wins for each switches
    printArray(SwitchLoss, N - 1); // print losses for each switches
    return 0;
}
// Calculate mathematical probability for each event and then simulate the result
