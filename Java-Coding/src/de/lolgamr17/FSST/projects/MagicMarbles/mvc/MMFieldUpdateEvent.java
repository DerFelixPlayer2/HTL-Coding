package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import de.lolgamr17.FSST.projects.MagicMarbles.model.MMFieldState;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMState;

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