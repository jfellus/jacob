all: control

control: bin/main.o
	g++ -o $@ $^

bin/%.o: %.cpp
	mkdir -p `dirname $@`
	g++ -o $@ -c $<
