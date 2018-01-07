#ifndef DHT_WATCHER_H
#define DHT_WATCHER_H

class DHTWatcher : public Watcher {
public:
  DHTWatcher(int _model, int _pin, int _port, long _duration) : Watcher(_duration), model(_model), pin(_pin), port(_port) {
    this->init();
    PRINT("Initializing duration: %d\n", this->duration);
  }

  void loop(long time) {
    if (should_run(time)) {
      float h = this->driver->readHumidity();
      float t = this->driver->readTemperature();

      if (!isnan(t) && !isnan(h)) {
        PRINT("Temp: %.2f, Hum: %.2f\n", t, h);

        char out[50];
        snprintf(&out[0], 50, "{\"temp\":%.4f, \"hum\":%.4f}", t, h);
        send_json(this->port, &out[0]);
        this->set_executed(time);
      }
    }

  }

private:
  const int model;
  const int pin;
  const int port;
  DHT *driver;

  void init() {
    this->driver = new DHT(this->pin, this->model);
    if (!this->driver) {
      PRINT("Couldn't initialize the DHT driver");
    }

    this->driver->begin();
  }
};



#endif //DHT_WATCHER_H
