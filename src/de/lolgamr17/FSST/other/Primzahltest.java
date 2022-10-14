package de.lolgamr17.FSST.other;

import java.util.Scanner;

public class Primzahltest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            int in = scanner.nextInt();

            if (!isPrime(in)) System.out.println(in + " is a prime number.");
            else System.out.println(in + " is not a prime number.");
        }
    }

    private static boolean isPrime(int num) {
        for (int i = 2; i <= num / 2; ++i)
            if (num % i == 0)
                return true;
        return false;
    }
}