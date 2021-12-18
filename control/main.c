#include <Windows.h>
#include <stdio.h>

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

		void* NTOPENPROCESS = GetProcAddress(hNtdll, "NtOpenProcess");
		void* NTMAPVIEWOFFILE = GetProcAddress(hNtdll, "NtMapViewOfSection");
		void* NTCREATEFILE = GetProcAddress(hNtdll, "NtCreateFile");
		void* NTALLOCATEVIRTUALMEMORY = GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
		void* NTCREATEFILEMAPPING = GetProcAddress(hNtdll, "NtCreateSection");
		void* LDRLOADDLL = GetProcAddress(hNtdll, "LdrLoadDll");

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

	printf("\n\nGetProcAddress:\n\n");
	printf("[+] Average elapsed Time: %.10f seconds\n", average);
}