#pragma once

#include "hash_table.h"
#include <Windows.h>

struct hash_table* LoadExportsIntoTable(PVOID pModuleBase);