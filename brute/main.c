#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "import.h"

#define HASH_MESSAGEBOXA 0xff6fbc9e23f38fa6
#define HASH_NTOPENPROCESS 0xbb37f620b6b2bfca
#define HASH_NTMAPVIEWOFFILE  0xa2fd2cb0c3f1901c
#define HASH_NTCREATEFILE  0xee64935975d9c60d
#define HASH_NTALLOCATEVIRTUALMEMORY  0xb5a8bda23b96393e
#define HASH_NTCREATEFILEMAPPING  0x54b0c15c9e9ac4c2
#define HASH_LDRLOADDLL  0x45cce9a819afbfd5

#define TRIAL_COUNT 100

double get_time()
{
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
	return ((double)t.QuadPart / (double)f.QuadPart);
}

int main(void)
{
	HMODULE hNtdll = LoadLibraryA("ntdll.dll");
	
	double average = 0.;

	for (int i = 0; i < TRIAL_COUNT; i++)
	{
		double start_time = get_time();

		void* NTOPENPROCESS = GetProcAddressWithHash(hNtdll, HASH_NTOPENPROCESS);
		void* NTMAPVIEWOFFILE = GetProcAddressWithHash(hNtdll, HASH_NTMAPVIEWOFFILE);
		void* NTCREATEFILE = GetProcAddressWithHash(hNtdll, HASH_NTCREATEFILE);
		void* NTALLOCATEVIRTUALMEMORY = GetProcAddressWithHash(hNtdll, HASH_NTALLOCATEVIRTUALMEMORY);
		void* NTCREATEFILEMAPPING = GetProcAddressWithHash(hNtdll, HASH_NTCREATEFILEMAPPING);
		void* LDRLOADDLL = GetProcAddressWithHash(hNtdll, HASH_LDRLOADDLL);

		double elapsed_time = (double)(get_time() - start_time);

		average += elapsed_time;

		printf("Trial %d:\n", i);
		printf("[*] %p\n", NTOPENPROCESS);
		printf("[*] %p\n", NTMAPVIEWOFFILE);
		printf("[*] %p\n", NTCREATEFILE);
		printf("[*] %p\n", NTALLOCATEVIRTUALMEMORY);
		printf("[*] %p\n", NTCREATEFILEMAPPING);
		printf("[*] %p\n", LDRLOADDLL);
		printf("[+] Elapsed time: %.10f seconds\n", elapsed_time);
	}

	average = average / TRIAL_COUNT;

	printf("\n\nBrute:\n\n");
	printf("[+] Average elapsed Time: %.10f seconds\n", average);
}