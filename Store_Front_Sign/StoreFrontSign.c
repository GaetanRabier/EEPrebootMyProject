// New-BlinkingSign.cpp : Defines the entry point for the console application.

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1 

#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <conio.h>
#include <stdio.h>


typedef struct signPowerInfo
{
    int BatteryUsage;
    int ProductionHours; // Battery Tracking - how long has the sign been in use for warranty purposes 
    char* cBatteryBrand;
}signPowerInfo;

struct signPowerInfo* mySignPowerInfo;

//function declarations 
int  filter(unsigned int code, struct _EXCEPTION_POINTERS* ep);
void LightUpSign();
int  GetBatteryUsage();
void PrintBatteryBrand();
void RechargeBattery();
void AddBatteryVendor();

// Variables
int iBatteryBrandChanged = 0;

//Main
int main(int argc, char* argv[])
{

    /*++

    Routine Description:

    This function starts blinking the lights for the sign.
    It also checks the battery level and Prints the battery brand.

    --*/
    mySignPowerInfo = (signPowerInfo*)malloc(sizeof(signPowerInfo));
    

    //mySignPowerInfo->
    if (mySignPowerInfo == NULL)
    {
        printf("ERROR: Out of memory\n");
        return 1;
    }
    else
    {
        //assigning the initial values
        mySignPowerInfo->BatteryUsage = 5;
        
    }

    int UserSelection;
    int iBatteryUsage;
    char charcBatteryBrand;

    while (1)
    {
        //Get the user selection
        printf("Choose an Option- \nL to Power up the blinking lights (Open For Business) \nB for BatteryUsage \nP to print the battery brand \nR to recharge the Battery\nA Add a battery vendor\nQ to quit\n\n");
        UserSelection = getchar();

        switch (UserSelection)
        {
        case 'L':
        {
            //Light Up the Sign
            LightUpSign();
            getchar(); //to clear the Enter Key
            break;
        }
        case 'B':
        {
            //Check the Battery Level
            iBatteryUsage = GetBatteryUsage();
            printf("The current battery level is %d\n\n", iBatteryUsage);
            getchar(); //to clear the Enter Key;
            break;
        }
        case 'P':
        {
            //Print the Battery Brand 
            PrintBatteryBrand();
            getchar(); //to clear the Enter Key;
            break;
        }
        case 'Q':
        {
            return 0;
            break;
        }
        case 'R':
        {
            RechargeBattery();
        }
        case 'A':
        {
            AddBatteryVendor();
        }

        default:
        {
            printf("Invalid Option\n\n");
            getchar(); //to clear the Enter Key;
            break;
        }
        }
    }
}


int GetBatteryUsage()
{
    return mySignPowerInfo->BatteryUsage;
}

void PrintBatteryBrand()
{
    /*++

    Routine Description:

    This function prints out the current battery brand.
    TO DO: We need the ability to allow the user to add
    a new vendor (forward thinking)

    Requirements:
    1. This requires a second temp buffer with the a string literal
    2. Copy the contents of the temp buffer into mySignPowerInfo->cBatteryBrand

    --*/
    if (iBatteryBrandChanged == 0)
    {
        int len;

        //Current Supplier is Rayovac with a 10 year contract 
        char cBatteryBrand[8] = { 'R', 'a', 'y', 'o', 'v', 'a', 'c','\0' };

        len = sizeof(cBatteryBrand);

        mySignPowerInfo->cBatteryBrand = malloc(len);

        //Copy the buffer over 
        strncpy(mySignPowerInfo->cBatteryBrand, cBatteryBrand, len);
    }

    printf("The battery brand is %s\n\n", mySignPowerInfo->cBatteryBrand);

    return;
}

void LightUpSign()
{
    if (mySignPowerInfo->BatteryUsage == 0)
    {
        printf("Not enough battery, please recharge using R option in the main menu");
        Sleep(5000);
    }
    else
    {

        int i = 0;

        for (i = 1; i < 20; i++)
        {
            if (mySignPowerInfo->BatteryUsage == 0)
            {
                printf("No more Battery. Shutting down.....\n");
                Sleep(1000);
                printf("3\n");
                Sleep(1000);
                printf("2\n");
                Sleep(1000);
                printf("1\n\n\n");
                Sleep(1000);
                printf("Silently dying....\n");
                Sleep(3000);
                break;
            }
            //clear the screen
            system("cls");
            //yellow text
            system("COLOR 06");
            printf("Open For Business!\n");
            Sleep(100);

            if (i > 10)
            {
                __try
                {
                    //clear the screen
                    system("cls");
                    //red text
                    system("COLOR 7C");
                    printf("Open For Business!\n");
                    Sleep(100);

                    mySignPowerInfo->BatteryUsage--;

                }
                __except (filter(GetExceptionCode(), GetExceptionInformation()))
                {
                    printf("Malfunction!\n");
                    //clear the screen
                    system("cls");
                    //yellow text
                    system("COLOR 06");
                    printf("Malfunction!\n");
                    Sleep(100);
                    getchar();
                    return;
                }
            }

            //clear the screen
            system("cls");
            //red text
            system("COLOR 7C");
            printf("Open For Business!\n");
            Sleep(100);
        }
    }

    system("cls");
    system("COLOR 07");
    printf("Power Cycle Complete - Turning Lights Off\n\n");
    return;
}

int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
    if (code == EXCEPTION_ACCESS_VIOLATION)
    {
        return EXCEPTION_EXECUTE_HANDLER;
    }
    else
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }
}

void RechargeBattery()
{
    while (mySignPowerInfo->BatteryUsage != 100)
    {
        mySignPowerInfo->BatteryUsage++;
        Sleep(1000);
        printf("Charging the battery....\n");
        if (mySignPowerInfo->BatteryUsage % 10 == 0)
        {
            printf("The battery is now at %d.\n", mySignPowerInfo->BatteryUsage);
        }
    }
}

void AddBatteryVendor()
{
    printf("Please enter the name of the new vendor of the battery\n");
    char cBatteryBrand[50];
    scanf_s("%s", &cBatteryBrand,sizeof(cBatteryBrand));
    int len = sizeof(cBatteryBrand);;
    mySignPowerInfo->cBatteryBrand = malloc(len);

    strncpy(mySignPowerInfo->cBatteryBrand, cBatteryBrand, len);

    iBatteryBrandChanged = 1;

    //mySignPowerInfo->cBatteryBrand = malloc(len);
    

}