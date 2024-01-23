package dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.mvc;

import java.util.EventObject;

public class MMMarblePressedEvent extends EventObject {

    private final int x, y;

    public MMMarblePressedEvent(Object source, int x, int y) {
        super(source);
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

}