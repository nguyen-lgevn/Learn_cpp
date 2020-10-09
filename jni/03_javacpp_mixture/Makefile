CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libhello.so

libhello.so : HelloJNICpp.o HelloJNICppImpl.o
	g++ -fPIC -shared -o $@ $^

HelloJNICppImpl.o : HelloJNICppImpl.cpp HelloJNICppImpl.h
	g++ -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c $< -o $@

HelloJNICpp.o : HelloJNICpp.c HelloJNICpp.h
	g++ -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c $< -o $@

HelloJNICpp.h : HelloJNICpp.class
	javac -h . HelloJNICpp.java
#	javah -classpath $(CLASS_PATH) $*

clean:
	rm HelloJNICpp.h HelloJNICpp.o HelloJNICppImpl.o libhello.so
