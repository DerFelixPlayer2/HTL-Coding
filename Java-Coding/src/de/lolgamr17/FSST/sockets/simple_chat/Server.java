package de.lolgamr17.FSST.sockets.simple_chat;

import org.jetbrains.annotations.NotNull;
import org.json.JSONArray;
import org.json.JSONObject;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Server {
    public static void main(String[] args) throws IOException {
        try (ServerSocket server = new ServerSocket(1234)) {
            final List<Message> messages = new ArrayList<>();
            final List<PrintWriter> writers = new ArrayList<>();
            while (true) {
                final Socket socket = server.accept();
                new Thread(new ConnectionThread(messages, writers, socket)).start();
            }
        }
    }

    private record Message(String sender, String message) {
    }

    static class ConnectionThread implements Runnable {
        private final List<Message> messages;
        private final List<PrintWriter> writers;
        private final Socket socket;

        ConnectionThread(List<Message> messages, List<PrintWriter> writers, Socket socket) {
            this.messages = messages;
            this.writers = writers;
            this.socket = socket;
        }

        @Override
        public void run() {
            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                 PrintWriter out = new PrintWriter((socket.getOutputStream()), true)) {
                synchronized (writers) {
                    writers.add(out);
                }
                while (true) {
                    String l = in.readLine();
                    System.err.println("received: " + l);
                    JSONObject json = new JSONObject(l);
                    int type = (int) json.get("type");
                    if (type == 0) {
                        Message m = new Message((String) json.get("name"), (String) json.get("nachricht"));
                        synchronized (messages) {
                            messages.add(m);
                        }
                        broadcastMessage(m);
                    } else if (type == 1) {
                        replyHistory(out);
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private void replyHistory(PrintWriter out) {
            JSONObject reply = new JSONObject();
            reply.put("type", 2);
            JSONArray arr = new JSONArray();
            synchronized (messages) {
                for (Message m : messages) {
                    JSONObject message = getJsonObject(m);
                    arr.put(message);
                }
            }
            reply.put("history", arr);
            out.println(reply);
        }

        private @NotNull JSONObject getJsonObject(@NotNull Message m) {
            JSONObject message = new JSONObject();
            message.put("type", 0);
            message.put("name", m.sender);
            message.put("nachricht", m.message);
            return message;
        }

        private void broadcastMessage(Message m) {
            synchronized (writers) {
                for (PrintWriter w : writers) {
                    w.println(getJsonObject(m));
                }
            }
        }
    }
}