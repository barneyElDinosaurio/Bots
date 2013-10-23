class MovingBot {
  PVector pos;
  PVector pos_old;

  color c = color(random(255), random(255), random(255));

  float tiempoDeAvance = 500;



  float tam = 15;
  float m = 1;

  Timer timer = new Timer();
  // Consistencia
  PVector vel = new PVector(1, 0, 0);
  float angle = 0;

  float vel_ang;

  String computingMode;


  MovingBot(float _x, float _y) {
    pos = new PVector();
    pos.set(_x, _y, 0);
    pos_old = new PVector();
    pos_old.set(pos);
    computingMode = "acc";

    // Siempre ajustar angulo y velocidad
  }
  MovingBot() {
    pos = new PVector(); // cero por defecto
    pos_old = new PVector(); // idem
    computingMode = "acc";
  }
  void dibujate() {
    pushMatrix();
    translate(pos.x, pos.y);
    rotate(angle);
    line(0, 0, 20, 0);
    fill(c);
    ellipse(0, 0, 1.5*tam, tam);
    popMatrix();
  }
  void mueveteAqui(float x, float y) {
    //      pos_old.set( pos.x, pos.y , 0);
    pos.set(x, y, 0);
  }
  void setComputingMode(String _s) {
    computingMode = _s;
  }
  void avanza() { // ?
    pos_old.set(pos);
    pos.add(vel);
    // PVector delta = PVector.sub(pos, pos_old);
    // angle = atan2(delta.y, delta.x);
  }
  void mueveteFuerza(PVector fuerza) {
    pos_old.set(pos);
    vel.add(PVector.mult(fuerza, 1/m));
    pos.add(vel);
  }
  void rota() {
    angle += delta_angle;
  }
  void rotaAqui(float _angle) {
    angle = _angle;
  }
  void setMasa(float _m) {
    m = _m;
  }
  void recalculaVelocidad(float anguloDiff) {
    if (computingMode == "acc") {

      //Opción 1: USAR LA ACELERACIÓN ANGULAR, ES DECIR, USAR UNA ESPECIE DE FUERZAS ANGULARES. IGUAL QUE NEWTON, PERO CON ÁNGULOS
      println("COMPUTING MODE: " + computingMode);
      float acc_angular = kAng * anguloDiff ;//- friccionAngular*vel_ang;
      vel_ang += acc_angular;
      println("vel_ang : " + vel_ang*180/PI);
      angle+=vel_ang;
      angle = angle % (2*PI);
      vel = PVector.fromAngle(angle);
    }
    else if (computingMode == "vel") {
      /* 
       Opción 2: USAR LA VELOCIDAD ANGULAR, ES DECIR, HACER ÁNGULO += K*DELTA_ÁNGULO. NO ESTOY SEGURO DE CUÁL ES LA
       DIFERENCIA CON EL MÉTODO ANTERIOR. CREO QUE LA DIFERENCIA ES QUE CON EL OTRO SE OBTIENE UN OSCILADOR AMORTIGUADO, Y
       EN ESTE CASO HAY UNA CONVERGENCIA EXPONENCIAL 
       */
       
       vel_ang += kAng * anguloDiff;
       angle+=vel_ang;
      angle = angle % (2*PI);
      vel = PVector.fromAngle(angle);
       
    }
    else{
      println("WARNING ::  wrong computing mode !!!!");
    }
  }
  
  void start() {
    timer.start();
  }
}

