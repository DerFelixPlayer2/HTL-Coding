package de.lolgamr17.standalone.classes.Mengenrechner;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
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
}