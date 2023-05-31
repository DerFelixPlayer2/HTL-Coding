package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import de.lolgamr17.FSST.projects.MagicMarbles.model.MMGame;

import java.util.ArrayList;
import java.util.EventObject;

public class MMModel {

    private final ArrayList<MMListener> listeners = new ArrayList<>();

    public void updateField(MMGame field) {
        emit(new MMFieldUpdateEvent(this, field));
    }

    public void updateScore(int score) {
        emit(new MMScoreUpdateEvent(this, score));
    }

    public void marblePressed(int x, int y) {
        emit(new MMMarblePressedEvent(this, x, y));
    }

    public void newGame(int rows, int cols) {
        emit(new MMNewGameEvent(this, rows, cols));
    }

    public void addListener(MMListener listener) {
        listeners.add(listener);
    }

    public void removeListener(MMListener listener) {
        listeners.remove(listener);
    }


    private void emit(EventObject e) throws IllegalArgumentException {
        for (MMListener l : listeners) {
            if (e.getClass().equals(MMFieldUpdateEvent.class)) {
                l.onUpdateField((MMFieldUpdateEvent) e);
            } else if (e.getClass().equals(MMScoreUpdateEvent.class)) {
                l.onUpdateScore((MMScoreUpdateEvent) e);
            } else if (e.getClass().equals(MMMarblePressedEvent.class)) {
                l.onMarblePressed((MMMarblePressedEvent) e);
            } else if (e.getClass().equals(MMNewGameEvent.class)) {
                l.onNewGame((MMNewGameEvent) e);
            } else {
                throw new IllegalArgumentException("Unknown event type: " + e.getClass().getName());
            }
        }
    }

}