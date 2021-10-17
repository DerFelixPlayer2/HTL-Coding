package de.lolgamr17.arrays;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class RightJustified {
    @Contract(pure = true)
    public static void main(String @NotNull [] strings) {
        int l = 0;
        for (String s : strings)
            if (s.length() > l)
                l = s.length();

        for (int i = 0; i < strings.length; i++)
            strings[i] = " ".repeat(l - strings[i].length()) + strings[i];
    }
}