# CC = gcc
# CFLAGS = -Wall -O2
# TARGET = sat_solverRB

# build: $(TARGET)

# $(TARGET): sat_solverRB.c
# 	$(CC) $(CFLAGS) -o $(TARGET) sat_solverRB.c

# run:
# 	./$(TARGET) $(INPUT) $(OUTPUT)

# clean:
# 	rm -f $(TARGET)

CC = g++
CFLAGS = -Wall -O2
TARGET = sat_solver

build: $(TARGET)

$(TARGET): sat_solver.cpp
	$(CC) $(CFLAGS) -o $(TARGET) sat_solver.cpp

run:
	./$(TARGET) $(INPUT) $(OUTPUT)

clean:
	rm -f $(TARGET)
