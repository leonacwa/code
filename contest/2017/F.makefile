objects:= F.cpp
app:= F.exe
in:=F.in
ans:=F.ans
all:${app}
	-${app} < ${in} 
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
