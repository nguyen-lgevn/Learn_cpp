CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libmyjni.so

libmyjni.so : JNIReferences.o
	g++ -fPIC -shared -o $@ $<

JNIReferences.o : JNIReferences.cpp JNIReferences.class
	g++ -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c -fPIC  $< -o $@

JNIReferences.h : JNIReferences.class
	echo $*
	javah -classpath $(CLASS_PATH) $*

JNIReferences.class:
	javac -h . JNIReferences.java

clean:
	rm JNIReferences.h JNIReferences.o libmyjni.so JNIReferences.class
