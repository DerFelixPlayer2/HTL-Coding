package de.lolgamr17.classes.abstraction.GUI;

public class PolyLine {
    /*@NotNull
    private final Point[] points;
    //private final int pointCount;

    public PolyLine(@NotNull Point[] points) {
        this.points = points;
        //this.pointCount = points.length;
    }

    @Contract(" -> new")
    public static @NotNull PolyLine readPolyLine() {
        ArrayList<Point> points = new ArrayList<>();

        while (true) {
            Point p = Point.readPoint();
            if (p.x == -1 || p.y == -1) break;
            points.add(p);
        }

        Point[] pointsArray = new Point[points.size()];
        points.toArray(pointsArray);

        return new PolyLine(pointsArray);
    }

    public void draw() {
        for (int i = 0; i < points.length - 1; i++)
            Window.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);

        for (Point p : points)
            p.draw();
    }

    public String asString() {
        StringBuilder sb = new StringBuilder("PolyLine(");
        for (int i = 0; i < points.length; i++)
            sb.append(points[i].asString()).append(i == points.length - 1 ? "" : ", ");
        return sb.append(")").toString();
    }*/
}