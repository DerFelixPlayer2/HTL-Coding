package dev.hofes.Classes.Inheritance.GUI;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.awt.*;

public class Circle extends GraphObject {
    private int radius;

    public Circle(Point center, int radius, Color color) {
        super(color, center);

        this.radius = radius;
    }

    @Contract(" -> new")
    public static @NotNull Circle readCircle() {
        Point center = Point.readPoint();
        System.out.print("Radius: ");
        int radius = Point.scanner.nextInt();
        System.out.print("Color (R G B): ");
        return new Circle(center, radius, new Color(Point.scanner.nextInt(), Point.scanner.nextInt(), Point.scanner.nextInt()));
    }

    public void resize(double factor) {
        radius *= factor;
    }

    public void draw() {
        Window.fillCircle(getLocation().getX(), getLocation().getY(), radius, getColor());
    }

    public String toString() {
        return "Circle(" + getLocation() + ", " + radius + ")";
    }
}