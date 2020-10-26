#include "Zone.h"


void Zone::ChangeTo(size_t i, size_t j, Cell cellType) {
	zone[i][j] = cellType;
}

Zone::Cell Zone::Get(size_t i, size_t j) const
{
	return zone[i][j];
}

void Zone::RandomGenerate()
{
    


    bool randoming = true;
    int count1 = 4;
    int count2 = 3;
    int count3 = 2;
    int count4 = 1;
    while (randoming)
    {
        int x = rand()%10;
        int y = rand() % 10;

        bool dir;
        if (rand()%2 == 0)
            dir = false;
        else
            dir = true;

        int j = 0;
        if (count4 != 0)
            j = 4;
        else if (count3 != 0)
            j = 3;
        else if (count2 != 0)
            j = 2;
        else if (count1 != 0)
            j = 1;

        if (dir == false)
        {

            //Horizontal
            if (10 - y + 1 <= j)
            {
                continue;
            }
            else
            {
                bool isDone = true;
                for (int i = 0; i < j; i++)
                {

                    for (int n = -1; n < 2; n++)
                    {
                        for (int m = -1; m < 2; m++)
                        {
                            if (x + n > 9 || y + i + m > 9 || x + n < 0 || y + i + m < 0)
                                continue;
                            if (zone[x + n][y + i + m] == Cell::IsShip)
                            {
                                isDone = false;
                                break;
                            }
                        }
                        if (isDone == false)
                        {
                            break;
                        }
                    }
                    if (isDone == false)
                    {
                        break;
                    }
                }
                if (isDone == true)
                {
                    for (int i = 0; i < j; i++)
                    {
                        zone[x][y + i] = Cell::IsShip;
                    }
                    if (j == 4)
                        count4--;
                    else if (j == 3)
                        count3--;
                    else if (j == 2)
                        count2--;
                    else if (j == 1)
                        count1--;
                }
            }
        }
        else if (dir == true)
        {
            //Vertical
            if (10 - x + 1 <= j)
            {
                continue;
            }
            else
            {
                bool isDone = true;
                for (int i = 0; i < j; i++)
                {
                    for (int n = -1; n <= 1; n++)
                    {
                        for (int m = -1; m <= 1; m++)
                        {
                            if (x + i + n > 9 || y + m > 9 || x + i + n < 0 || y + m < 0)
                                continue;
                            if (zone[x + i + n][y + m] == Cell::IsShip)
                            {
                                isDone = false;
                                break;
                            }
                        }
                        if (isDone == false)
                        {
                            break;
                        }
                    }
                    if (isDone == false)
                    {
                        break;
                    }
                }
                if (isDone == true)
                {
                    for (int i = 0; i < j; i++)
                    {
                        zone[x + i][y] = Cell::IsShip;
                    }
                    if (j == 4)
                    {
                        count4--;
                    }
                    else if (j == 3)
                    {
                        count3--;
                    }
                    else if (j == 2)
                    {
                        count2--;
                    }
                    else if (j == 1)
                    {
                        count1--;
                    }
                }
            }
        }


        if (j == 0)
            randoming = false;
    }
    
}
