package dev.hofes.FSST.arrays;

import org.jetbrains.annotations.NotNull;

public class SimpleSearch {
    public static int main(int @NotNull [] a, int x) {
        int i;
        for (i = 0; i < a.length && a[i] != x; i++) ;
        if (i >= a.length) return -1;
        return i;
    }
}