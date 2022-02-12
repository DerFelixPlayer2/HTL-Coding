package de.lolgamr17.strings;

import java.util.Scanner;

public class CountWords {
    public static void main() {
        Scanner scanner = new Scanner(System.in);
        while (true)
            if (scanner.nextLine().equals("START"))
                break;

        int c = 0;
        while (true) {
            String s = scanner.nextLine();
            if (s.toLowerCase().contains("salad")) c++;
            else if (s.equals("END")) {
                System.out.println("Matched " + c + " characters.");
                return;
            }
        }
    }
}