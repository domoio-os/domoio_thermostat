#include <Arduino.h>
#include <FS.h>

#include "domoio.h"
#include "DHT.h"
#include "dht_watcher.h"

Port *relay_1 = NULL;

void setup() {
  // This macro is needed to make sure that all the dependencies are loaded
  // TODO: fix it?
  __FIX_COMPILER_ISSUES;

  // Internal LED
  Port *state_led = new Port();
  state_led->id = 16;
  state_led->port_type = PORT_DIGITAL;
  state_led->io = PORT_OUTPUT;
  state_led->active_low = true;
  setup_port(state_led);
  domoio::set_led_port(state_led);

  // Reset BTN
  Port *reset_port = new Port();
  reset_port->id = 0;
  reset_port->port_type = PORT_DIGITAL;
  reset_port->io = PORT_INPUT;
  setup_port(reset_port);
  domoio::set_reset_port(reset_port);

  // Relay 1  // Relay 2
  relay_1 = new Port();
  relay_1->id = D1; //
  relay_1->port_type = PORT_DIGITAL;
  relay_1->io = PORT_OUTPUT;
  relay_1->active_low = true;
  setup_port(relay_1);

  Port *relay_2 = new Port();
  relay_2->id = D2; //
  relay_2->port_type = PORT_DIGITAL;
  relay_2->io = PORT_OUTPUT;
  relay_2->active_low = true;
  setup_port(relay_2);


  // Check the temperature everty 2 minutes
  DHTWatcher *dht_watcher = new DHTWatcher(DHT11, D5, 101, 120 * 1000);
  setup_watcher(dht_watcher);

  domoio::setup();
}


void loop() {
  domoio::loop();
}


void reset_btn_callback() {
  int value = relay_1->value == 1 ? 0 : 1;
  relay_1->set_value(value);
  IntMessageValue message_value(relay_1->id, value);
  send_port_change(&message_value);
}

void handle_event(event_type type, void * payload) {
}
