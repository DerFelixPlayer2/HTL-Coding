package dev.hofes.Recursion;

public class SumDigits {
    public static int main(int n) {
        if (n / 10 == 0) return n;
        return n % 10 + main(n / 10);
    }
}