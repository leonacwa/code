objects:= G.cpp
app:= G.exe
in:=G.in
ans:=G.ans
all:${app}
	-${app} < ${in} 
${app}:${objects}
	g++ -o ${app} ${objects} 
.PHONY:clean
clean:
	-rm ${app}
