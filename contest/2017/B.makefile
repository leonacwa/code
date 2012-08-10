objects:= B.cpp
app:= B.exe
in:=B.in
ans:=B.ans
all:${app}
	-${app} < ${in}
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
