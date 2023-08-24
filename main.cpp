#include <iostream>
void tablero(char movimientos[]);
char victoria(char movimientos[],char simbolo);
int regMov(char movimientos[],char simbolo);
int autoMov(char movimientos[],char simbolo,int movAnt);
void test(char movimientos[]);

using namespace std;

//Movimientos se registran en un arreglo tam=9 (uno para cada player o una matriz(tam 2x9) para almacenar los 2)
int main(){
    char movimientos[9]={'~','~','~','~','~','~','~','~','~'}; // ~ = Sin movimiento registrado | 'X' Movimiento P1 | 'O' Movimiento P2
    int movAnt=0;
    /*
    tablero(movimientos);
    regMov(movimientos,'O');
    cout<<"\n\n";
    tablero(movimientos);
    cout<<victoria(movimientos,'O');
    */

    tablero(movimientos);
    for(int i=0;i<5;i++){
        movAnt = regMov(movimientos,'X');
        cout<<"\n\n";
        //tablero(movimientos);
        if(victoria(movimientos,'X')){
            cout<<"\n\nGanador es: X\n";
            break;
        }

        if(i==4){ //Evita que se jueguen 10 turnos evitando el turno 5 de 'O' y declara empate
            cout<<"\n\nEmpate \n";
            break;
        }
        movAnt = autoMov(movimientos,'O',movAnt);
        //tablero(movimientos);
        cout<<"\n\n";
        if(victoria(movimientos,'O')){
            cout<<"\n\nGanador es: O\n";
            break;
        }

    }

    return 1;
}

//nombreFuncion(Parametros)

//Grafico del tablero(matrizMovimientos)
void tablero(char movimientos[]){
    /* Impresion con doble for (Descartado)
    for(int i=0;i<3;i++){
        for(int j=1;j<6;j++){
            if(j%2){
                cout<<i+j;
            }else{
                cout<<"|";
            }
        }
        if(i!=2)
            cout<<"\n-----\n";
    }
    */
    //
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

//ChecarPorVictoriaEnUnTurno(matrizMovimientos)
char victoria(char movimientos[],char simbolo){
    //Regresa el simbolo del ganador o algo(por decidir) para que siga el juego
    //Si esta por perder en un turno entonces poner pieza para evitarlo sino entonces ponerla de forma adjacente(a donde lo puso el rival) donde no hayamos ocupado ya esa linea
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
    if(movimientos[0]==simbolo && movimientos[1]==simbolo && movimientos[2]==simbolo)
        return simbolo;
    if(movimientos[0]==simbolo && movimientos[4]==simbolo && movimientos[8]==simbolo)
        return simbolo;
    if(movimientos[0]==simbolo && movimientos[3]==simbolo && movimientos[6]==simbolo)
        return simbolo;
    if(movimientos[1]==simbolo && movimientos[4]==simbolo && movimientos[7]==simbolo)
        return simbolo;
    if(movimientos[2]==simbolo && movimientos[4]==simbolo && movimientos[6]==simbolo)
        return simbolo;
    if(movimientos[2]==simbolo && movimientos[5]==simbolo && movimientos[8]==simbolo)
        return simbolo;
    if(movimientos[3]==simbolo && movimientos[4]==simbolo && movimientos[5]==simbolo)
        return simbolo;
    if(movimientos[6]==simbolo && movimientos[7]==simbolo && movimientos[8]==simbolo)
        return simbolo;
    return 0;
}

//registrarMovimiento(movimientos)
int regMov(char movimientos[],char simbolo){
    //Pide la posicion (1-9) y coloca el simbolo(auto o pedira simbolo?) ahi
    int i;
    do{
        cout<<"\nIngrese la posicion (1-9): "<<simbolo<<"\n";
        cin>>i;
    }while(movimientos[i-1]!='~');

    movimientos[i-1]=simbolo;

    tablero(movimientos);
}

//Moverse de forma automatica
int autoMov(char movimientos[],char simbolo,int movAnt);{
    //Evalua el movimiento anterior(sino entonces agarra el centro) y envase a eso decide que hacer
    if(!movAnt){ //Si no hubo movimiento anterior entonces elige el centro
        movimientos[4]=simbolo;
        return 5;
    }


}
