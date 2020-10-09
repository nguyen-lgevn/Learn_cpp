public class JNIPrimitive {
    static {
        System.loadLibrary("myjni");
    }

    private native double average(int n1, int n2);
    private native String sayHello(String msg);
    private native double[] sumAndAverage(int[] numbers);

    public static void main(String[] args) {
        System.out.println("In Java, the average is " + new JNIPrimitive().average(3, 2));

        String result = new JNIPrimitive().sayHello("Hello from Java");
        System.out.println("In Java, the returned string is: " + result);

        int[] numbers = {22, 33, 55};
        double[] results = new JNIPrimitive().sumAndAverage(numbers);
        System.out.println("In Java, the sum is " + results[0]);
        System.out.println("In Java, the average is " + results[1]);
    }
}
