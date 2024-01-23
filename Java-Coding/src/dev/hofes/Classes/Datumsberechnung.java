package dev.hofes.Classes;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Datumsberechnung {
    private static class Date {
        public int day;
        public int month;
        public int year;
    }

    // Difference between two dates
    public static int dayDiff(Date date1, Date date2) {
        if (needsSwap(date1, date2)) {
            Date temp = date1;
            date1 = date2;
            date2 = temp;
        }

        int days = 0;
        int month = date1.month;
        int year = date1.year;
        while (year != date2.year || month != date2.month) {
            days += getDaysInMonth(month);
            month++;
            if (month > 11) {
                month = 0;
                year++;
            }
        }
        days += date2.day - date1.day;
        return days;
    }

    @Contract(pure = true)
    private static boolean needsSwap(@NotNull Date date1, @NotNull Date date2) {
        if (date1.year > date2.year) {
            return true;
        } else if (date1.year == date2.year) {
            if (date1.month > date2.month) {
                return true;
            } else if (date1.month == date2.month) {
                return date1.day > date2.day;
            }
        }
        return false;
    }

    private static int getDaysInMonth(int i) {
        return switch (i) {
            case 0, 2, 4, 6, 7, 9, 11 -> 31;
            case 3, 5, 8, 10 -> 30;
            case 1 -> 28;
            default -> 0;
        };
    }

    public static void main(String[] args) {
        Date date1 = new Date();
        date1.day = 10;
        date1.month = 1;
        date1.year = 2022;
        Date date2 = new Date();
        date2.day = 13;
        date2.month = 0;
        date2.year = 2021;
        System.out.println(dayDiff(date1, date2));
    }

}