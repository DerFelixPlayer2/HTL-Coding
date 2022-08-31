package de.lolgamr17.strings;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Zaehler {
    final String definition;
    int amt;

    public Zaehler(String definition, int amt) {
        this.definition = definition;
        this.amt = amt;
    }

    public void print() {
        System.out.println(amt + " " + format(definition));
    }

    public void inc() {
        this.amt++;
    }

    public void print(@NotNull String str) {
        System.out.println(str.replace("%b", format(definition)).replace("%n", String.valueOf(amt)));
    }

    @Contract(pure = true)
    private @NotNull String format(@NotNull String str) {
        return str.toLowerCase().substring(0, 1).toUpperCase() + str.toLowerCase().substring(1).toLowerCase();
    }
}