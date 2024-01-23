package dev.hofes.FSST.arrays.walterslist;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;

public class WaltersList {
    ArrayList<Student> list;

    public WaltersList() {
        this.list = new ArrayList<>();
    }

    public void addFine(String name, String Class, double amt) {
        Student s = get(name);
        if (s == null) list.add(new Student(name, Class, amt));
        else s.addFine(amt);
    }

    public void printList() {
        for (Student s : list)
            System.out.println(s.getFine() + " -- " + s.getName() + ", " + s.getClassName());
    }

    public void finePaid(String name) {
        Student s = get(name);
        if (s == null) throw new IllegalArgumentException("Name does not exist.");
        list.remove(s);
    }

    public void sortByAmount() {
        for (int i = 0; i < list.size() - 1; i++) {
            for (int j = 0; j < list.size() - 1 - i; j++) {
                if (list.get(j + 1).getFine() > list.get(j).getFine()) {
                    Student s = list.get(j + 1);
                    list.set(j + 1, list.get(j));
                    list.set(j, s);
                }
            }
        }
    }

    public void printAmountByClass(@NotNull String Class) {
        double sum = 0;
        for (Student s : list)
            if (s.getClassName().equals(Class))
                sum += s.getFine();
        System.out.println("Fine of whole " + Class + " class: " + sum + "€");
    }

    @NotNull
    public ArrayList<Double> getAmountByClass(@NotNull String Class) {
        ArrayList<Double> list = new ArrayList<>();
        for (Student s : this.list)
            if (s.getClassName().equals(Class))
                list.add(s.getFine());
        return list;
    }

    @Nullable
    private Student get(String name) {
        for (Student s : list)
            if (s.getName().equals(name))
                return s;
        return null;
    }
}