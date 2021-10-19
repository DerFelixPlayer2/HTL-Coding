package de.lolgamr17.random;

public class PrimeSiblings {
    public static void main(String[] args) {
        int s = 0;
        for (int i = 0; i < 100000; i++)
            if (isPrime(i))
                if (isPrime(i + 2))
                    s++;
        System.out.println(s);

        for (int i = 0; i < 100000; i++)
            if (isPrime(i))
                if (isPrime(i + 2))
                    if (((i + 1) % 6) != 0) {
                        System.out.println("FALSE: " + i + " " + (i + 2));
                    }

    }

    private static boolean isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= Math.sqrt(n); i++)
            if (n % i == 0)
                return false;
        return true;
    }
}