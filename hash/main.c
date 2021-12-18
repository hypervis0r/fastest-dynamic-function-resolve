#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table.h"
#include "import.h"

#define HASH_MESSAGEBOXA 0xff6fbc9e23f38fa6
#define HASH_NTOPENPROCESS 0xbb37f620b6b2bfca
#define HASH_NTMAPVIEWOFFILE  0xa2fd2cb0c3f1901c
#define HASH_NTCREATEFILE  0xee64935975d9c60d
#define HASH_NTALLOCATEVIRTUALMEMORY  0xb5a8bda23b96393e
#define HASH_NTCREATEFILEMAPPING  0x54b0c15c9e9ac4c2
#define HASH_LDRLOADDLL  0x45cce9a819afbfd5

#define TRIAL_COUNT 30

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

		struct hash_table* table = LoadExportsIntoTable(hNtdll);
		if (table == NULL)
			return -1;

		void* NTOPENPROCESS = hash_table_search(table, HASH_NTOPENPROCESS);
		void* NTMAPVIEWOFFILE = hash_table_search(table, HASH_NTMAPVIEWOFFILE);
		void* NTCREATEFILE = hash_table_search(table, HASH_NTCREATEFILE);
		void* NTALLOCATEVIRTUALMEMORY = hash_table_search(table, HASH_NTALLOCATEVIRTUALMEMORY);
		void* NTCREATEFILEMAPPING = hash_table_search(table, HASH_NTCREATEFILEMAPPING);
		void* LDRLOADDLL = hash_table_search(table, HASH_LDRLOADDLL);

		//free_hash_table(table);

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
	
	printf("\n\nHash Table:\n\n");
	printf("[+] Average elapsed Time: %.10f seconds\n", average);
}