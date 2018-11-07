CC		= g++
C		= cpp
H		= h

CFLAGS		= -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lGLU -lm
  endif
endif

PROJECT		= tree

${PROJECT}:	${PROJECT}.${C}
	${CC} ${CFLAGS} -o ${PROJECT} ${PROJECT}.${C} ${OBJS} ${LDFLAGS}

clean:
	rm -f core.* *.o *~ ${PROJECT}
	rm -rf *.dSYM