CC:=g++
objects:=F.cpp
all:F.exe
	F.exe < data.in
F.exe:${objects}
	${CC} -o F.exe ${objects}

.PHONY:clean
clean:
	-rm *.exe 
	-rm *.o
