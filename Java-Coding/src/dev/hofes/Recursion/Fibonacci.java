package dev.hofes.Recursion;

public class Fibonacci {
    public static int main(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return main(n - 1) + main(n - 2);
    }
}