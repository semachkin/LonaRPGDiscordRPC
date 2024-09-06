DLL = lonarpg_rpc.dll
GCC = i686-w64-mingw32-gcc

MASK = LonaMouseWheel.dll

FLAGS := -Wall -m32

entry:
	$(GCC) $(FLAGS) -c dllmain.c
	$(GCC) $(FLAGS) -shared dllmain.o -o $(MASK)
	@del $(DLL)
	@ren $(MASK) $(DLL)
	@del dllmain.o