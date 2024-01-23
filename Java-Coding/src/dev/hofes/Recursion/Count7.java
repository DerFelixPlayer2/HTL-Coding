package dev.hofes.Recursion;

public class Count7 {
    public static int main(int n) {
        if (n == 7) return 1;
        else if (n / 10 == 0) return 0;
        return main(n / 10) + (n % 10 == 7 ? 1 : 0);
    }
}