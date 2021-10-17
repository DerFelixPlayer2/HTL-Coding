package de.lolgamr17.recursion;

public class Fakultaet {
    public static void main(String[] args) {
        int l = 12;

        int[] a = new int[l + 1];
        for (int i = 0; i < l + 1; i++) {
            a[i] = fact(i);
        }

        for (int i = l; i > 0; i--) {
            System.out.print(a[i] + ", ");
        }
        System.out.print(a[0]);
    }

    private static int fact(int x) {
        if (x <= 0) return 1;
        return fact(x - 1) * x;
    }
}