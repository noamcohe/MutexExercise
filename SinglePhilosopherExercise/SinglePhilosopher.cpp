#include "pch.h"


// The number of iterations in the loop:
#define RUNNING_LOOP 1000000

// size of CHAR in a INT type, for 'sprintf_s'
// 1 byte to the digit, and 1 to NULL character:
#define SIZE 2


// argc = Argument Count. Number of arguments the function takes.
// argv = Argument Vector. Array of pointers to arguments.
INT main(INT argc, PCHAR argv[])
{
	if (argc != 2)
	{
		printf_s("Incorrect number of arguments\n");
		return 0;
	}

	// The argument that we got:
	INT id = atoi(argv[1]);

	// Names of Mutexes that will open:
	PCHAR idRightSide = (PCHAR)malloc(SIZE);
	PCHAR idLeftSide = (PCHAR)malloc(SIZE);

	// Convert it to a string:
	// Else if the serial number of our process is 5:
	if (id == 5)
	{
		if (idRightSide != NULL)
		{
			sprintf_s(idRightSide, SIZE, "%d", id);
		}

		if (idLeftSide != NULL)
		{
			sprintf_s(idLeftSide, SIZE, "%d", 1);
		}
	}

	// Else if 1 < id < 5:
	else
	{
		if (idRightSide != NULL)
		{
			sprintf_s(idRightSide, SIZE, "%d", id);
		}

		if (idLeftSide != NULL)
		{
			sprintf_s(idLeftSide, SIZE, "%d", (id + 1));
		}
	}

	// Create two Mutexes, one for each side:
	// Create Mutex for right side:
	HANDLE firstMutex = CreateMutexA(NULL, FALSE, idRightSide);

	// Create Mutex for left side:
	HANDLE lastMutex = CreateMutexA(NULL, FALSE, idLeftSide);

	INT count = 0;

	for (INT i = 0; i < RUNNING_LOOP; i++)
	{
		// Wait until right side will be open:
		if (firstMutex != NULL)
		{
			DWORD waitRightSide = WaitForSingleObject(firstMutex, INFINITE);
		}

		// Return if left side is open or close:
		if (lastMutex != NULL)
		{
			DWORD waitLeftSide = WaitForSingleObject(lastMutex, 0);

			// If the left sife is open:
			if (waitLeftSide == WAIT_OBJECT_0)
			{
				count++;
			}
		}

		// Close the left side:
		if (lastMutex != NULL)
		{
			ReleaseMutex(lastMutex);
		}

		// Close the right side:
		if (firstMutex != NULL)
		{
			ReleaseMutex(firstMutex);
		}
	}

	printf_s("Philosopher %d ate a million times\n", id);

	// Close the Handles:
	if (firstMutex != NULL)
	{
		CloseHandle(firstMutex);
	}
	if (lastMutex != NULL)
	{
		CloseHandle(lastMutex);
	}
}