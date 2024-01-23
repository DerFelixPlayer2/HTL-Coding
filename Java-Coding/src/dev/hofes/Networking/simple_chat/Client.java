package dev.hofes.Networking.simple_chat;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in).useDelimiter(System.lineSeparator());
        System.out.print("Enter your name: ");
        final String name = scanner.next();

        try (final Socket socket  = new Socket("localhost", 1234);
            final BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            final PrintWriter out = new PrintWriter((socket.getOutputStream()), true)) {

            JSONObject getHistory = new JSONObject();
            getHistory.put("type", 1);
            out.println(getHistory);

            new Thread(() -> {
                try {
                    String line;
                    while ((line = in.readLine()) != null) {
                        JSONObject json = new JSONObject(line);
                        int type = (int) json.get("type");
                        if (type == 0) {
                            System.out.println(json.get("name") + ": " + json.get("nachricht"));
                        } else if (type == 2) {
                            JSONArray arr = (JSONArray) json.get("history");
                            for (Object a : arr) {
                                JSONObject m = (JSONObject) a;
                                System.out.println(m.get("name") + ": " + m.get("nachricht"));
                            }
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }).start();

            while (true) {
                String msg = scanner.next();
                JSONObject json = new JSONObject();
                json.put("type", 0);
                json.put("name", name);
                json.put("nachricht", msg);
                out.println(json);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}