package dev.hofes.SEN.sorting;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

public class InsertSort {
    public static void sort(int @NotNull [] array) {
        System.out.println("---- vor InsertSort ----");
        System.out.println(Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));

        for (int i = 0; i < array.length; i++) {
            for (int j = i; j != 0 && array[j] < array[j - 1]; j--) {
                int tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
            if (i != 0) System.out.println(i + ". Durchlauf: " + Arrays.toString(array).replace("[", "").replace("]", "").replace(
                    ",", ""));
        }


        System.out.println("---- nach InsertSort ----");
        System.out.println(Arrays.toString(array).replace("[", "").replace("]", "").replace(",", ""));
    }

    public static void main(String[] args) {
        int[] array = {61, 96, 24, 45, 87, 29, 4, 14, 31, 31};
        sort(array);
    }
}