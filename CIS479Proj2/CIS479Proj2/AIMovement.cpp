#include "AIMovement.h"
#include <iostream>

using namespace std;

AI::AI(double maze[6][7])
{
	rowMaster = 5;
	colMaster = 1;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			nodeMaze[i][j].currentValue = maze[i][j];
		}
	}
}

int* AI:: sensorUpdate(int row, int col)
{
	static int sensed[4];//0 is blocked, 1 is open
	//0west, 1north, 2east, 3south
	
		if (row - 1 > -1)
		{
			if (nodeMaze[row-1][col].currentValue != -2)//north
			{
				sensed[1] = 1;
			}
			else
			{
				sensed[1] = 0;
			}
		}
		else
		{
			sensed[1] = 0;
		}

		if (row + 1 > 5)//south
		{
			sensed[3] = 0;
		}
		else
		{
			if (nodeMaze[row + 1][col].currentValue != -2)
			{
				sensed[3] = 1;
			}
			else
			{
				sensed[3] = 0;
			}
		}

		if (col - 1 > -1)//west
		{
			if (nodeMaze[row][col - 1].currentValue != -2)
			{
				sensed[0] = 1;
			}
			else
			{
				sensed[0] = 0;
			}
		}
		else
		{
			sensed[0] = 0;
		}

		if (col + 1 > 6)//east
		{
			sensed[2] = 0;
		}
		else
		{
			if (nodeMaze[row][col + 1].currentValue != -2)
			{
				sensed[2] = 1;
			}
			else
			{
				sensed[2] = 0;
			}
		}

		return sensed;

		
}

void AI::updateMasterSense()
{
	int* sensed = sensorUpdate(rowMaster, colMaster);
	for (int i = 0; i < 4; i++)
	{
		masterSense[i] = *(sensed+i);
	}
}

void AI::masterMazeUpdate(double maze[6][7])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			maze[6][7] = nodeMaze[6][7].currentValue;
		}
	}
}

void AI::sensorValues()// check master sense against current and then update sensor value
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int* temp = sensorUpdate(i, j);
			for (int w = 0; w < 4; w++)
			{
				nodeMaze[i][j].sensed[w] = *(temp + w);
			}
		}
	}

	masterSenseValue = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (nodeMaze[i][j].currentValue != -2)
			{
				double tempTotal = 1;
				for (int w = 0; w < 4; w++)
				{
					if (nodeMaze[i][j].sensed[w] == masterSense[w])//same as sensed
					{
						if (masterSense[w] == 1)
						{
							tempTotal = tempTotal * .9;
						}
						else
						{
							tempTotal = tempTotal * .85;
						}
					}
					else//different sensed
					{
						if (masterSense[w] == 1)
						{
							tempTotal = tempTotal * .15;
						}
						else
						{
							tempTotal = tempTotal * .1;
						}
					}
				}

				nodeMaze[i][j].sensedValue = tempTotal * nodeMaze[i][j].currentValue;
				masterSenseValue += nodeMaze[i][j].sensedValue;
			}
		}
	}


	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (nodeMaze[i][j].currentValue != -2)
			{
				nodeMaze[i][j].currentValue = (nodeMaze[i][j].sensedValue / masterSenseValue) *100;
				
			}

			cout << nodeMaze[i][j].currentValue << "    " << " ";
		}
		cout << endl;
	}
	

	
}

void AI:: movementUpdate(int direction)
{
	if (direction == 1)//west
	{
		if (colMaster - 1 > -1)
		{
			colMaster--;
		}
	}
	else if (direction == 2)//north
	{
		if (rowMaster - 1 > -1)
		{
			rowMaster--;
		}
		updateMovementProbabilityNorth();
	}
	else if (direction == 3)//east
	{
		if (colMaster + 1 < 7)
		{
			colMaster++;
		}
		updateMovementProbabilityEast();
	}
	else if (direction == 4)//south
	{
		if (rowMaster + 1 < 6)
		{
			rowMaster++;
		}
	}


}

void AI::updateMovementProbabilityNorth()
{
	double tempMaze[6][7];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			double tempTotal = 0;
			if (nodeMaze[i][j].currentValue != -2)
			{
				if (i + 1 < 6 && nodeMaze[i+1][j].currentValue != -2)//south
				{
					tempTotal = tempTotal + (nodeMaze[i+1][j].currentValue *.8);
				}

				if (j + 1 < 7 && nodeMaze[i][j+1].currentValue != -2)//east
				{
					tempTotal = tempTotal + (nodeMaze[i][j + 1].currentValue *.1);
				}
				else
				{
					tempTotal = tempTotal + (nodeMaze[i][j].currentValue *.1);
				}

				if (j - 1 > -1 && nodeMaze[i][j-1].currentValue != -2)//west
				{
					tempTotal = tempTotal + (nodeMaze[i][j - 1].currentValue *.1);
				}
				else
				{
					tempTotal = tempTotal + (nodeMaze[i][j].currentValue *.1);
				}

				if (i - 1 < 0 || nodeMaze[i - 1][j].currentValue == -2)
				{
					tempTotal = tempTotal + (nodeMaze[i][j].currentValue * .8);
				}
				tempMaze[i][j] = tempTotal;
			}
			else
			{
				tempMaze[i][j] = -2;
			}

			
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			nodeMaze[i][j].currentValue = tempMaze[i][j];
			cout << nodeMaze[i][j].currentValue << "    " << " ";
		}
		cout << endl;
	}
}

void AI::updateMovementProbabilityEast()
{
	double tempMaze[6][7];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			double tempTotal = 0;
			if (nodeMaze[i][j].currentValue != -2)
			{
				

				if (j - 1 > -1 && nodeMaze[i][j - 1].currentValue != -2)//west
				{
					tempTotal = tempTotal + (nodeMaze[i][j - 1].currentValue *.8);
				}

				if (i - 1 > -1 && nodeMaze[i - 1][j].currentValue != -2)//north
				{
					tempTotal = tempTotal + (nodeMaze[i - 1][j].currentValue * .1);
				}
				else
				{
					tempTotal = tempTotal + (nodeMaze[i][j].currentValue *.1);
				}

				if (i + 1 < 6 && nodeMaze[i + 1][j].currentValue != -2)//south
				{
					tempTotal = tempTotal + (nodeMaze[i + 1][j].currentValue *.1);
				}
				else
				{
					tempTotal = tempTotal + (nodeMaze[i][j].currentValue *.1);
				}

				
				if (j + 1 > 6 || nodeMaze[i][j+1].currentValue == -2)
				{
					tempTotal = tempTotal + (nodeMaze[i][j].currentValue * .8);
				}

				
				tempMaze[i][j] = tempTotal;
			}
			else
			{
				tempMaze[i][j] = -2;
			}


		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			nodeMaze[i][j].currentValue = tempMaze[i][j];
			cout << nodeMaze[i][j].currentValue << "    " << " ";
		}
		cout << endl;
	}
}

void AI::updateProbabilitySensor()
{
	sensorValues();
}