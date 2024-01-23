package dev.hofes.FSST.arrays.schoolway;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class SchoolwayStatistics {
    @NotNull
    ArrayList<Integer> list;

    public SchoolwayStatistics() {
        list = new ArrayList<>();

        Scanner scanner = new Scanner(System.in);
        while (true) {
            int i = scanner.nextInt();
            if (i <= 0) break;
            list.add(i);
        }
        scanner.close();
    }

    public SchoolwayStatistics(@NotNull ArrayList<Integer> list) {
        this.list = list;
    }

    public double avg() {
        return Arrays.stream(list.stream().mapToInt(i -> i).toArray()).average().orElse(-1);
    }

    public double scattering() {
        double avg = avg();
        if (avg == -1) throw new NumberFormatException("Expected ArrayList average, got -1");

        ArrayList<Double> list = new ArrayList<>();
        for (int i : this.list)
            list.add(Math.abs(i - avg));
        return Arrays.stream(list.stream().mapToDouble(i -> i).toArray()).average().orElse(-1);
    }
}