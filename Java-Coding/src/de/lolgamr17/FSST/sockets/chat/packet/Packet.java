package de.lolgamr17.FSST.sockets.chat.packet;

import org.jetbrains.annotations.NotNull;
import org.json.JSONException;
import org.json.JSONObject;

import java.time.Instant;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;

public abstract class Packet {

    private final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm").withZone(ZoneId.systemDefault());
    protected final JSONObject packet;

    protected Packet(String clientName) {
        this.packet = new JSONObject();
        this.packet.put("client", clientName);
        packet.put("timestamp", Instant.now().toString());
    }

    protected Packet(JSONObject packet) {
        this.packet = packet;
    }

    @NotNull
    public static Packet from(@NotNull JSONObject obj) throws JSONException {
        return switch (obj.getInt("type")) {
            case 0 -> new ClientConnectPacket(obj);
            case 1 -> new ClientDisconnectPacket(obj);
            case 2 -> new MessagePacket(obj);
            default -> throw new JSONException("Invalid packet type");
        };
    }

    public String getTimestamp() {
        Instant time = Instant.parse(packet.getString("timestamp"));
        return formatter.format(time);
    }

    public String getClientName() {
        return packet.getString("client");
    }

    public abstract String toNiceString();

    @Override
    public abstract String toString();

}