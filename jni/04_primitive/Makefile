CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libmyjni.so

libmyjni.so : JNIPrimitive.o
	g++ -fPIC -shared -o $@ $<

JNIPrimitive.o : JNIPrimitive.cpp JNIPrimitive.class
	g++ -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c -fPIC  $< -o $@

JNIPrimitive.h : JNIPrimitive.class
	javah -classpath $(CLASS_PATH) $*

JNIPrimitive.class:
	javac -h . JNIPrimitive.java

clean:
	rm JNIPrimitive.class JNIPrimitive.h JNIPrimitive.o
