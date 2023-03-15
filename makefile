###################{ makefile }###################
SRC = $(shell find src/ -type f -name '*.cpp') 

OBJ = $(SRC:.cpp=.o)

CC = x86_64-w64-mingw32-g++
CCL = g++ 

NAME = GUR
FILE_EXT = 
BOOT_PARAM = 

FLAGS = -Wall -static-libstdc++ -static-libgcc -std=c++20 -fcoroutines -lcurl -ljsoncpp
DANGEROUSFLAGS = -fpermissive
SUBSRC =

all: $(NAME) # /make

$(NAME):
	$(CCL) -o "$(NAME)$(FILE_EXT)" $(SRC) $(SUBSRC) $(FLAGS) $(DANGEROUSFLAGS)
    
clean:
	rm -f $(OBJ) 

fclean: 
	rm -f "$(NAME)$(FILE_EXT)"

rcfile:
	x86_64-w64-mingw32-windres "$(NAME).rc" -O coff -o  "$(NAME).res"

re: fclean $(NAME)

#linux only
try:
	$(NAME) $(BOOT_PARAM)

norc: fclean
	$(CC) -o "$(NAME).exe" $(SRC) $(FLAGS) $(DANGEROUSFLAGS)