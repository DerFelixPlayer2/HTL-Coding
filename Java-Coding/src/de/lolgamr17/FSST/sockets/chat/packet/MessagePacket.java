package de.lolgamr17.FSST.sockets.chat.packet;

import org.jetbrains.annotations.NotNull;
import org.json.JSONObject;

public class MessagePacket extends Packet {

    public MessagePacket(@NotNull String clientName, @NotNull String message) {
        super(clientName);
        packet.put("type", 2);
        packet.put("message", message);
    }

    MessagePacket(@NotNull JSONObject packet) {
        super(packet);
    }

    public String getMessage() {
        return packet.getString("message");
    }

    public String toNiceString() {
        return "[" + getTimestamp() + "] " + getClientName() + ": " + getMessage();
    }

    @Override
    public String toString() {
        return packet.toString();
    }
}