package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import java.util.EventListener;

public interface MMListener extends EventListener {
    void onUpdateField(MMFieldUpdateEvent evt);

    void onUpdateScore(MMScoreUpdateEvent evt);

    void onMarblePressed(MMMarblePressedEvent evt);

    void onNewGame(MMNewGameEvent evt);

}