package de.lolgamr17.recursion;

public class PowerN {
    public static int main(int base, int exp) {
        if (exp == 1) return base;
        return main(base, exp - 1) * base;
    }
}