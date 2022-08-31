package de.lolgamr17.strings;

import org.jetbrains.annotations.NotNull;

public class LongestCommonSuffix {
    public static int main(@NotNull String str, @NotNull String str2) {
        int i;
        for (i = 0; i < Math.min(str.length(), str2.length()); i++)
            if (!str.endsWith(str2.substring(str2.length() - i - 1)))
                break;
        return i;
    }
}