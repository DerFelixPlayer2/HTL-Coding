package de.lolgamr17.projects.GUI;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.awt.*;

public class Rectangle extends GraphObject {
    private int w, h;

    public Rectangle(Point position, int w, int h, Color color) {
        super(color, position);

        this.w = w;
        this.h = h;
    }

    @Contract(" -> new")
    public static @NotNull Rectangle readRectangle() {
        Point position = Point.readPoint();
        System.out.print("Width: ");
        int w = Point.scanner.nextInt();
        System.out.print("Height: ");
        int h = Point.scanner.nextInt();
        System.out.println("Color (R G B): ");
        Color color = new Color(Point.scanner.nextInt(), Point.scanner.nextInt(), Point.scanner.nextInt());
        return new Rectangle(position, w, h, color);
    }

    @Override
    public void resize(double factor) {
        w = (int) (w * factor);
        h = (int) (h * factor);
    }

    @Override
    public void draw() {
        Window.fillRectangle(getLocation().getX(), getLocation().getY(), w, h, getColor());
    }

    @Override
    public String toString() {
        return "Rectangle(" + getLocation() + ", " + w + ", " + h + ")";
    }
}