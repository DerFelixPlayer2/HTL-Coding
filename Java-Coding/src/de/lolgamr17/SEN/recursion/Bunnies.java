package de.lolgamr17.recursion;

public class Bunnies {
    public static int main(int v) {
        if (v == 0) return 0;
        return v % 2 == 0 ? main(v - 1) + 3 : main(v - 1) + 2;
    }
}