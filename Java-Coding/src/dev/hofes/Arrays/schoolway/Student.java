package dev.hofes.Arrays.schoolway;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;

public class Student {
    final String name;
    @NotNull
    private final SchoolwayStatistics statistic;

    public Student(String name, @NotNull ArrayList<Integer> list) {
        this.name = name;
        this.statistic = new SchoolwayStatistics(list);
    }

    public Student(String name) {
        this.name = name;
        this.statistic = new SchoolwayStatistics();
    }

    @NotNull
    public SchoolwayStatistics getStatistic() {
        return statistic;
    }
}