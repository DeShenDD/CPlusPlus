CCMAKE=g++

SRC=$(wildcard src/*cpp)
OBJS=$(patsubst %cpp, %o, $(SRC))

ClientSRC=$(wildcard sampleApp/*cpp)

FLAGS= -Wall -g -std=c++11 
SHARED=-shared -fPIC

LIBS= -I./include

TARGET=libcmd.so

Client=client

all:$(TARGET)


$(TARGET):$(OBJS)
	$(CCMAKE) $(SHARED) -o $@ $^
$(OBJS):%.o:%.cpp
	$(CCMAKE) -c $(LIBS) $(FLAGS) $(SHARED) $< -o $@

$(Client):$(ClientSRC)
	$(CCMAKE) $(ClientSRC) $(LIBS)  -L./ -lcmd -o $@

clean:
	rm $(Client) $(TARGET)
