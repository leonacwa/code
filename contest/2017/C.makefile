objects:= C.cpp
app:= C.exe
in:=C.in
ans:=C.ans
all:${app}
	-${app} < ${in}
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
