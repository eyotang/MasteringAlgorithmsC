TARGET = test_list
all:$(TARGET)

CXX = g++
CXX_FLAGS = -g
LIBS = 
INCS=-I./

LIBS += -lgtest_main -lgtest -lpthread
CXX_FLAGS += -DUNIT_TEST


OBJS = test_list.o list.o

$(TARGET):$(OBJS)
	$(CXX) $(CXX_FLAGS) $(LIBS) -o $(TARGET) $(OBJS)

.c.o:
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf $(TARGET)
	rm -rf *.o *.a *.la
