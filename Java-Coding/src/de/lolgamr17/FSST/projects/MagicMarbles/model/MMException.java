package de.lolgamr17.FSST.projects.MagicMarbles.model;

import java.io.Serial;

/**
 * The exception class for exceptions with the magic marble game
 */
public class MMException extends Exception {
    @Serial
    private static final long serialVersionUID = 8614515858833371347L;

    /**
     * Constructor
     *
     * @param message the message of the exception
     */
    public MMException(String message) {
        super(message);
    }
}