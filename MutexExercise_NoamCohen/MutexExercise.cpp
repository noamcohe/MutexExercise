#include "pch.h"


// Name of file that we will run:
#define EXE_FILENAME "C:\\Operating Systems\\MutexExercise_NoamCohen\\Debug\\SinglePhilosopherExercise.exe"

// Amount of the processes that will be create:
#define NUM_PROCESSES 5

// size of CHAR in a INT type, for 'sprintf_s'
// 1 byte to the digit, and 1 to NULL character:
#define SIZE 2


INT main()
{
	// Measuring time:
	clock_t initialTime = clock();

	// Array of Mutexes:
	HANDLE hMutexes[NUM_PROCESSES];

	// length is increased by 3:
	// space character- 1 byte, one digit number- 1 byte, string NULL terminator- 1 byte
	INT size = strlen(EXE_FILENAME) + 3;

	// The param that will send to 'CreateProcessA':
	PCHAR param = (PCHAR)calloc(size, sizeof(CHAR));

	// Pointer to CHAR type, that will help in Create Mutexes:
	PCHAR buffer = (PCHAR)calloc(SIZE, sizeof(CHAR));

	// Create 5 Mutexes:
	for (INT i = 0; i < NUM_PROCESSES; i++)
	{
		// convert 'i' to string type and put in 'buffer':
		if (buffer != NULL)
		{
			sprintf_s(buffer, SIZE, "%d", (i + 1));
		}

		// Create new Mutex:
		hMutexes[i] = CreateMutexA(NULL, FALSE, buffer);
	}

	STARTUPINFOA si;
	PROCESS_INFORMATION pi[NUM_PROCESSES];

	for (INT i = 0; i < NUM_PROCESSES; i++)
	{
		if (param != NULL)
		{
			sprintf_s(param, size, "%s %d", EXE_FILENAME, (i + 1));
		}

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi[i], sizeof(pi[i]));

		CreateProcessA(
			NULL,
			param,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi[i]
		);
	}

	// Wait for every process to finish, close everything before return
	for (INT i = 0; i < NUM_PROCESSES; i++)
	{
		WaitForSingleObject(pi[i].hProcess, INFINITE);
	}

	// Release all Mutexes and close all handles:
	for (INT i = 0; i < NUM_PROCESSES; i++)
	{
		if (hMutexes[i] != NULL)
		{
			ReleaseMutex(hMutexes[i]);
		}
	}

	// Close all Handles:
	for (INT i = 0; i < NUM_PROCESSES; i++)
	{
		CloseHandle(pi[i].hThread);
		CloseHandle(pi[i].hProcess);
		if (hMutexes[i] != NULL)
		{
			CloseHandle(hMutexes[i]);
		}
	}

	free(param);
	free(buffer);

	clock_t currentTime = clock();
	FLOAT deltaSec = FLOAT(currentTime - initialTime) / CLOCKS_PER_SEC;
	printf("run time: %f sec\n", deltaSec);

	return 0;
}