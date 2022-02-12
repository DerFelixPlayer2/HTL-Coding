package de.lolgamr17.random;

public class PrimzahltestII {
    public static void main(String[] args) {
        int c = 0;
        long t = System.currentTimeMillis();
        for (int i = 2; i < 100000; i++) {
            if (isPrime(i)) c++;
        }
        System.out.println(c);
        System.out.println("Took " + (System.currentTimeMillis() - t) + "ms");
    }

    private static boolean isPrime(int num) {
        for (int i = 2; i <= num / 2; ++i)
            if (num % i == 0)
                return false;
        return true;
    }

    // TODO: 5.1d (Primzahlen II)
}