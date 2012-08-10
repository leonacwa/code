objects:= D.cpp
app:= D.exe
in:=D.in
ans:=D.ans
all:${app}
	-${app} < ${in} 
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
