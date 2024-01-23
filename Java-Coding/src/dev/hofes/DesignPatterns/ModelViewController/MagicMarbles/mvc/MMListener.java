package dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.mvc;

import java.util.EventListener;

public interface MMListener extends EventListener {
    void onUpdateField(MMFieldUpdateEvent evt);

    void onUpdateScore(MMScoreUpdateEvent evt);

    void onMarblePressed(MMMarblePressedEvent evt);

    void onNewGame(MMNewGameEvent evt);

}