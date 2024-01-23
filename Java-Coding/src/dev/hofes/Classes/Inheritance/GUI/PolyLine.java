package dev.hofes.Classes.Inheritance.GUI;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;

public class PolyLine {
    @NotNull
    private final Point[] points;

    public PolyLine(@NotNull Point[] points) {
        this.points = points;
    }

    @Contract(" -> new")
    public static @NotNull PolyLine readPolyLine() {
        ArrayList<Point> points = new ArrayList<>();

        while (true) {
            Point p = Point.readPoint();
            if (p.getX() == -1 || p.getY() == -1) break;
            points.add(p);
        }

        Point[] pointsArray = new Point[points.size()];
        points.toArray(pointsArray);

        return new PolyLine(pointsArray);
    }

    public void draw() {
        for (int i = 0; i < points.length - 1; i++)
            Window.drawLine(points[i].getX(), points[i].getY(), points[i + 1].getX(), points[i + 1].getY());
    }

    public String asString() {
        StringBuilder sb = new StringBuilder("PolyLine(");
        for (int i = 0; i < points.length; i++)
            sb.append(points[i]).append(i == points.length - 1 ? "" : ", ");
        return sb.append(")").toString();
    }
}