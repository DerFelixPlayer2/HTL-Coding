package de.lolgamr17.FSST.classes;

import org.jetbrains.annotations.NotNull;

public class Artikelverwaltung {

    private static class Article {
        public int artikelNr;
        public int einzelPreis;
        public int amt;
    }

    static @NotNull Article readArticle(@NotNull String s) {
        String[] input = s.split("\\w+");

        Article article = new Article();
        article.artikelNr = Integer.parseInt(input[0]);
        article.einzelPreis = Integer.parseInt(input[1]);

        int amt = 0;
        for (int i = 2; i < input.length; i++)
            amt += Integer.parseInt(input[i]);
        article.amt = amt;

        return article;
    }

    static void printArticle(@NotNull Article article) {
        System.out.println(article.artikelNr + " " + (article.amt * article.einzelPreis));
    }
}