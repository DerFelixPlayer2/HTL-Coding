package dev.hofes;

import java.util.Scanner;

public class PrimzahlTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            int in = scanner.nextInt();

            if (!isPrime(in)) System.out.println(in + " is a prime number.");
            else System.out.println(in + " is not a prime number.");
        }
    }

    public static void main2(String[] args) {
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
                return true;
        return false;
    }
}