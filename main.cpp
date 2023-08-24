#include <iostream>
void tablero(char movimientos[]);
int victoria(char movimientos[],char simbolo);
void regMov(char movimientos[],char simbolo);
using namespace std;

//Movimientos se registran en un arreglo tam=9 (uno para cada player o una matriz(tam 2x9) para almacenar los 2)
int main(){
    char movimientos[9]={'X','X','~','O','O','~','~','~','~'}; // ~ = Sin movimiento registrado | 'X' Movimiento P1 | 'O' Movimiento P2
    
    tablero(movimientos);
    regMov(movimientos,'O');
    cout<<"\n\n";
    tablero(movimientos);
    cout<<victoria(movimientos,'O');
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
int victoria(char movimientos[],char simbolo){ 
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
        return 1;
    if(movimientos[0]==simbolo && movimientos[4]==simbolo && movimientos[8]==simbolo)
        return 2;
    if(movimientos[0]==simbolo && movimientos[3]==simbolo && movimientos[6]==simbolo)
        return 3;
    if(movimientos[1]==simbolo && movimientos[4]==simbolo && movimientos[7]==simbolo)
        return 4;
    if(movimientos[2]==simbolo && movimientos[4]==simbolo && movimientos[6]==simbolo)
        return 5;
    if(movimientos[2]==simbolo && movimientos[5]==simbolo && movimientos[8]==simbolo)
        return 6;
    if(movimientos[3]==simbolo && movimientos[4]==simbolo && movimientos[5]==simbolo)
        return 7;
    if(movimientos[6]==simbolo && movimientos[7]==simbolo && movimientos[8]==simbolo)
        return 8;
    return 0;
}

//registrarMovimiento(movimientos)
void regMov(char movimientos[],char simbolo){
    //Pide la posicion (1-9) y coloca el simbolo(auto o pedira simbolo?) ahi
    int i=6;
    //cin>>i;
    movimientos[i-1]=simbolo;
}