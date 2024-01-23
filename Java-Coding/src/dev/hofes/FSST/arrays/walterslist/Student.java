package dev.hofes.FSST.arrays.walterslist;

import java.util.Objects;

public class Student {
    private final String name;
    private final String Class;
    private double fine;

    protected Student(String name, String Class, double fine) {
        this.name = name;
        this.fine = fine;
        this.Class = Class;
    }

    public String getName() {
        return name;
    }

    public void addFine(double amt) {
        this.fine += amt;
    }

    public double getFine() {
        return fine;
    }

    public String getClassName() {
        return Class;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        return Objects.equals(name, ((Student) o).name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}