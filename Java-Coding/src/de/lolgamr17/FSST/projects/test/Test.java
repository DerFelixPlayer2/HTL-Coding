package de.lolgamr17.FSST.projects.test;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Arrays;
import java.util.function.Function;


public class Test {
    public static void main(String[] args) {
        int[][] arr = {{1,2,3,4}, {2,3,4,5}, {6,7,8,9}};
        pascalschesDreieck();
        printColumnByColumn(arr);
        System.out.println(Arrays.toString(getRowSums(arr)));
        System.out.println(Arrays.toString(getColumnSums(arr)));
    }

    public static void printRowByRow(int[] @NotNull [] a) {
        for (int[] ints : a) {
            for (int anInt : ints) {
                System.out.print(anInt + " ");
            }
            System.out.print("\n");
        }
    }

    /*
    * 0 0
    * 1 0
    * 2 0
    *
    * 0 1
    * 1 1
    * 2 1
    * */
    public static void printColumnByColumn(int[] @NotNull [] a) {
        System.out.println(a[0].length);
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {

                //System.out.print(a[k][j] + " ");
            }
            System.out.print("\n");
        }
    }

    @Contract(pure = true)
    public static int @NotNull [] getRowSums(int[] @NotNull [] a) {
        int[] sums = new int[a.length];
        for (int i = 0; i < a.length; i++) {
            int s = 0;
            for (int j = 0; j < a[i].length; j++) {
                s += a[i][j];
            }
            sums[i] = s;
        }
        return sums;
    }

    public static int[] getColumnSums(int[][] a) {
        // TODO: Task 4
        return null;
    }

    public static void pascalschesDreieck() {
        int[] row = new int[] {1};
        for (int i = 0; i < 5; i++) {
            System.out.println(Arrays.toString(row));
            row = computeRow(row);
        }
    }

    @Contract(pure = true)
    public static int @NotNull [] computeRow(int @NotNull [] row) {
        if (row.length == 1) {
            return new int[]{1, 1};
        }

        int[] vals = new int[row.length + 1];
        vals[0] = 1;

        for (int i = 0; i < row.length - 1; i++) {
            vals[i + 1] = row[i] + row[i + 1];
        }
        vals[vals.length - 1] = 1;
        return vals;
    }

    public static int[][] transpose(int[][] a) {
        // TODO: Task 5
        return null;
    }
}