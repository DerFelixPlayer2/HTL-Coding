package dev.hofes.SEN.sorting;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

public class SelectSort {
    public static void sort(int @NotNull [] array) {
        System.out.println("---- vor SelectSort ----");
        System.out.println(Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));

        for (int i = 0; i < array.length; i++) {
            int smallest_idx = i;
            for (int j = i + 1; j < array.length; j++) {
                if (array[j] < array[smallest_idx])
                    smallest_idx = j;
            }

            if (smallest_idx != i) {
                int tmp = array[smallest_idx];
                array[smallest_idx] = array[i];
                array[i] = tmp;
            }
            if (i != 0) System.out.println(i + ". Durchlauf: " + Arrays.toString(array).replace("[", "").replace("]", "").replace(
                    ",", ""));
        }


        System.out.println("---- nach SelectSort ----");
        System.out.println(Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));
    }

    public static void main(String[] args) {
        int[] array = {24 ,74, 24, 86, 59, 96, 13, 76, 7, 39};
        sort(array);
    }
}