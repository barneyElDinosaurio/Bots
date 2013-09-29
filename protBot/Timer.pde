class Timer {
  int tiempoDeInicio;
  boolean started = false;
  Timer() {
  }
  void start() {
    tiempoDeInicio = millis();
    started = true;
  }
  int tiempo() {
    if (started) {
      return(millis() - tiempoDeInicio);
    }
    else {
      return(0);
    }
  }
  void restart() {
    started = true;
    start();
  }
}

