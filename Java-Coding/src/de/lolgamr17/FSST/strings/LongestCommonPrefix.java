package de.lolgamr17.FSST.strings;

import org.jetbrains.annotations.NotNull;

public class LongestCommonPrefix {
    public static int main(@NotNull String str, @NotNull String str2) {
        int i;
        for (i = 0; i < Math.min(str.length(), str2.length()); i++)
            if (!str.startsWith(str2.substring(0, i + 1)))
                break;
        return i;
    }
}