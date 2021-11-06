package de.lolgamr17.non_standalone.arrays;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;

public class Split {
    @Contract(pure = true)
    public static int @NotNull [] main(int s, int n) {
        if (s < 1) throw new IllegalArgumentException("Expected positive integer (>= 1), got " + s);
        if (n < 1) throw new IllegalArgumentException("Expected positive integer (>= 1), got " + n);

        int v = s;
        int[] r = new int[s];

        for (int i = 0; v > 0; i++) {
            if (v >= n) {
                v -= n;
                r[i] = n;
            } else break;
        }
        if (v == 0) return trim(r);

        int j = Math.abs(n - v);
        if (j >= count(r)) return main(s, n - 1);
        for (int i = 0; i < j; i++) {
            r[i]--;
            v++;
        }
        r[r.length - 1] = v;

        return trim(r);
    }

    private static int @NotNull [] trim(int @NotNull [] arr) {
        ArrayList<Integer> list = new ArrayList<>();
        for (int v : arr)
            if (v > 0) list.add(v);
        return list.stream().mapToInt(i -> i).toArray();
    }

    private static int count(int @NotNull [] arr) {
        int i = 0;
        for (int v : arr)
            if (v > 0) i++;
        return i;
    }
}