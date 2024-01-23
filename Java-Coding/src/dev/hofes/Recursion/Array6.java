package dev.hofes.Recursion;

public class Array6 {
    public static boolean main(int[] arr, int i) {
        if (i >= arr.length) return false;
        if (arr[i] == 6) return true;
        return main(arr, i + 1);
    }

    public static boolean main(int[] arr) {
        return main(arr, 0);
    }
}