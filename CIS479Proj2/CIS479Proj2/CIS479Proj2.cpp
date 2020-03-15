#include "AIMovement.h"
#include <iostream>

using namespace std;

int main()
{
	double masterA[][7] = { {3.23, 3.23, 3.23, 3.23, 3.23, 3.23, 3.23},
						 {3.23, 3.23, -2, -2, -2, -2, 3.23},
						 {3.23, 3.23, -2, 3.23, 3.23, -2, 3.23},
						 {3.23, -2, -2, 3.23, 3.23, -2, 3.23},
						 {3.23, 3.23, 3.23, 3.23, -2, -2, 3.23},
						 {3.23, 3.23, 3.23, 3.23, 3.23, 3.23, 3.23} };

	AI z(masterA);

	z.updateMasterSense();
	cout << "Sensor update" << endl;
	z.updateProbabilitySensor();
	cout<< endl << "motion Update N" << endl;
	z.movementUpdate(2);
	cout << endl<< "Sensor update" << endl;
	z.updateMasterSense();
	z.updateProbabilitySensor();
	cout << endl << "motion Update E" << endl;
	z.movementUpdate(3);
	cout << endl << "Sensor update" << endl;
	z.updateMasterSense();
	z.updateProbabilitySensor();
	cout << endl << "motion Update E" << endl;
	z.movementUpdate(3);
	cout << endl << "Sensor update" << endl;
	z.updateMasterSense();
	z.updateProbabilitySensor();
}

