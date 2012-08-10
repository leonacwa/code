objects:= sample.cpp
app:= A.exe
in:=A.in
ans:=A.ans
all:${app}
	-${app} < ${in}
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
