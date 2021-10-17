package de.lolgamr17.recursion;

import org.jetbrains.annotations.NotNull;

public class Array11 {
    public static int main(int @NotNull [] arr, int i) {
        if (i == arr.length - 1) return arr[i] == 11 ? 1 : 0;
        return main(arr, i + 1) + (arr[i] == 11 ? 1 : 0);
    }

    public static int main(int @NotNull [] arr) {
        return main(arr, 0);
    }
}