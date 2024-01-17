import pandas as pd
import time
import datetime
import paho.mqtt.client as paho

broker = "mosquitto"
port = 1883
topic = "pv"


def main():
  client = paho.Client("PV_Data")
  client.on_connect = lambda _: print("Connected")
  client.connect(broker, port)

  data = pd.read_csv('2023_10.csv', delimiter=',')
  data = data.drop([0, 0])
  values = list(data.columns)[1:]
  data[values] = data[values].apply(pd.to_numeric)
  data['Datum und Uhrzeit'] = pd.to_datetime(
    data['Datum und Uhrzeit'], format='%d.%m.%Y %H:%M')

  data = data.set_index('Datum und Uhrzeit')

  data = data.groupby(data.index).sum()
  selectedcolumns = data[["Energie in Batterie gespeichert", "Energie aus Batterie bezogen", "PV Produktion", "Verbrauch",
                          "Energie vom Netz bezogen", "Direkt verbraucht", "Energie ins Netz eingespeist", "State of Charge"]].copy()

  for i in selectedcolumns.index:
    time.sleep(1)
    now = datetime.datetime.now()
    j = selectedcolumns.loc[i]
    j["time"] = now
    client.publish(topic, j.to_json())


if __name__ == "__main__":
  main()
