package de.lolgamr17.FSST.projects.GUI;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.awt.*;

public class Line extends GraphObject {
    private int dx, dy;

    public Line(Point from, int dx, int dy, Color color) {
        super(color, from);

        this.dx = dx;
        this.dy = dy;
    }

    @Contract(" -> new")
    public static @NotNull Line readLine() {
        Point from = Point.readPoint();
        Point to = Point.readPoint();
        System.out.print("Color (R G B): ");
        return new Line(from, to.getX() - from.getX(), to.getY() - from.getY(),
                new Color(Point.scanner.nextInt(), Point.scanner.nextInt(), Point.scanner.nextInt()));
    }

    public void resize(double factor) {
        dx *= factor;
        dy *= factor;
    }

    public void draw() {
        Window.drawLine(getLocation().getX(), getLocation().getY(), getLocation().getX() + dx,
                getLocation().getY() + dy, getColor());
    }

    public String toString() {
        return "Line(" + getLocation() + ", " + new Point(getLocation().getX() + dx, getLocation().getY() + dy) + ")";
    }
}