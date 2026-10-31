INC := inc
SRC := src
OBJ := obj
LIB := lib
APP := app
CC := gcc
CFLAGS :=  -Wall -Wextra -g
CPPFLAGS := -I$(INC)
all: $(APP)/app_static $(APP)/app_dynamic
# Tao thu muc dau ra
obj lib app:
	mkdir -p $@
# Tao object file
$(OBJ)/%.o: $(SRC)/%.c $(INC)/hello.h |$(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
# Tao obj file voi -fPIC
$(OBJ)/hello_pic.o: $(SRC)/hello.c $(INC)/hello.h |$(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@
# Tao thu vien
$(LIB)/libhello.a: $(OBJ)/hello.o |$(LIB)
	ar rcs $@ $<
$(LIB)/libhello.so: $(OBJ)/hello_pic.o |$(LIB)
	$(CC)  -shared -o $@ $<
#Link chuong trinh voi static lib
$(APP)/app_static: $(OBJ)/main.o $(LIB)/libhello.a |$(APP)
	$(CC) $^ -o $@
$(APP)/app_dynamic: $(OBJ)/main.o $(LIB)/libhello.so |$(APP)
	$(CC) $< -L$(LIB) -lhello -o $@
clean:
	rm -rf $(OBJ) $(LIB) $(APP)
.PHONY : all clean



