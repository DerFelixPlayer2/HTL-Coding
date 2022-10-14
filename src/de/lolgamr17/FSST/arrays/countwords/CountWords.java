package de.lolgamr17.FSST.arrays.countwords;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class CountWords {
    public static void main() {
        ArrayList<Word> words = new ArrayList<>();

        Scanner scanner = new Scanner(System.in);
        while (true) {
            String s = scanner.nextLine();
            if (s.equals("END") || s.equals("ENDE")) break;
            if (exists(s, words)) Objects.requireNonNull(get(s, words)).inc();
            else words.add(new Word(s));
        }

        long highest = 0;
        String word = "";
        for (Word w : words) {
            long c = w.getCount();
            if (c > highest) {
                highest = c;
                word = w.getWord();
            }
            System.out.println(c + " ... " + w.getWord());
        }
        System.out.println("Most occuring Word: " + word + " (" + highest + ")");

    }

    private static boolean exists(String s, @NotNull ArrayList<Word> list) {
        for (Word w : list)
            if (w.getWord().equals(s))
                return true;
        return false;
    }

    @Nullable
    private static Word get(String s, @NotNull ArrayList<Word> list) {
        for (Word w : list)
            if (w.getWord().equals(s))
                return w;
        return null;
    }
}