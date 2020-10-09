CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libmyjni.so

libmyjni.so : JNIObjArray.o
	g++ -fPIC -shared -o $@ $<

JNIObjArray.o : JNIObjArray.cpp JNIObjArray.h
	g++ -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c -fPIC  $< -o $@

JNIObjArray.h : JNIObjArray.class
	echo $*
	javah -classpath $(CLASS_PATH) $*

JNIObjArray.class:
	javac -h . JNIObjArray.java

clean:
	rm JNIObjArray.h JNIObjArray.o libmyjni.so JNIObjArray.class
