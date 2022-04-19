package de.lolgamr17.interfaces;

import org.jetbrains.annotations.NotNull;

public class Fraction implements Comparable<Fraction> {
    public final int numerator;
    public final int denominator;

    public Fraction(int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
    }

    @Override
    public int compareTo(@NotNull Fraction o) {
        return (int) Math.signum(this.numerator * o.denominator - this.denominator * o.numerator);
    }

    @Override
    public String toString() {
        return numerator + " / " + denominator;
    }
}