import { connect as mqttConnect } from "mqtt";

const mqttClient = mqttConnect('', {
  host: "mosquitto",
  port: 1883,
  reconnectPeriod: 1000,
  connectTimeout: 10000,
});

mqttClient.on('connect', () => {
  console.log("Connected to MQTT");
  // mqttClient.subscribe('sinus');

  setInterval(() => {
    mqttClient.publish('sinus', Math.sin(Date.now() / 1000).toFixed(2));
  }, 500);
});

// mqttClient.on('message', (topic, message) => {
//   console.log(topic, message.toString());
// });

mqttClient.on('error', (e) => {
  console.error(e)
});
