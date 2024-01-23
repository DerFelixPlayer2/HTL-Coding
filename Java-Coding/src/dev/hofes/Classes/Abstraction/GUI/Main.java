package dev.hofes.Classes.Abstraction.GUI;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Window.open();

        ArrayList<GraphObject> objects = new ArrayList<>(100);

        while (true) {
            System.out.print("Figure (L|R|C): ");
            String input = scanner.nextLine();

            switch (input) {
                case "L" -> {
                    objects.add(Line.readLine());
                    objects.get(objects.size() - 1).draw();
                }
                case "R" -> {
                    objects.add(Rectangle.readRectangle());
                    objects.get(objects.size() - 1).draw();
                }
                case "C" -> {
                    objects.add(Circle.readCircle());
                    objects.get(objects.size() - 1).draw();
                }
                case "." -> {
                    System.out.println();
                    for (GraphObject obj : objects)
                        System.out.println(obj);
                    System.exit(0);
                }
                default -> System.out.println("Invalid input!");
            }


        }


    }
}