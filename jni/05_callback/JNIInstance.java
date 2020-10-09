public class JNIInstance {
    static {
        System.loadLibrary("myjni");
    }

    private int number = 88;
    private String message = "Hello from Java";

    private static double dNumber = 55.66;

    // Declare native methods
    private native void modifyInstanceVariable();
    private native void modifyStaticVariable();

    private native void nativeMethod();

    private void callback() {
        System.out.println("In Java");   
    }

    private void callback(String message) {
        System.out.println("In Java with " + message);   
    }

    private double callbackAverage(int n1, int n2) {
        return ((double)n1 + n2) / 2.0;
    }

    private static String callbackStatic() {
        return "From static Java method";
    }

    public static void main(String[] args) {    
        JNIInstance test = new JNIInstance();
        test.modifyInstanceVariable();
        System.out.println("In Java, int is " + test.number);
        System.out.println("In Java, String is " + test.message);
        test.modifyStaticVariable();
        System.out.println("In Java, double is " + test.dNumber);

        test.nativeMethod();
    }
}
