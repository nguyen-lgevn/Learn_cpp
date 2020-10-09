CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libhello.so

libhello.so : HelloJNICpp.o
	g++ -fPIC -shared -o $@ $<

HelloJNICpp.o : HelloJNI.cpp HelloJNICpp.class  #HelloJNICpp.h
	g++ -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c -fPIC  $< -o $@

#HelloJNICpp.h : HelloJNICpp.class
#	echo $*
#	javac -classpath $(CLASS_PATH) $*

HelloJNICpp.class:
	javac -h . HelloJNICpp.java

clean:
	rm HelloJNICpp.h HelloJNICpp.o libhello.so HelloJNICpp.class
