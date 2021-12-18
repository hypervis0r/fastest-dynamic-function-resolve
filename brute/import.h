#include <Windows.h>
#include <stdint.h>

uint64_t hash_string_djb2(char* str);
void *GetProcAddressWithHash(PVOID pModuleBase, uint64_t hash);