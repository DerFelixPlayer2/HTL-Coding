package dev.hofes.Recursion;

public class Factorial {
    public static int main(int v) {
        if (v <= 1) return 1;
        return main(v - 1) * v;
    }
}