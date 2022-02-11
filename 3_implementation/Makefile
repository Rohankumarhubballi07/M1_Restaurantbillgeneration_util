#Target_name : Dependencies
#<TAB>command

SRC= restaurant.c productioninvoice.c
INC= headder.h

#CXX= cpp
#CC= gcc
#AS= as
#LD= ld

SRC=src
INC=inc


CFLAGS = -I$(INC)
#-DMACRO=value
#-g
#-v

#ASFLAGS
all.out : S$(SRC) $(INC)
	gcc $^ -I$(INC) -o $@


run: target
	./a.out

clean:
	rm all.out
