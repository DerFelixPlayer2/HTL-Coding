package dev.hofes.FSST.other;

public class GoldbachscheVermutung {
    public static void main(String[] args) {

        boolean ersterCheck;
        boolean zweiterCheck;
        int erstePrim = 2;
        int zweitePrim;

        for (int n = 4; n <= 1000; n += 2)
            w1:while (erstePrim < 1000 - 2) {
                ersterCheck = isPrime(erstePrim);
                if (ersterCheck) {
                    zweitePrim = 2;
                    while (zweitePrim < n) {
                        zweiterCheck = isPrime(zweitePrim);
                        if (zweiterCheck) {
                            if (erstePrim + zweitePrim == n) {
                                System.out.println(erstePrim + " + " + zweitePrim + " = " + n);
                                break w1;
                            }
                        }
                        zweitePrim++;
                    }
                }
                erstePrim++;
            }

    }

    private static boolean isPrime(int num) {
        for (int i = 2; i <= num / 2; ++i)
            if (num % i == 0)
                return false;
        return true;
    }
}