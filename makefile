# Makefile for building tests application

OUT_DIR     = ./build
CC          = g++
SOURCE_LIB  = LoggingPulseCounterBase.cpp
SOURCE_TEST = test.cpp
OUT_APP     = test
INCLUDES	= ./


build: clean
	mkdir $(OUT_DIR)
	$(CC) $(SOURCE_TEST) $(SOURCE_LIB) -I$(INCLUDES) -o $(OUT_DIR)/$(OUT_APP)

clean:
	rm -rf $(OUT_DIR)