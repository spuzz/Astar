// AstarUnitTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Astar.h"
#include <iostream>
#include <numeric>
#include "AstarThreadPool.h"
#include "AstarService.h"
#include "AstarLifeCycleHandler.h"

using namespace std;

/* Main Test Program for Astar Library 
 *
 *	Currently creates a threadpool and an Astar factory
 *	Then runs multiple Astars to test the speed
 *  Outputs the path length to confirm that the function is retrieving a real path
 *
 * TODO : Add real Unit tests to confirm path integrity and error handling
 */
class AstarHandler : public AstarLifeCycleHandler
{
	void successOnPathFinding(locationVector path) {
		static int count = 0;
		cout << "Output Path Size " << count << " + "<< path.size() << endl;
		count++;
	}

	void errorOnPathFinding() {

	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	// Create a grid (Would be the tilemap) to test Astar
	std::vector<std::vector<int>> gridVector;
	for (int a = 0; a < 1000; a++) {
		std::vector<int> v(1000);
		if (a == 0 || a == 999) {
			std::fill(v.begin(), v.end(), 1);
		}
		else {
			std::fill(v.begin(), v.end(), 10);
			v[0] = 1;
		}

		gridVector.push_back(v);
	}
	
	// Create thread pool and astar factory


	auto start = std::chrono::steady_clock::now();
	shared_ptr<AstarLifeCycleHandler> handler(new AstarHandler);
	vector<shared_ptr<AstarService>> Astars;
	shared_ptr<AstarService> astar;
	// Loop through retrieving Astar objects from factory and running path calculation using threads from pool
	for (int a = 0; a < 255; a++) {
		
		astar = shared_ptr<AstarService>(new GridAstarService(gridVector, 10, 10));
		astar->submitPath(999, 999, 10, 10, handler);
		//unitTest->calculatePreSetupPath();
	    //threadPool.enqueue(unitTest);
	}

	// Retrieve results from pathing
	//while (1) {
	//	std::this_thread::sleep_for(std::chrono::seconds(1));
	//}
	//cout << "HELLO" << endl;
	//auto end = std::chrono::steady_clock::now();
	//auto diff = end - start;
	//cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	return 0;
}

