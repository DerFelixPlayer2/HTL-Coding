package dev.hofes.Interfaces;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class Tokenizer implements Iterable<String> {
    private final String sentence;
    private final String[] tokens;

    @Contract(pure = true)
    public Tokenizer(@NotNull String sentence) {
        this.sentence = sentence;
        this.tokens = sentence.split(" ");
    }

    public String getSentence() {
        return sentence;
    }

    public String[] getTokens() {
        return tokens;
    }

    @NotNull
    @Override
    public Iterator<String> iterator() {
        return new Iterator<>() {
            private int i = 0;

            @Override
            public boolean hasNext() {
                return i < tokens.length;
            }

            @Override
            public String next() {
                return tokens[i++];
            }
        };
    }
}