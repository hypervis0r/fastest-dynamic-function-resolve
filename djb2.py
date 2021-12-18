from ctypes import c_uint64

def hash_djb2(s):    
   hash = 0x1337133713371337
   for x in s:
      hash = (( hash << 5) + hash) + ord(x)
   return c_uint64(hash)

lines = [
    "NtOpenProcess",
"NtMapViewOfSection",
"NtCreateFile",
"NtAllocateVirtualMemory",
"NtCreateSection",
"LdrLoadDll"]

for name in lines:
   print(name + ": " + str(hex(hash_djb2(name).value)))