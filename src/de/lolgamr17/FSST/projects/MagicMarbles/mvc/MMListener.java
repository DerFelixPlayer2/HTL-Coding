package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import java.util.EventListener;

public interface MMListener extends EventListener {
    void fieldChanged(MMFieldUpdateEvent evt);

}