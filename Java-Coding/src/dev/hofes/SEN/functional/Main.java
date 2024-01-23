package dev.hofes.SEN.functional;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;
import java.util.function.Function;
import java.util.function.Predicate;

public class Main {
    public static void main(String[] args) {

        /*Function add = (a, b) -> a + b;
        Function sub = (a, b) -> a - b;
        Function mul = (a, b) -> a * b;
        Function div = (a, b) -> a / b;

        System.out.println(add.evaluate(1, 2));
        System.out.println(sub.evaluate(1, 2));
        System.out.println(mul.evaluate(1, 2));
        System.out.println(div.evaluate(1, 2));/**/
    }

    public static int calculate(int a, int b, @NotNull _Function f) {
        return f.apply(a, b);
    }

    public static int @NotNull [] map(Function<Integer, Integer> f, int @NotNull [] arr) {
        int[] result = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            result[i] = f.apply(arr[i]);
        }
        return result;
    }

    public static int @NotNull [] filter(Predicate<Integer> f, int @NotNull [] arr) {
        int[] result = new int[arr.length];
        int index = 0;
        for (int j : arr) {
            if (f.test(j)) {
                result[index] = j;
                index++;
            }
        }
        return Arrays.copyOf(result, index);
    }
}