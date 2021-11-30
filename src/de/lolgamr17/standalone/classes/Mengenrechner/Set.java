package de.lolgamr17.standalone.classes.Mengenrechner;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;

public class Set {
    private final boolean[] values;

    Set() {
        values = new boolean[16];
    }

    Set(int @NotNull [] values) {
        if (values.length > 16) throw new IllegalArgumentException("Set cannot be longer than 16!");
        this.values = new boolean[16];
        for (int v : values) {
            if (v < 0 || v > 15) throw new IllegalArgumentException("Set cannot contain values < 0 or > 15!");
            this.values[v] = true;
        }
    }

    @NotNull Set duplicate() {
        Set s = new Set();
        System.arraycopy(this.values, 0, s.values, 0, this.values.length);
        return s;
    }

    static @NotNull Set readSet() {
        Scanner sc = new Scanner(System.in);
        Set s = new Set();
        int v;
        while (true) {
            System.out.print("Bitte geben Sie eine Zahl ein: ");
            v = sc.nextInt();
            if (v == -1)
                break;
            s.values[v] = true;
        }
        return s;
    }

    static @NotNull Set union(@NotNull Set s1, @NotNull Set s2) {
        Set s = s1.duplicate();
        s.union(s2);
        return s;
    }

    static @NotNull Set intersect(@NotNull Set s1, @NotNull Set s2) {
        Set s = s1.duplicate();
        s.intersect(s2);
        return s;
    }

    static @NotNull Set diff(@NotNull Set s1, @NotNull Set s2) {
        Set s = s1.duplicate();
        s.diff(s2);
        return s;
    }

    boolean contains(int v) {
        return this.values[v];
    }

    void union(@NotNull Set s) {
        for (int i = 0; i < s.values.length; i++)
            if (s.values[i])
                this.values[i] = true;
    }

    void intersect(@NotNull Set s) {
        for (int i = 0; i < s.values.length; i++)
            if (!s.values[i])
                this.values[i] = false;
    }

    void diff(@NotNull Set s) {
        for (int i = 0; i < s.values.length; i++)
            if (s.values[i])
                this.values[i] = false;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{ ");
        for (int i = 0; i < values.length; i++)
            if (values[i])
                sb.append(i).append(" ");
        sb.append("}");
        return sb.toString();
    }
}