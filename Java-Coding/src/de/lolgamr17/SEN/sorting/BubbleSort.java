package de.lolgamr17.sorting;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

public class BubbleSort {
    public static void sort(int @NotNull [] array) {
        System.out.println("---- vor BubbleSort ----");
        System.out.println(Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));

        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array.length - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
            System.out.println((i + 1) + ". Durchlauf: " + Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));
        }

        System.out.println("---- nach BubbleSort ----");
        System.out.println(Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));
    }

    public static void main(String[] args) {
        int[] values = {5, 2, 4, 6, 1, 3};
        sort(values);
    }

}