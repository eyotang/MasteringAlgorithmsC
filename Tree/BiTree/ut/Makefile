CC = gcc  
CPP = g++  
LINK = g++  
CFLAGS = -g -Wall -Werror -Wextra -std=gnu99  
CPPFLAGS = -g -Wall -Werror -Wextra  
LIBS = -lgtest_main -lgtest -lpthread 
      
      
C__SOURCES = $(wildcard *.c)  
CPPSOURCES = $(wildcard *.cpp)  
OBJECTS = $(patsubst %.c, %.o, $(C__SOURCES)) $(patsubst %.cpp, %.o, $(CPPSOURCES))  
TARGET = test_job
      
      
first: all  
      
      
%.o: %.c  
	$(CPP) -c $(CPPFLAGS) -o $@ $<  
      
      
%.o: %.cpp  
	$(CPP) -c $(CPPFLAGS) -o $@ $<  
      
      
all: $(TARGET)  
      
      
$(TARGET): $(OBJECTS)  
	$(LINK) $(CPPFLAGS) $(LIBS) -o $(TARGET) $(OBJECTS)  
      
      
.PHONY: clean  
      
      
clean:  
	rm -f $(TARGET) $(OBJECTS)  
