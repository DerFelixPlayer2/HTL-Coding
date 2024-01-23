package dev.hofes.Arrays;

import java.util.ArrayList;

public class PrimeFactors {
    public static int[] main(int n) {
        if (n <= 0) throw new IllegalArgumentException("Expected positive integer, got " + n);

        ArrayList<Integer> list = new ArrayList<>();
        for (int i = 2; i < n; i++)
            for (; n % i == 0; n /= i)
                list.add(i);
        list.add(n);

        return list.stream().mapToInt(i -> i).toArray();
    }
}