class Mode{
	public:

	float sensorValue;
	string mode;

	Mode(){}
	Mode(string _mode, float _sensorValue){
		this->mode = _mode;
		this->sensorValue = _sensorValue;
	}
	Mode( string _mode){
		this->mode = _mode;
		// Qué hacer con el valor?
	}
	void setSensorValue(float theValor){
		sensorValue = theValor;
		// ATENCIÓN CON ESTO. ESTO DEBE LLAMARSE AL INICIAR CADA BOT, PORQUE SI NO, TIRA NULL POINTER EXCEPTION.
	}

};