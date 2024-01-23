package dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.mvc;

import dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.model.MMFieldState;
import dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.model.MMState;

import java.util.EventObject;

public class MMFieldUpdateEvent extends EventObject {
    private final MMFieldState[][] field;
    private final MMState state;

    public MMFieldUpdateEvent(Object source, MMFieldState[][] field, MMState state) {
        super(source);
        this.field = field;
        this.state = state;
    }

    public MMState getState() {
        return state;
    }

    public MMFieldState[][] getField() {
        return field;
    }

}