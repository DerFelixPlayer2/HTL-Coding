package de.lolgamr17.SEN.streams;

import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) {
        // nothingSpecial();
        // System.out.println("");
        // special();



        Stream.iterate(new long[]{0, 1}, t -> new long[]{t[1], t[0] + t[1]})
                .map(t -> t[0]).limit(100).forEach(System.out::println);

        Stream<Integer> posInts = Stream.iterate(1, x -> x + 1);
        posInts.limit(5)
                .flatMapToInt(i -> IntStream.iterate(1, j -> j + 1).limit(i))
                .forEach(System.out::println);
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