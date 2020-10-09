public class JNIObjArray {
    static {
        System.loadLibrary("myjni");
    }

    private native Integer getIntegerObject(int number);
    private native Double[] sumAndAverage(Integer[] numbers);

    public static void main(String[] args) {    
        JNIObjArray test = new JNIObjArray();
        System.out.println("In Java, the number is " + test.getIntegerObject(9999));

        Integer[] numbers = {11, 22, 32};
        Double[] result = test.sumAndAverage(numbers);
        System.out.println("In Java, the sum is " + result[0]);
        System.out.println("In Java, the average is " + result[1]);
    }
}
