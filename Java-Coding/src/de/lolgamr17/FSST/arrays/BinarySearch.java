package de.lolgamr17.FSST.arrays;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class BinarySearch {
    @Contract(pure = true)
    public static int main(int @NotNull [] a, int x) {
        int low = 0;
        int high = a.length - 1;
        while (low <= high) {
            int m = (low + high) / 2;
            if (a[m] == x) return m;
            else if (x > a[m]) low = m + 1;
            else high = m - 1;
        }
        return -1;
    }
}