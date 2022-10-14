package de.lolgamr17.SEN.streams;

import java.lang.reflect.Array;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        nothingSpecial();
        System.out.println("");
        special();
    }

    private static void nothingSpecial() {
        List<Dish> menu = Arrays.asList(
                new Dish("pork", false, 800, Dish.Type.MEAT), new Dish("beef", false, 700, Dish.Type.MEAT),
                new Dish("chicken", false, 400, Dish.Type.MEAT), new Dish("french fries", true, 530,
                        Dish.Type.OTHER),
                new Dish("rice", true, 350, Dish.Type.OTHER), new Dish("season fruit", true, 120,
                        Dish.Type.OTHER),
                new Dish("pizza", true, 550, Dish.Type.OTHER), new Dish("prawns", false, 400,
                        Dish.Type.FISH),
                new Dish("salmon", false, 450, Dish.Type.FISH)
        );

        List<Dish> lowCalories = new ArrayList<>();
        for (Dish dish : menu) {
            if (dish.getCalories() < 400) {
                lowCalories.add(dish);
            }
        }
        Collections.sort(lowCalories, (a, b) -> a.getCalories() - b.getCalories());

        List<String> names = new ArrayList<>();
        for (Dish dish : lowCalories) {
            names.add(dish.getName());
        }

        for (String name : names) {
            System.out.println(name);
        }
    }

    private static void special() {
        List<Dish> menu = Arrays.asList(
                new Dish("pork", false, 800, Dish.Type.MEAT),
                new Dish("beef", false, 700, Dish.Type.MEAT),
                new Dish("chicken", false, 400, Dish.Type.MEAT),
                new Dish("french fries", true, 530, Dish.Type.OTHER),
                new Dish("rice", true, 350, Dish.Type.OTHER),
                new Dish("season fruit", true, 120, Dish.Type.OTHER),
                new Dish("pizza", true, 550, Dish.Type.OTHER),
                new Dish("prawns", false, 400, Dish.Type.FISH),
                new Dish("salmon", false, 450, Dish.Type.FISH)
        );

        menu.stream()
                .filter(dish -> dish.getCalories() < 400)
                .sorted(Comparator.comparing(Dish::getCalories))
                .map(Dish::getName)
                .forEach(System.out::println);
    }

}