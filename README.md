# runsc

Run shellcode in a debugger

Load runsc.exe in Olly (or a debugger of your choice), make sure you catch INT 3,
set the command line argument to a file containging shellcode and hit run. The dbugger
should catch the exception and you can go from there.
