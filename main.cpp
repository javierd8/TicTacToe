#include <iostream>
#include <time.h>
#include <random>

void tablero(char movimientos[]);
char victoria(char movimientos[],char simbolo);
int regMov(char movimientos[],char simbolo,int mov);
int oporWin(char movimientos[],char simbolo);
int centro(char movimientos[]);
int cpuMov(char movimientos[],char simbolo,int movAnt,int turno,char simboloContr);
int esquina(char movimientos[], int movAnt, int turno);
int borde(char movimientos[], int movAnt, int turno);

using namespace std;

//Movimientos se registran en un arreglo tam=9 (uno para cada player o una matriz(tam 2x9) para almacenar los 2)
int main(){
    int num=1,win=0,empate=0;
    while(num++){
        char movimientos[9]={'~','~','~','~','~','~','~','~','~'}; // ~ = Sin movimiento registrado | 'X' Movimiento P1 | 'O' Movimiento P2
        int movAnt=0,movSig=0;

        tablero(movimientos);
        cout<<"\n\n";
        for(int i=0;i<5;i++){

            movSig = cpuMov(movimientos,'X',movAnt,i,'O');
            movAnt = regMov(movimientos,'X',movSig); 

            tablero(movimientos);
            cout<<"\n\n";

            if(victoria(movimientos,'X')){
                cout<<"\n\nGanador es: X\n";
                win++;
                break;
            }

            if(i==4){ //Evita que se jueguen 10 turnos evitando el turno 5 de 'O' y declara empate
                cout<<"\n\nEmpate \n";
                empate++;
                break;
            }

            //movSig = cpuMov(movimientos,'O',movAnt,i,'X');
            //movAnt = regMov(movimientos,'O',movSig); 

            movAnt = regMov(movimientos,'O',-1);

            tablero(movimientos);
            cout<<"\n\n";
            if(victoria(movimientos,'O')){
                cout<<"\n\nGanador es: O\n";
                num=0; //Cuando pierde el 1er jugador el juego se pausa/termina
                break;
            }

        }
    }

    return 1;
}

//Grafico del tablero
void tablero(char movimientos[]){
    for(int i=1;i<10;i++){
        if(movimientos[i-1]!='~')
            cout<<movimientos[i-1];
            //cout<<i; //Simbologia del tablero
        else
            cout<<"~";
        if(!(i%3))
            (i!=9)?cout<<"\n-----\n":cout<<"" ;
        else
            cout<<"|";
    }
}

//Checa si alguien ya gano
char victoria(char movimientos[],char simbolo){
    //Regresa el simbolo del ganador o 0 para que siga el juego
    //CondiVictoria 1-2-3 | 1-5-9 | 1-4-7 | 2-5-8 | 3-5-7 | 3-6-9 | 4-5-6 | 7-8-9 Si alguno de esos tiene el mismo simbolo entonces WIN para el player del simbolo
    //Lo mismo pero acomodado a pos de arreglo
    /*CondiVictoria 0-1-2 |
                    0-4-8 |
                    0-3-6 |
                    1-4-7 |
                    2-4-6 |
                    2-5-8 |
                    3-4-5 |
                    6-7-8 Si alguno de esos tiene el mismo simbolo entonces WIN para el player del simbolo*/

    //Forma precaria en lo que pienso en como optimizar
    if(movimientos[0]==simbolo && movimientos[1]==simbolo && movimientos[2]==simbolo) //Horizontal
        return simbolo;
    if(movimientos[0]==simbolo && movimientos[4]==simbolo && movimientos[8]==simbolo) //Diagonal ascendente
        return simbolo;
    if(movimientos[0]==simbolo && movimientos[3]==simbolo && movimientos[6]==simbolo) //Vertical
        return simbolo;
    if(movimientos[1]==simbolo && movimientos[4]==simbolo && movimientos[7]==simbolo) //Vertical
        return simbolo;
    if(movimientos[2]==simbolo && movimientos[4]==simbolo && movimientos[6]==simbolo) //Diagonal descendente
        return simbolo;
    if(movimientos[2]==simbolo && movimientos[5]==simbolo && movimientos[8]==simbolo) //Vertical
        return simbolo;
    if(movimientos[3]==simbolo && movimientos[4]==simbolo && movimientos[5]==simbolo) //Horizontal
        return simbolo;
    if(movimientos[6]==simbolo && movimientos[7]==simbolo && movimientos[8]==simbolo) //Horizontal
        return simbolo;
    return 0;
}

//Registra el movimiento en el tablero con las debidas validaciones
int regMov(char movimientos[],char simbolo,int mov){
    //Si el mov es -1 entonces saca un random sino entonces se registra a donde indica
    if(mov==-1){
        int i;            
        do{         
            //Mucho mejor que rand()
            random_device rand;  
            mt19937 gen(rand());  
            uniform_int_distribution<>dis(0, 8);  
            i = dis(gen);  
        }while(movimientos[i]!='~'); //Mientras no sea un espacio en blanco se seguiran sacando randoms hasta que toque uno en blanco
        movimientos[i]=simbolo;
        return i;
    }else{
        movimientos[mov]=simbolo;
    }
    return mov;
}

//Jugar de forma automatica
//Reglas de comportamiento
/*
-IA siempre es primer movimiento (primer movimiento = modo ataque)
-El 2do jugador tendra movimientos random (aka otro jugador)
-La IA seleccionara su movimiento segun lo siguiente (Prioridad a->b->c->d y dentro ese el orden en que estan escritas las reglas):
a)Contraataque
    Tomar una WIN cuando se tenga la oportunidad
    Evitar un WIN del otro jugador en su sig turno (aka bloquearlo)
b)Centro
    Tomarlo en el primer turno o cuando se de la oportunidad
c)Esquina
    Modo ataque exclusivo(?) //Caso WIN del diagonal casi asegurado
        Cuando sea nuestro 2do turno, el otro jugador haya jugado esquina en su 1er turno y tengamos el centro
            en este caso jugamos la esquina opuesta al del otro jugador
                en caso de que en el sig turno del otro jugador juegue un borde entonces jugamos la esquina opuesta a ese borde
                y tenemos WIN asegurada (4 de 6 de las casillas libres lo asegura)
                Sino entonces fallo la asegurada y seguimos jugando (Activar bandera de win diagonal fallada)
    Cuando el otro jugador haya jugado borde y haya fallado el "WIN de linea casi asegurado"
        en este caso jugamos una esquina adyacente al movimiento del otro jugador
d)Borde
    Modo ataque exclusivo(?) //Caso WIN de linea casi asegurado
        Cuando sea nuestro 2do turno y el otro jugador haya jugado borde en su 1ro y tengamos el centro
            en este caso jugamos el borde opuesto al del 1er jugador
                en caso de que en el sig turno del otro jugador juegue un borde entonces jugamos la esquina adyacente a una pieza nuestra
                y tenemos WIN asegurada (2 de 6 de las casillas libres lo asegura)
                Sino entonces fallo la asegurada y seguimos jugando (Activar bandera de win linea fallada)
    Cuando el 1er jugador haya jugado esquina
        en este caso jugamos un borde adyacente al movimiento del 1er jugador
*/
//Lista de movimientos de la IA (o cpu no se como llamarle pero la funcion dira cpu)
int cpuMov(char movimientos[],char simbolo,int movAnt,int turno,char simboloContr){
    int mov=-1;
    mov = oporWin(movimientos,simbolo); //Checa por una Win
    if(mov!=-1)
        return mov;
    mov = oporWin(movimientos,simboloContr); //Checa por una Lose
    if(mov!=-1)
        return mov;
    mov = centro(movimientos); //Checa para agarrar centro
    if(mov!=-1)
        return mov;
    mov = esquina(movimientos,movAnt,turno); //Checa para agarrar esquina
    if(mov!=-1)
        return mov;
    mov = borde(movimientos,movAnt,turno); //Checa para agarrar borde
    if(mov!=-1)
        return mov;
    return mov;
}

//Checa por una oportunidad de ganar- Retorna posMatriz de la casilla para ganar o -1 si no la hay (Esta madre se convirtio en contraataque sin querer xd)
int oporWin(char movimientos[],char simbolo){
    int contSim=0,contVac=0,posVac=-1;
    //Checa el tablero en busca de oportunidades de ganar(?)
    //Recorre el tablero contando nuestros simbolos y espacios en blanco, si llega a 2 simbolos y 1 blanco es win sino cont=0 y sig linea
    for(int i=0;i<9;i++){ //Busca en horizontal
        if(movimientos[i]=='~'){ //Checa si es espacio en blanco
            contVac++;
            posVac=i;
            if(contVac>1){ //Si hay mas 2 espacio entonces sig linea
                i+=3-contSim-contVac;
            }
        }else{
            if(movimientos[i]==simbolo) //Checa si es simbolo nuesto
                contSim++;
            else                        //Sino entonces sig linea
                i+=2-contSim-contVac;
        }
        if(contSim==2 && contVac==1){    //Si hay oportunidad de win entonces regresa la pos en la matriz
            //cout<<"horizontal";
            return posVac;
        }
        if(!((i+1)%3)){ //Si es sig linea entonces cont=0
            contSim=0;
            contVac=0;
        }
    }

    for(int i=0;i<3;i++){  //Busca en vertical
        for(int j=0;j<3;j++){
            if(movimientos[i+j*3]=='~'){ //Checa si es espacio en blanco
                contVac++;
                posVac=i+j*3;
                if(contVac>1){ //Si hay mas 2 espacio entonces sig linea
                    j+=3-contSim-contVac;
                }
            }else{
                if(movimientos[i+j*3]==simbolo) //Checa si es simbolo nuesto
                    contSim++;
                else                        //Sino entonces sig linea
                    j+=2-contSim-contVac;
            }
            if(contSim==2 && contVac==1){    //Si hay oportunidad de win entonces regresa la pos en la matriz
                //cout<<"vertical";
                return posVac;
            }
            if(!((j+1)%3)){ //Si es sig linea entonces cont=0
                contSim=0;
                contVac=0;
            }
        }
    }

    for(int i=0;i<9;i+=4){ //Busca en diagonal ascendente (?)
        if(movimientos[i]=='~'){ //Checa si es espacio en blanco
                contVac++;
                posVac=i;
            }else{
                if(movimientos[i]==simbolo) //Checa si es simbolo nuesto
                    contSim++;
            }
            if(contSim==2 && contVac==1)    //Si hay oportunidad de win entonces regresa la pos en la matriz
                return posVac;
    }

    contSim=0;
    contVac=0;

    for(int i=2;i<7;i+=2){ //Busca en diagonal descendente (?) (No se me ocurrio una forma de automatizar jeje)
        if(movimientos[i]=='~'){ //Checa si es espacio en blanco
                contVac++;
                posVac=i;
            }else{
                if(movimientos[i]==simbolo) //Checa si es simbolo nuesto
                    contSim++;
            }
            if(contSim==2 && contVac==1)    //Si hay oportunidad de win entonces regresa la pos en la matriz
                return posVac;
    }

    return -1;
}

//Centro (Nada que decir se explica solo xd)
int centro(char movimientos[]){
    if(movimientos[4]=='~')
        return 4;
    return -1;
}

//Si se cumple la condicion jugamos una esquina sino no
int esquina(char movimientos[], int movAnt, int turno){
    //Dependiendo del movimiento anterior y el turno actual se juega de una forma u otra
    //Caso WIN del diagonal
    /*if(turno<3)
        if((movAnt+1)%2 && movAnt!=5){ //Checa si es impar(esquina) y que no sea el centro(que tambien es impar)

        }
    else*/
        if(!((movAnt+1)%2)) //Checa si es par(borde)
            switch (movAnt){
            case 1:
                if(movimientos[0]=='~')
                    return 0;
                if(movimientos[2]=='~')
                    return 2;
                break;
            case 3:
                if(movimientos[0]=='~')
                    return 0;
                if(movimientos[6]=='~')
                    return 6;
                break;
            case 5:
                if(movimientos[2]=='~')
                    return 2;
                if(movimientos[8]=='~')
                    return 8;
                break;
            case 7:
                if(movimientos[6]=='~')
                    return 6;
                if(movimientos[8]=='~')
                    return 8;
                break;
            }
    return -1;
}


//Si se cumple la condicion jugamos un borde sino no
int borde(char movimientos[], int movAnt, int turno){
    //Dependiendo del movimiento anterior y el turno actual se juega de una forma u otra
    //Caso WIN del diagonal
    /*if(turno<3)
        if((movAnt+1)%2 && movAnt!=5){ //Checa si es impar(esquina) y que no sea el centro(que tambien es impar)

        }
    else*/
        if((movAnt+1)%2) //Checa si es impar(esquina)
            switch (movAnt){
            case 0:
                if(movimientos[1]=='~')
                    return 1;
                if(movimientos[3]=='~')
                    return 3;
                break;
            case 2:
                if(movimientos[1]=='~')
                    return 1;
                if(movimientos[5]=='~')
                    return 5;
                break;
            case 6:
                if(movimientos[3]=='~')
                    return 3;
                if(movimientos[7]=='~')
                    return 7;
                break;
            case 8:
                if(movimientos[5]=='~')
                    return 5;
                if(movimientos[7]=='~')
                    return 7;
                break;
            }
    return -1;
}
