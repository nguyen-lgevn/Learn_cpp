public class JNIReferences {
    static {
        System.loadLibrary("myjni");
    }

    private native Integer getFooIntegerObject(int number);

    private native Integer getBarIntegerObject(int number);

    public static void main (String args[])
    {
        JNIReferences ref = new JNIReferences();
        System.out.println(ref.getFooIntegerObject(1));
        System.out.println(ref.getFooIntegerObject(2));
        System.out.println(ref.getBarIntegerObject(3));
    }
}
