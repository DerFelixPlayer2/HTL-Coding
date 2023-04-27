package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import de.lolgamr17.FSST.projects.MagicMarbles.model.MMGame;

import java.util.EventObject;

public class MMFieldUpdateEvent extends EventObject {
    private final MMGame game;

    public MMFieldUpdateEvent(Object source, MMGame game) {
        super(source);
        this.game = game;
    }

    public MMGame getGame() {
        return game;
    }
}