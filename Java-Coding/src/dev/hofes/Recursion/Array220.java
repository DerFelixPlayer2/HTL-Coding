package dev.hofes.Recursion;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Array220 {
    @Contract(pure = true)
    public static boolean main(int @NotNull [] arr, int i) {
        if (arr.length <= 1) return false;
        if (arr.length - 2 <= i) return arr[i] * 10 == arr[i + 1];
        return (arr[i] * 10 == arr[i + 1]) || main(arr, i + 1);
    }

    public static boolean main(int @NotNull [] arr) {
        return main(arr, 0);
    }
}