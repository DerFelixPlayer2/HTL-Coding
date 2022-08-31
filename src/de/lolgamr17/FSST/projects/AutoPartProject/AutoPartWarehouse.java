package de.lolgamr17.projects.AutoPartProject;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

import de.lolgamr17.projects.AutoPartProject.Order.Item;
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class AutoPartWarehouse {
    private Part[] parts = null;
    private Order[] orders = null;

    AutoPartWarehouse(String partPath, String orderPath) {
        ArrayList<Part> p = new ArrayList<>();
        ArrayList<Order> o = new ArrayList<>();

        try {
            File file = new File("src/de/lolgamr17/projects/AutoPartProject/" + partPath);
            Scanner parts = new Scanner(file);

            int len = Integer.parseInt(parts.nextLine());
            for (int i = 0; i < len && parts.hasNextLine(); i++) {
                String line = parts.nextLine();

                String[] split = line.split(" ");
                int id = Integer.parseInt(split[0]);
                String description = line.substring(line.indexOf("\"") + 1, line.lastIndexOf("\""));
                int amt = Integer.parseInt(split[split.length - 1]);

                p.add(new Part(id, description, amt));
            }

            this.parts = p.toArray(new Part[0]);
            parts.close();

            file = new File("src/de/lolgamr17/projects/AutoPartProject/" + orderPath);
            Scanner orders = new Scanner(file);

            len = Integer.parseInt(orders.nextLine());
            for (int i = 0; i < len && orders.hasNextLine(); i++) {
                String line = orders.nextLine();
                String[] split = line.split(" ");

                Item[] items = new Item[split.length - 1];
                for (int j = 1; j < split.length; j++) {
                    String[] s = split[j].split(",");
                    items[j - 1] = new Item(getPartByID(Integer.parseInt(s[0])), Integer.parseInt(s[1]));
                }

                o.add(new Order(items));
            }
            this.orders = o.toArray(new Order[0]);
            orders.close();

        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    @Contract(pure = true)
    private @NotNull Part getPartByID(int id) {
        for (Part p : this.parts)
            if (p.id == id)
                return p;
        throw new IllegalArgumentException("No part with id " + id + " found");
    }

    public void processOrders() {
        for (int i = 0; i < this.orders.length; i++) {
            Order order = this.orders[i];
            if (order != null && order.isFulfillable()) {
                order.process();
                this.orders[i] = null;
            }
        }
    }

    public void print() {
        Optional<Part> longest = Arrays.stream(this.parts).max(Comparator.comparingInt(Part::descLength));
        if (longest.isEmpty()) {
            System.out.println("No parts found");
            return;
        }
        int len = longest.get().descLength();

        System.out.println("\nPart no. | Description " + " ".repeat(Math.max((len - 8), 0)) + "| Stock");
        System.out.println("-----------------------" + "-".repeat(Math.max((len - 8), 0)) + "-------");
        for (Part part : this.parts) {
            System.out.printf("%8d | %-" + (len + 3) + "s | %5d\n", part.id, part.description, part.amount);
        }

        System.out.println("\nPart no. | Amounts");
        System.out.println("------------------");
        for (int i = 0; i < this.orders.length; i++) {
            if (this.orders[i] != null) {
                for (Item item : this.orders[i].items) {
                    System.out.printf("%8d | %7d\n", item.part.id, item.amt);
                }
                if (i != this.orders.length - 1) System.out.println("------------------");
            }
        }
    }
}