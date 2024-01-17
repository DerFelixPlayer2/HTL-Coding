package de.lolgamr17.recursion;

public class SumDigits {
    public static int main(int n) {
        if (n / 10 == 0) return n;
        return n % 10 + main(n / 10);
    }
}