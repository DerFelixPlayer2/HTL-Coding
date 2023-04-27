package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import de.lolgamr17.FSST.projects.MagicMarbles.MagicMarblesMain;
import de.lolgamr17.FSST.projects.MagicMarbles.model.MMGame;

import java.util.ArrayList;

public class MMModel {

    private ArrayList<MMListener> listeners = new ArrayList<>();

    public void updateField(MMGame field) {
        emit(new MMFieldUpdateEvent(this, field));
//        MagicMarblesMain.printField(field);
    }

    public void addListener(MMListener listener) {
        listeners.add(listener);
    }

    public void removeListener(MMListener listener) {
        listeners.remove(listener);
    }

    private void emit(MMFieldUpdateEvent e) {
        for (MMListener l : listeners) {
            l.fieldChanged(e);
        }
    }

}