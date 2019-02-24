// checkActivity.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include <string>

#include <fstream>

/*typedef struct tagLASTINPUTINFO {
	UINT  cbSize;
	DWORD dwTime;
} LASTINPUTINFO, *PLASTINPUTINFO;
*/

int main(int argc, char* argv[])
{
	//possible command params
	
	unsigned long timeoutSec = 293; // ~5 mins +/- sleepSec // after this limit is reached machine is available
	std::string outputfileName;   // outputfile that will contain either FREE or BUSY
	unsigned int sleepSec = 15;   // how often to check if we're busy or not.

	//internal variables
	DWORD currentTick;   // check current tick against lastinputinfo tick
	LASTINPUTINFO plii;  // set by GetLastInputInfo()
	plii.cbSize = sizeof(LASTINPUTINFO); //need to set buffer size to appropriate size
	DWORD tickdiff;      // holds difference between currentTick and last Input 
	DWORD timeoutInTicks = timeoutSec*1000; 

	outputfileName = "freebusy.dat";
	
	std::ofstream ofile;

	//stop us from uneccesarily writing file with same info
	// initialise to false to force run on first iteration 
	// will this always fire, even if no recent input 
	// e.g. started automatically with system start or task scheduler?
	bool lastStatusBusy = false;

	printf("Checking every %ld sec if active within last %ld sec, outputting to file %s\n",
		    sleepSec, timeoutSec, outputfileName.c_str());
	printf("Ctrl+C a couple of times to exit\n");
	
	while (true) {
		currentTick = GetTickCount();
		
		if (GetLastInputInfo(&plii)) {
			tickdiff = currentTick - plii.dwTime;
			if (tickdiff >= timeoutInTicks) {
				printf("FREE since %lds\r",(unsigned long)(tickdiff/1000));
				//do stuff to show computer is free
				//update output file
				if (lastStatusBusy) {
					ofile.open(outputfileName);
					ofile << "FREE";
					ofile.close();
					lastStatusBusy = false;
				}
			}
			else {
				printf("BUSY                   \r");
				//do stuff to show computer is in use
				//update output file
				if (!lastStatusBusy) {
					ofile.open(outputfileName);
					ofile << "BUSY";
					ofile.close();
					lastStatusBusy = true;
				}
			}
		}
		else {
			printf("getLastInputInfo failed.\n");
		}
		
		Sleep(1000 * sleepSec);
	}
    return 0;
}
