name :=  1001
CC := g++
objects := ${name}.cpp
in := ${name}.in
out := ${name}.out
app := ${name}.exe

all: ${app}
	./${app} < ${in}


${app} : ${objects}
	${CC} -o ${app} ${objects}
