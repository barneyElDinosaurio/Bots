int w = 400*2;
int h = 300*2;

float delta_angle = PI/15;

MovingBot elBot = new MovingBot();
MovingBot elOtroBot;// = new MovingBot();

PVector bebedero; 
Obstacle obstaculo;

float kAng = 0.03;
float kAng2 = 0.25;
float kRepulsion = 0.25;
float friccionAngular = 0.05;
boolean loop;

float distanciaColision;

void setup() {
  smooth();
  size(w, h);
  bebedero = new PVector(300, 300);
  obstaculo = new Obstacle( new PVector( 270, 270), 10 ) ;
  distanciaColision = 40;

  elOtroBot = new MovingBot( 300*0.1, 260*0.01 );  

  elBot.mueveteAqui( 300*0.1, 250*0.1);
  elBot.start();
  elBot.setComputingMode("vel");
  loop = true;
}

void draw() {
  background(155);
  
  //*********** DIBUJO ************* 

  elBot.dibujate();
  noFill();
  ellipse(elBot.pos.x, elBot.pos.y , distanciaColision/2, distanciaColision/2 );
  elOtroBot.dibujate();
  fill(0, 0, 200);
  rect(bebedero.x, bebedero.y, 20, 20);

  line(elBot.pos.x, elBot.pos.y, bebedero.x, bebedero.y);

  // OBSTACULO
  //PVector distanciaObstaculo = PVector.sub(obstaculo, elBot.pos);
  line( obstaculo.pos.x, obstaculo.pos.y, elBot.pos.x, elBot.pos.y);
  obstaculo.dibujate();

  //*********** LA VELOCIDAD COMO OSCILADOR AMORTIGUADO  (BOT + BEBEDERO )*************
  // Calcula el ángulo....

  if ( elBot.timer.tiempo() < elBot.tiempoDeAvance) {
    elBot.avanza();
  }
  else {
    elBot.timer.restart();
    elBot.computeAngleAttractor(bebedero);
    elBot.computeAngleObstacle(obstaculo);
    elBot.recalculaVelocidad();
    
   
  }

  
}

float deltaAngle(PVector v1, PVector v2 ) {
  /*
Función que calcula la diferencia angular (CON SIGNO), entre dos vectores.
   El ángulo de v2 - el ángulo de v1
   */

  float angle = PVector.angleBetween(v1, v2);
  PVector signVector = v1.cross(v2);
  angle*= signOf( signOf( signVector.z ) );

  println("SV: " + signVector);

  return(angle);
}
int signOf(float num) {
  if ( num >= 0) {
    return(1);
  }
  else {
    return(-1);
  }
}

void keyPressed() {
  if (key == ' ') {
    loop = !loop;
  }
  if (loop) {
    loop();
  }
  else {
    noLoop();
  }
}

