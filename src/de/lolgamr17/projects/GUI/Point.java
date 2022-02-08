package de.lolgamr17.projects.GUI;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.awt.*;
import java.util.Scanner;

public class Point {
    protected static final Scanner scanner = new Scanner(System.in);
    private final int x, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Contract(" -> new")
    public static @NotNull Point readPoint() {
        System.out.print("Point (x, y): ");
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        return new Point(x, y);
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public String toString() {
        return "Point(" + this.x + ", " + this.y + ")";
    }
}