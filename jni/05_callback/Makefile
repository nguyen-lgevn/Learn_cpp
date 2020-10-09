CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libmyjni.so

libmyjni.so : JNIInstance.o
	g++ -fPIC -shared -o $@ $<

JNIInstance.o : JNIInstance.cpp JNIInstance.h
	g++ -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c -fPIC  $< -o $@

JNIInstance.h : JNIInstance.class
	echo $*
	javah -classpath $(CLASS_PATH) $*

JNIInstance.class:
	javac -h . JNIInstance.java

clean:
	rm JNIInstance.h JNIInstance.o libmyjni.so JNIInstance.class
