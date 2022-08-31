package de.lolgamr17.recursion;

public class Triangle {
    public static int main(int n) {
        if (n == 0) return 0;
        return main(n - 1) + n;
    }
}