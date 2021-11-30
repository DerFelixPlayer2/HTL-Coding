package de.lolgamr17.standalone.classes;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class RectangleIntersection {
    private static class Rectangle {
        int x, y;
        int width, height;

        public Rectangle(int x, int y, int width, int height) {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
        }

        @Override
        public String toString() {
            return "Rectangle{" +
                    "x=" + x +
                    ", y=" + y +
                    ", width=" + width +
                    ", height=" + height +
                    '}';
        }
    }

    @Nullable
    public static Rectangle intersection(@NotNull Rectangle r1, @NotNull Rectangle r2) {
        // Write a method intersection(r1, r2), that calculates the intersection of r1 and r2 and returns it.
        // null, if there is no intersection
        // r1 and r2 are not modified.

        Rectangle r = new Rectangle(0, 0, 0, 0);
        r.x = Math.max(r1.x, r2.x);
        r.y = Math.max(r1.y, r2.y);

        r.width = Math.min(r1.x + r1.width, r2.x + r2.width) - r.x;
        r.height = Math.min(r1.y + r1.height, r2.y + r2.height) - r.y;

        if (r.width < 0 || r.height < 0) {
            return null;
        }

        return r;
    }
}