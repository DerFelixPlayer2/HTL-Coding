package dev.hofes.Classes;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Mengenrechner {
    public static void main(String[] args) {
        System.out.println("\nFolgende Operationen stehenn zur Verfügung:");
        System.out.println("R - Read: Liest eine neue Menge ein");
        System.out.println("D - Duplicate: Dupliziert eine Menge");
        System.out.println("U - Union: Vereinigt zwei Mengen");
        System.out.println("I - Intersect: Schneidet zwei Mengen");
        System.out.println("F - Diff: Bildet die Differenz von zwei Mengen");
        System.out.println("M - Member: Prueft ob ein Wert Teil einer Menge ist");
        System.out.println(". - Exit: Beendet das Programm");
        System.out.println("-----------------------------------------------------");

        Scanner scanner = new Scanner(System.in);
        List<Set> sets = new ArrayList<>(2);

        sets.add(new Set());
        sets.add(new Set(new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}));

        System.out.println("[0] " + sets.get(0));
        System.out.println("[1] " + sets.get(1));

        while (true) {
            int i, i2;
            Set set = null;

            System.out.print("Kommando (R|D|U|I|F|M|.): ");
            String command = scanner.nextLine();
            switch (command.toUpperCase()) {
                case "R":
                    System.out.print("Elemente (Ende mit -1): ");
                    List<Integer> elements = new ArrayList<>();
                    int element = scanner.nextInt();
                    while (element != -1) {
                        elements.add(element);
                        element = scanner.nextInt();
                    }
                    set = new Set(elements.stream().mapToInt(Integer::intValue).toArray());
                    sets.add(set);

                    System.out.printf("[%d] %s\n", sets.size() - 1, set);
                    break;

                case "D":
                    System.out.print("Index Operand 1: ");
                    i = scanner.nextInt();

                    if (i < 0 || i >= sets.size())
                        throw new IllegalArgumentException("Index out of bounds");

                    set = sets.get(i);
                    sets.add(set.duplicate());
                    System.out.printf("[%d] %s\n", sets.size() - 1, set);
                    break;

                case "M":
                    System.out.print("Index Operand 1: ");
                    i = scanner.nextInt();

                    if (i < 0 || i >= sets.size())
                        throw new IllegalArgumentException("Index out of bounds");

                    System.out.print("Wert: ");
                    int value = scanner.nextInt();

                    System.out.println(sets.get(i).contains(value));
                    break;

                case "F":
                case "U":
                case "I":

                    System.out.print("Index Operand 1: ");
                    i = scanner.nextInt();
                    System.out.print("Index Operand 2: ");
                    i2 = scanner.nextInt();

                    if (i < 0 || i >= sets.size() || i2 < 0 || i2 >= sets.size())
                        throw new IllegalArgumentException("Index out of bounds");

                    switch (command.toUpperCase()) {
                        case "U" -> set = Set.intersect(sets.get(i), sets.get(i2));
                        case "I" -> set = Set.union(sets.get(i), sets.get(i2));
                        case "F" -> set = Set.diff(sets.get(i), sets.get(i2));
                    }

                    sets.add(set);
                    System.out.printf("[%d] %s\n", sets.size() - 1, set);
                    break;

                case ".":
                    return;
            }
            scanner.nextLine();
        }
    }


    private static class Set {
        private final boolean[] values;

        Set() {
            values = new boolean[16];
        }

        Set(int @NotNull [] values) {
            if (values.length > 16) throw new IllegalArgumentException("Set cannot be longer than 16!");
            this.values = new boolean[16];
            for (int v : values) {
                if (v < 0 || v > 15) throw new IllegalArgumentException("Set cannot contain values < 0 or > 15!");
                this.values[v] = true;
            }
        }

        @NotNull Set duplicate() {
            Set s = new Set();
            System.arraycopy(this.values, 0, s.values, 0, this.values.length);
            return s;
        }

        static @NotNull Set readSet() {
            Scanner sc = new Scanner(System.in);
            Set s = new Set();
            int v;
            while (true) {
                System.out.print("Bitte geben Sie eine Zahl ein: ");
                v = sc.nextInt();
                if (v == -1)
                    break;
                s.values[v] = true;
            }
            return s;
        }

        static @NotNull Set union(@NotNull Set s1, @NotNull Set s2) {
            Set s = s1.duplicate();
            s.union(s2);
            return s;
        }

        static @NotNull Set intersect(@NotNull Set s1, @NotNull Set s2) {
            Set s = s1.duplicate();
            s.intersect(s2);
            return s;
        }

        static @NotNull Set diff(@NotNull Set s1, @NotNull Set s2) {
            Set s = s1.duplicate();
            s.diff(s2);
            return s;
        }

        boolean contains(int v) {
            return this.values[v];
        }

        void union(@NotNull Set s) {
            for (int i = 0; i < s.values.length; i++)
                if (s.values[i])
                    this.values[i] = true;
        }

        void intersect(@NotNull Set s) {
            for (int i = 0; i < s.values.length; i++)
                if (!s.values[i])
                    this.values[i] = false;
        }

        void diff(@NotNull Set s) {
            for (int i = 0; i < s.values.length; i++)
                if (s.values[i])
                    this.values[i] = false;
        }

        @Override
        public @NotNull String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("{ ");
            for (int i = 0; i < values.length; i++)
                if (values[i])
                    sb.append(i).append(" ");
            sb.append("}");
            return sb.toString();
        }
    }
}