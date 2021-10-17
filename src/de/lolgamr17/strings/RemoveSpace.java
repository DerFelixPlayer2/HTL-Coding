package de.lolgamr17.strings;

import org.jetbrains.annotations.NotNull;

import java.lang.module.FindException;

public class RemoveSpace {
    public static @NotNull String withCharAt(@NotNull String str) {
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < str.length(); i++)
            if (str.charAt(i) != ' ')
                b.append(str.charAt(i));
        return b.toString();
    }

    public static @NotNull String withIndexOf(@NotNull String str) {
        StringBuilder b = new StringBuilder(str);
        while (b.toString().contains(" "))
            b.delete(b.indexOf(" "), b.indexOf(" ") + 1);
        return b.toString();
    }

    public static @NotNull String withReplace(@NotNull String str) {
        return str.replace(" ", "");
    }
}