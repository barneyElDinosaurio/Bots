int w = 400*2;
int h = 300*2;

float delta_angle = PI/15;

MovingBot elBot = new MovingBot();
MovingBot elOtroBot;// = new MovingBot();

PVector bebedero; 
float kAng = 0.03;
float friccionAngular = 0.05;
boolean loop;
void setup() {
  smooth();
  size(w, h);
  bebedero = new PVector(300, 250);

  elOtroBot = new MovingBot( 300*0.1, 260*0.01 );  

  elBot.mueveteAqui( 300*0.1, 250*0.1);
  elBot.start();
  elBot.setComputingMode("vel");
  loop = true;
}

void draw() {
  background(155);
  /*if(loop == true){
    loop();
  }else{
    noLoop();
  }*/
  
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
    
    // Vector que une la posición del bot actual con el destino.
    PVector distancia = PVector.sub( bebedero , elBot.pos );
    
    // Ángulo entre los dos vectores. Atención con el cálculo, porque hay que hacerle un wrap para que quede entre -pi y pi
    //float angulo = PVector.angleBetween( elBot.vel , distancia );
    
    
    //float angulo = deltaAngle( elBot.vel , distancia);
    float angulo2 = distancia.heading() - elBot.vel.heading();
    float angulo = deltaAngle(elBot.vel, distancia);
    println("--------- comparacion entre angulos");
    println(angulo);
    println(angulo2);
    println("-------");
    
    println("angulo diff " + angulo*180/PI);
    if(angulo > PI || angulo < -PI){
      println("WARNING ::: El ángulo no está siendo medido en el intervalo correcto");
      noLoop();
    }
    elBot.recalculaVelocidad(angulo);
  }
  
  //*********** DIBUJO ************* 

  elBot.dibujate();
  elOtroBot.dibujate();
  fill(0, 0, 200);
  rect(bebedero.x, bebedero.y, 20, 20);
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

void keyPressed(){
  if(key == ' '){
    loop = !loop;
  }
  if(loop){
    loop();
  }else{
  noLoop();
  }
}
  
