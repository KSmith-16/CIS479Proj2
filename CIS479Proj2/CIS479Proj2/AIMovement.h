#pragma once

struct squares
{
	double sensedValue;
	int sensed[4];
	double currentValue;
};

class AI
{
public:
	AI(double maze[6][7]);
	//movement stuff
	void movementUpdate(int direction);//1 west, 2 north, 3 east, 4 south
	//sensor stuff
	void updateProbabilitySensor();
	void updateMasterSense();
	void masterMazeUpdate(double maze[6][7]);
	
private:
	int rowMaster;
	int colMaster;
	double masterSenseValue;
	//sensro stuff
	int masterSense[4];//0 is blocked, 1 is open
	//0west, 1north, 2east, 3south
	squares nodeMaze[6][7];
	int* sensorUpdate(int row, int col);
	void sensorValues();
	//movement stuff
	void updateMovementProbabilityNorth();
	void updateMovementProbabilityWeat();
	void updateMovementProbabilityEast();
	void updateMovementProbabilitySouth();
};
