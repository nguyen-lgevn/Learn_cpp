# CMake generated Testfile for 
# Source directory: /home/pearl/workspace/Learn_cpp/jni/02_javacpp
# Build directory: /home/pearl/workspace/Learn_cpp/jni/02_javacpp/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestHelloJNICpp "/usr/lib/jvm/java-9-oracle/bin/java" "-Djava.library.path=/home/pearl/workspace/Learn_cpp/jni/02_javacpp/build" "-cp" "/home/pearl/workspace/Learn_cpp/jni/02_javacpp/build/HelloJNICpp.jar" "HelloJNICpp")
set_tests_properties(TestHelloJNICpp PROPERTIES  _BACKTRACE_TRIPLES "/home/pearl/workspace/Learn_cpp/jni/02_javacpp/CMakeLists.txt;40;add_test;/home/pearl/workspace/Learn_cpp/jni/02_javacpp/CMakeLists.txt;0;")
