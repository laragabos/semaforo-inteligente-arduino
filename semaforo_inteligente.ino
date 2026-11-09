// Indicação das portas que serão utilizadas
const int verdeCarro = 8;
const int amareloCarro = 9;
const int vermelhoCarro = 10;

const int verdePedestre = 11;
const int vermelhoPedestre = 12;

const int botao = 2;

// Utilizando o cronometro do arduino
int estado = 0;
unsigned long tempo = 0;

// Ações que acontecerão apenas uma vez
void setup()
{
    // Inicio da comunicação com o Monitor Serial
    Serial. begin(9600); 
    
    pinMode(verdeCarro, OUTPUT);
    pinMode(amareloCarro, OUTPUT);
    pinMode(vermelhoCarro, OUTPUT);

    pinMode(verdePedestre, OUTPUT);
    pinMode(vermelhoPedestre, OUTPUT);

    pinMode(botao, INPUT_PULLUP);

    digitalWrite(verdeCarro, HIGH);
    digitalWrite(vermelhoPedestre, HIGH);
}

// Ações que se repetirão em loop
void loop()
{
    switch(estado)
    {
      case 0:
        if (digitalRead(botao) == LOW)
        {
        tempo = millis();
        estado = 1;
        }
    break;

    case 1:
      if(millis() - tempo >= 2000)
    {
        digitalWrite(verdeCarro, LOW);
        digitalWrite(amareloCarro, HIGH);
        tempo = millis();
        estado = 2;
    }
    break;

    case 2:
      if(millis() - tempo >= 2000)
      {
        digitalWrite(amareloCarro, LOW);
        digitalWrite(vermelhoCarro, HIGH);

        digitalWrite(vermelhoPedestre, LOW);
        digitalWrite(verdePedestre, HIGH);
        Serial.println("Travessia liberada!");
        tempo = millis();
        estado = 3;
      }
      break; 

      case 3:
        if(millis() - tempo >= 5000)
        {
        digitalWrite(verdePedestre, LOW);
        digitalWrite(vermelhoPedestre, HIGH);
        Serial.println("Travessia encerrada");

        digitalWrite(vermelhoCarro, LOW);
        digitalWrite(verdeCarro, HIGH);
        estado = 0;
        }
      break;
    }
  }