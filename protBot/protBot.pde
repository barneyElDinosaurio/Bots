int w = 400*2;
int h = 300*2;

float delta_angle = PI/15;

MovingBot elBot = new MovingBot();
MovingBot elOtroBot;// = new MovingBot();

PVector bebedero; 
float kAng = 0.03;
float friccionAngular = 0.05;

void setup() {
  smooth();
  size(w, h);
  bebedero = new PVector(300, 250);

  elOtroBot = new MovingBot( 300*0.1, 260*0.01 );  

  elBot.mueveteAqui( 300*0.1, 250*0.1);
  elBot.start();
}

void draw() {
  background(155);
  
  // *************** CALCULO PRELIMINAR *****************
  /*
  // Calcular Fuerza
  // Qué fuerzas calculamos?

  // ** Con el bebedero;

  float k = 0.01;
  PVector fuerza = new PVector();
  PVector distancia = PVector.sub( bebedero, elBot.pos);

  //fuerza.add( PVector.mult(distancia, k) );
  println("FUERZA BEB " + fuerza);
  
  
  // ** Con el otro Bot
  // exponencial

  float const_f = 10;
  PVector distBots = PVector.sub( elBot.pos, elOtroBot.pos );
  float r = distBots.mag();
  float magFuerza = const_f * exp(-r*r/200);
  PVector dirFuerza = new PVector(distBots.x, distBots.y);
  dirFuerza.normalize();
  PVector fuerzaBot = PVector.mult(dirFuerza, magFuerza);
  fuerza.add( fuerzaBot);
  println( "FUERZA BOT" + fuerzaBot );

  elBot.mueveteFuerza(fuerza);
  */
  
  //*********** LA VELOCIDAD COMO OSCILADOR AMORTIGUADO  (BOT + BEBEDERO )*************
  // Calcula el ángulo....
  
  if( elBot.timer.tiempo() < elBot.tiempoDeAvance){
    elBot.avanza();
  }
  else{
    elBot.timer.restart();
    PVector distancia = PVector.sub( bebedero , elBot.pos );
    //float angulo = PVector.angleBetween( elBot.vel , distancia );
    float angulo = distancia.heading() - elBot.vel.heading();
    println("angulo diff " + angulo*180/PI);
    elBot.recalculaVelocidad(angulo);
  }
  
  
  
  
  //*********** DIBUJO ************* 

  elBot.dibujate();
  elOtroBot.dibujate();
  fill(0, 0, 200);
  rect(bebedero.x, bebedero.y, 20, 20);
}

