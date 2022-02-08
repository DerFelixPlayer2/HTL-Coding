package de.lolgamr17.projects.GUI;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Window.open();

        ArrayList<Line> lines = new ArrayList<>(100);
        ArrayList<Rectangle> rectangles = new ArrayList<>(100);
        ArrayList<Circle> circles = new ArrayList<>(100);
        ArrayList<PolyLine> polyLines = new ArrayList<>(100);

        while (true) {
            System.out.print("Figure (L|R|C|P): ");
            String input = scanner.nextLine();

            switch (input) {
                case "L" -> {
                    lines.add(Line.readLine());
                    lines.get(lines.size() - 1).draw();
                }
                case "R" -> {
                    rectangles.add(Rectangle.readRectangle());
                    rectangles.get(rectangles.size() - 1).draw();
                }
                case "C" -> {
                    circles.add(Circle.readCircle());
                    circles.get(circles.size() - 1).draw();
                }
                case "P" -> {
                    polyLines.add(PolyLine.readPolyLine());
                    polyLines.get(polyLines.size() - 1).draw();
                }
                case "." -> {
                    System.out.println("");
                    for (Line line : lines)
                        System.out.println(line.asString());
                    for (Rectangle rectangle : rectangles)
                        System.out.println(rectangle.asString());
                    for (Circle circle : circles)
                        System.out.println(circle.asString());
                    for (PolyLine polyLine : polyLines)
                        System.out.println(polyLine.asString());
                    System.exit(0);
                }
                default -> System.out.println("Invalid input!");
            }


        }


    }
}