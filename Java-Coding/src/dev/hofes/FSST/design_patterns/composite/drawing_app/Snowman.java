package dev.hofes.FSST.design_patterns.composite.drawing_app;

import static java.awt.Color.WHITE;

public class Snowman extends CompositeShape {


    public Snowman(int x, int y, int radius, double inc) {
        super(x, y);

        add(new Circle(x, y, radius));
        add(new Circle(x, (int) Math.floor(y + (radius * 1.8)), (int) Math.floor(radius * inc)));
        add(new Circle(x, (int) Math.floor(y + (2 * radius * 1.8)), ((int) Math.floor(radius * inc * inc))));
    }

    public void move(int dx, int dy) {
        draw(WHITE);

        setX(getX() + dx);
        setY(getY() + dy);

        draw();
    }
}