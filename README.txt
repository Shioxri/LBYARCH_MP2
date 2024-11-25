copy paste to compile and run
> nasm -f win64 MP2SASM.asm
> gcc -c MP2C.c -o MP2C.obj -m64
> gcc MP2C.obj MP2SASM.obj -o MP2C.exe -m64
> MP2C.exe
