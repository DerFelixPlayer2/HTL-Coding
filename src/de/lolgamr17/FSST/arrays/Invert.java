package de.lolgamr17.arrays;

import org.jetbrains.annotations.NotNull;

public class Invert {
    public static void main(int @NotNull [] arr) {
        for (int i = 0; i < arr.length / 2; i++) {
            int temp = arr[i];
            arr[i] = arr[arr.length - i - 1];
            arr[arr.length - i - 1] = temp;
        }
    }
}