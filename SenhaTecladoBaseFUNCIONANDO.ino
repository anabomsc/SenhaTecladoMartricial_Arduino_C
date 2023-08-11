#include <math.h>
#define TAM_MAXIMO_DA_SENHA 3

char letrasTeclado[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
int password = 123;
int tentativa = 0;
int contador = TAM_MAXIMO_DA_SENHA + 1;
int multiplicador = 1; 
void configuradoPortasParaTeclado(){
  //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
   
  //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

char imprimeTecla(int x, int y){
  Serial.println(letrasTeclado[x][y]);
  delay(10);
  return letrasTeclado[x][y];
}

char acionamentoDeTecla(bool *acionamentoConfirmado){
  for (int ti = 3; ti<7; ti++)
    {
      //Alterna o estado dos pinos das linhas
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(ti, HIGH);
      //Verifica se alguma tecla da coluna 1 foi pressionada
      if (digitalRead(8) == HIGH)
      {
        *acionamentoConfirmado = HIGH;
        return imprimeTecla(ti-3, 0);
        while(digitalRead(8) == HIGH){}
      }
   
      //Verifica se alguma tecla da coluna 2 foi pressionada    
      if (digitalRead(9) == HIGH)
      {
        *acionamentoConfirmado = HIGH;
        return imprimeTecla(ti-3, 1);
        while(digitalRead(9) == HIGH){};
      }
       
      //Verifica se alguma tecla da coluna 3 foi pressionada
      if (digitalRead(10) == HIGH)
      {
        *acionamentoConfirmado = HIGH;
        return imprimeTecla(ti-3, 2);
        while(digitalRead(10) == HIGH){}
      }
       
      //Verifica se alguma tecla da coluna 4 foi pressionada
      if (digitalRead(11) == HIGH)
      {
        *acionamentoConfirmado = HIGH;
        return imprimeTecla(ti-3, 3);
        while(digitalRead(11) == HIGH){} 
      }
   }
}

int converterCaracterParaNumero(char teclaPressionada){
  if(teclaPressionada == '1'){
    return 1;
  }

  if(teclaPressionada == '2'){
    return 2;
  }

  if(teclaPressionada == '3'){
    return 3;
  }

  if(teclaPressionada == '4'){
    return 4;
  }

  if(teclaPressionada == '5'){
    return 5;
  }

  if(teclaPressionada == '6'){
    return 6;
  }

  if(teclaPressionada == '7'){
    return 7;
  }

  if(teclaPressionada == '8'){
    return 8;
  }

  if(teclaPressionada == '9'){
    return 9;
  }

  if(teclaPressionada == '0'){
    return 0;
  }

  if(teclaPressionada == '*' || teclaPressionada == '#'){
    return -1;
  }

  if(teclaPressionada == 'A' || teclaPressionada == 'B' || teclaPressionada == 'C' || teclaPressionada == 'D'){
    return -1;
  }
}

int valorNumericoDasTeclas(bool *acionamentoConfirmado){
  return converterCaracterParaNumero(acionamentoDeTecla(&(*acionamentoConfirmado)));
}

void setup()
{
  configuradoPortasParaTeclado();
  
  pinMode(2, INPUT); // botao para resetar senha
  pinMode(12, OUTPUT); // LED vermelho para senha errada
  pinMode(13, OUTPUT); // LED verde para senha correta
  
  Serial.begin(9600);
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();

}
 
void loop()
{
   bool teclaPressionada = LOW;
   int tecla = valorNumericoDasTeclas(&teclaPressionada); // leitura do numero pressinado
   digitalWrite(13, LOW);
   digitalWrite(12, LOW);
   /*
   if(tecla == -1){// se a tecla não for numérica
    contador = TAM_MAXIMO_DA_SENHA;
    //multiplicador = 10^(contador - 1);
    multiplicador = 1;
    //for (int i = contador - 1;i >= 1; i--){
     // multiplicador *= 10;
    //}
    tentativa = 0;
    tecla = 0;
   }
*/
  if(tecla != -1){
   if(teclaPressionada){
    Serial.print("tecla = ");
    Serial.println(tecla);
    Serial.print("Tecla Pressionada. Tentativa = ");
    Serial.println(tentativa);
    contador--;
    multiplicador = 1;
    Serial.print("multiplicador = ");
    for (int i = contador - 1; i >= 1; i--)
    {
      multiplicador = multiplicador*10;
      Serial.print(multiplicador);
      Serial.print(" --> ");
    }
    Serial.println();
    //multiplicador = 10^(contador - 1);
    tentativa += tecla*multiplicador;
    Serial.print("tentiva depois = ");
    Serial.println(tentativa);
    Serial.print("Contador e multiplicador = ");
    Serial.print(contador);
    Serial.print(" e ");
    Serial.println(multiplicador);
    delay(100);
   }
   
   if(contador == 1){
    Serial.println("Checando tentativa...");
    delay(500);
    if(tentativa == password){
      Serial.println("Senha correta.");
      digitalWrite(13,  HIGH);
      digitalWrite(12, LOW);  
      delay(2000);
      contador = TAM_MAXIMO_DA_SENHA + 1;
      //multiplicador = 10^(contador - 1);
      multiplicador = 1;
      for(int i = contador - 1;i >= 1; i--){
      multiplicador *= 10;
      }
      tentativa = 0;
    }
    else{
      Serial.println("Senha incorreta. Aguarde 10 segundos para nova tentativa.");
      digitalWrite(13,  LOW);
      digitalWrite(12, HIGH);  
      delay(10000);
      contador = TAM_MAXIMO_DA_SENHA + 1;
      multiplicador = 1;
      for(int i = contador - 1;i <= 1; i--){
      multiplicador *= 10;
      }
      //multiplicador = 10^(contador - 1);
      tentativa = 0;
    }
   }
  }
   delay(100);
}
