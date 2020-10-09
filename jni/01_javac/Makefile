CLASS_PATH = .

vpath %.class ${CLASS_PATH}

all : libhello.so

libhello.so : HelloJNI.o
	gcc -shared -o $@ $<

HelloJNI.o : HelloJNI.c HelloJNI.h
	gcc -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" -c $< -o $@

HelloJNI.h : HelloJNI.class
	javah -classpath $(CLASS_PATH) $*

clean:
	rm HelloJNI.h HelloJNI.o libhello.so
