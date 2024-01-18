package de.lolgamr17.recursion;

import org.jetbrains.annotations.NotNull;

public class EndX {
    public static @NotNull String main(@NotNull String s, int i) {
        if (s.length() - 1 <= i) return s;
        if (s.charAt(i) == 'x') {
            String ss = main(s, i + 1);
            return ss.substring(0, i) + ss.substring(i + 1) + 'x';
        } else return main(s, i + 1);
    }

    public static @NotNull String main(@NotNull String s) {
        return main(s, 0);
    }
}