package dev.hofes.FSST.other;

import java.util.Arrays;

public class SiebDesEratosthenes {
    private static final boolean[] values = new boolean[10000];

    public static void main(String[] args) {
        Arrays.fill(values, true);

        for (int i = 2; i < values.length; i++)
            if (values[i] && isPrime(i))
                for (int j = i; j < values.length; j++)
                    if (j % i == 0)
                        values[j] = false;

        int c = 0;
        for (int i = 2; i < values.length; i++) {
            if (values[i]) {
                System.out.println(i);
                c++;
            }
        }

        System.out.println(c);
    }

    private static boolean isPrime(int num) {
        for (int i = 2; i <= num / 2; ++i)
            if (num % i == 0)
                return true;
        return false;
    }
}