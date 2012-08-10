objects:= E.cpp
app:= E.exe
in:=E.in
ans:=E.ans
all:${app}
	-${app} < ${in} 
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
