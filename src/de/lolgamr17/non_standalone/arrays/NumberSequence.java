package de.lolgamr17.non_standalone.arrays;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.Nullable;

public class NumberSequence {
    @Contract(pure = true)
    public static int @Nullable [] main(int len) {
        if (len <= 0) return null;
        if (len == 1) return new int[]{1};
        if (len == 2) return new int[]{1, 2};
        
        int[] arr = new int[len];
        arr[0] = 1;
        arr[1] = 2;

        for (int i = 2; i < len; i++)
            arr[i] = arr[i - 1] * arr[i - 2];
        return arr;
    }
}