package dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.mvc;

import java.util.EventObject;

public class MMScoreUpdateEvent extends EventObject {

    private final int score;

    public MMScoreUpdateEvent(Object source, int score) {
        super(source);
        this.score = score;
    }

    public int getScore() {
        return score;
    }
}