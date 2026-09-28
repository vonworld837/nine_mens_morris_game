#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;

void mostrar_tablero(vector<string>&tablero); //funcion para mostrar el tablero
bool verificartriada(vector<string>&tablero, string &jugador, int &posicion); //funcion para ver si los jugadores formaron triadas
void eliminarficha(vector<string>&tablero, string &jugador, int &posicion, int &fichastotalesj1, int &fichastotalesj2); //funcion para eliminar una ficha
bool es_adyacente(int origen, int destino); //ver si la posición adyacente está vacía o no
bool todasenTriada(vector<string>& tablero, string& oponente); //funcion para verificar si todas las fichas del oponente están en una tríada
int victoria(int &fichastotalesj1, int &fichastotalesj2); //verificar si un jugador tiene 2 fichas
bool victoriaporadyacente(vector<string>&tablero, string &jugador); //función para determinar si todos las fichas de un jugador no tiene posiciones adyacentes vacías

int main() {
    //tablero para que puedan ver los jugadores las posciones 
    vector<string> tablero = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
    bool juegoTerminado = false; //determinar si el juego terminó o no 
    //cantidad de fichas iniciales por jugador
    int fichastotalesj1 = 9;
    int fichastotalesj2 = 9;
    //cantidad de movimientos disponibles en la fase de colocación
    int fichas_jugador1 = 9; 
    int fichas_jugador2 = 9;
    string jugador = "X"; //empezar con jugador X

    mostrar_tablero(tablero);

    while (fichas_jugador1>0 || fichas_jugador2>0){ //hasta que las todas las fichas de los jugadores estén en el tablero
        int posicion;
        cout<<"Jugador "<<jugador<<" ingrese su ficha en la posicion: ";
        cin>>posicion;
        while ((posicion<0)||(posicion>23)||(tablero[posicion] == "X")||(tablero[posicion] == "O")){ //para ver si la casilla está ocupada o no
            cout<<"Posicion no valida, intente de nuevo"<<endl;
            cout<<"Jugador "<<jugador<<" ingrese su ficha en la posicion: ";
            cin>>posicion;
        }

        tablero[posicion] = jugador;

        if (jugador == "X") { //reducir cantidad de fichas fuera del tablero
            fichas_jugador1 -= 1;
        } else {
            fichas_jugador2 -= 1;
        }

        mostrar_tablero(tablero);
        //verificar si el jugador formo una triada
        bool comprobartriada = verificartriada(tablero, jugador, posicion); 

        //si existe una triada
        if(comprobartriada==true){
            cout<<"Jugador "<<jugador<<" formo una triada\n";
            string oponente = (jugador == "X") ? "O" : "X"; 

            if(todasenTriada(tablero, oponente)){ //si todas las fichas del oponente están en triadas, puede eliminar cualquier ficha
                cout<<"Todas las fichas del jugador "<<oponente<<" estan en una triada, se puede eliminar cualquier ficha\nPosicion: ";
                cin>>posicion;
                while (
                    (posicion<0) || (posicion>23) || (tablero[posicion] != oponente) //ver que la ficha al eliminar sea del oponente
                ){
                    cout<<"Esta ficha no es del oponente, intente de nuevo\nElimine una ficha del oponente: ";
                    cin>>posicion;
                }
                eliminarficha(tablero, jugador, posicion, fichastotalesj1, fichastotalesj2);
                mostrar_tablero(tablero);
            } else { //si no todas las fichas estan en triadas, se elimina una ficha del oponente
                cout<<"Elimine una ficha del oponente, Posicion: ";
                cin>>posicion;
                //comprobar que el movimiento sea valido
                while (
                    (posicion<0) || (posicion>23) || (tablero[posicion] != oponente) || 
                    (verificartriada(tablero, oponente, posicion)) //verificar que la ficha a eliminar no esté en una triada
                ){
                    cout<<"Movimiento no valido, intente de nuevo\nElimine una ficha del oponente: ";
                    cin>>posicion;
                }
                //si es valido, se elimina la ficha
                eliminarficha(tablero, jugador, posicion, fichastotalesj1, fichastotalesj2);
                mostrar_tablero(tablero);
                //ver si gana el jugador al reducir las fichas (por si acaso)
                int verificarvictoria = victoria(fichastotalesj1, fichastotalesj2);
                if (verificarvictoria==1) {
                    cout << "Jugador O gana ya que el jugador X tiene 2 fichas.\n";
                    juegoTerminado = true; //bool termina, rompe el while y ya no continua
                    break;
                }
                if (verificarvictoria==2) {
                    cout << "Jugador X gana ya que el jugador O tiene 2 fichas.\n";
                    juegoTerminado = true;
                    break;
                }
            }
        }
        jugador = (jugador == "X") ? "O" : "X"; //cambiar de jugador
    }

    //si en la primera fase nadie ganó, empieza la fase de movimiento
    if(!juegoTerminado){
        cout<<"\nTodas las fichas estan en el tablero, comienza la fase de movimiento\n";
    
        while (true) {
        // Para verificar las condiciones de victoria
        int verificarvictoria = victoria(fichastotalesj1, fichastotalesj2);
        if (verificarvictoria==1) {
            cout << "Jugador O gana ya que el jugador X tiene 2 fichas.\n";
            break;
        }
        if (verificarvictoria==2) {
            cout << "Jugador X gana ya que el jugador O tiene 2 fichas.\n";
            break;
        }
        
        //Ver si la ficha a mover es suya
        int origen, destino;
        cout << "Jugador " << jugador << " seleccione una ficha para mover (posicion actual): ";
        cin >> origen;

        while ((origen < 0) || (origen > 23) || (tablero[origen] != jugador)) {
            cout << "Posicion invalida. Seleccione una de sus fichas: ";
            cin >> origen;
        }

        // Si el jugador tiene más de 3 fichas, verificar que haya una adyacente libre
        if (!((jugador == "X" && fichastotalesj1 == 3) || (jugador == "O" && fichastotalesj2 == 3))) {
            //si todas las posiciones no están libres, el jugador pierde
            bool adyacentesocupadas = victoriaporadyacente(tablero, jugador);
            if (adyacentesocupadas){
                string oponente = (jugador == "X") ? "O" : "X";
                cout<<"Todas las fichas del jugador "<<jugador<<" no tienen posiciones adyacentes disponibles\nGana jugador "<<oponente; 
                juegoTerminado = true; //ya no se ejecuta el while
                break;
            }
            //si tiene al menos una adyacente libre, verificar que la fica que escogió tenga adyacentes libres, si no tiene que escoger otra 
            bool puede_mover = false;
            for (int i = 0; i < 24; i++) {
                if (es_adyacente(origen, i) && tablero[i] != "X" && tablero[i] != "O") {
                    puede_mover = true;
                    break;
                }
            }

            if (!puede_mover) {
                cout << "Esa ficha no tiene espacios adyacentes libres. Escoja otra ficha.\n";
                continue;
            }
        }       

        //si el jugador solo tiene 3 fichas, entra a la fase de vuelo
        if (((jugador == "X")&&(fichastotalesj1==3)) || ((jugador == "O")&&(fichastotalesj2==3))){
            cout<<"Jugador "<<jugador<<" solo tiene 3 fichas, puede mover a cualquier espacio vacio\nposicion: ";
            cin >> destino;
            while ((destino < 0) || (destino > 23) || (tablero[destino] == "X") || (tablero[destino] == "O")) {//verificar que la posicion esté vacía
                cout << "Movimiento invalido. Seleccione de nuevo la ficha a mover: ";
                cin >> destino;
            }
        } else { //Si tiene más de 3 fichas, se mantiene en la fase de movimiento
            cout << "Jugador " << jugador << " seleccione la posicion adyacente vacia a donde mover: ";
            cin >> destino;

            while ((destino < 0) || (destino > 23) || (tablero[destino] == "X") || (tablero[destino] == "O") || !es_adyacente(origen, destino)) {
                cout << "Movimiento invalido. Seleccione una posicion adyacente vacia: "; //verificar que la posición adyacentes que escogió esté libre
                cin >> destino;
            }
        }

        // realiza el movimiento
        tablero[destino] = jugador;
        tablero[origen] = to_string(origen); // dejar la posición anterior libre con su número original

        mostrar_tablero(tablero);

        //verificar triada en el turno del jugador
        bool comprobartriada = verificartriada(tablero, jugador, destino); 

        //si existe una triada, se elimina una ficha del oponente
        if(comprobartriada==true){
            cout<<"Jugador "<<jugador<<" formo una triada\n";
            string oponente = (jugador == "X") ? "O" : "X"; 

            if(todasenTriada(tablero, oponente)){ //si todas las fichas del oponente están en triadas, puede eliminar cualquiera del oponente
                cout<<"Todas las fichas del jugador "<<oponente<<" estan en una triada, se puede eliminar cualquier ficha\nPosicion: ";
                int eliminar;
                cin>>eliminar;
                while (
                    (eliminar<0) || (eliminar>23) || (tablero[eliminar] != oponente) //ver que la ficha al eliminar sea del oponente
                ){
                    cout<<"Movimiento no valido, intente de nuevo\nElimine una ficha del oponente: ";
                    cin>>eliminar;
                }
                eliminarficha(tablero, jugador, eliminar, fichastotalesj1, fichastotalesj2);
                mostrar_tablero(tablero);
            } else { //si no todas las fichas estan en triadas, se elimina una ficha del oponente
                cout<<"Elimine una ficha del oponente, Posicion: ";
                int eliminar;
                cin>>eliminar;
                //comprobar que el movimiento sea valido
                while (
                    (eliminar<0) || (eliminar>23) || (tablero[eliminar] != oponente) || 
                    (verificartriada(tablero, oponente, eliminar)) //verificar que la ficha a eliminar no esté en una triada
                ){
                    cout<<"Movimiento no valido, intente de nuevo\nElimine una ficha del oponente: ";
                    cin>>eliminar;
                }
                //si es valido, se elimina la ficha
                eliminarficha(tablero, jugador, eliminar, fichastotalesj1, fichastotalesj2);
                mostrar_tablero(tablero);
            }
        }

        jugador = (jugador == "X") ? "O" : "X"; //cambiar turno
    }
    }
}

void mostrar_tablero(vector<string>&tablero){ //diseño del tablero tipo string
    cout<<setw(2)<<tablero[0]<<"-------------------"<<setw(2)<<tablero[1]<<"-------------------"<<setw(2)<<tablero[2]<<endl;
    cout<<" |                    |                    |"<<endl;
    cout<<" |     "<<setw(2)<<tablero[3]<<"------------"<<setw(2)<<tablero[4]<<"------------"<<setw(2)<<tablero[5]<<"      |"<<endl;
    cout<<" |      |             |             |      |"<<endl;
    cout<<" |      |     "<<setw(2)<<tablero[6]<<"-----"<<setw(2)<<tablero[7]<<"-----"<<setw(2)<<tablero[8]<<"      |      |"<<endl;
    cout<<" |      |      |             |      |      |"<<endl;
    cout<<setw(2)<<tablero[9]<<"-----"<<setw(2)<<tablero[10]<<"-----"<<setw(2)<<tablero[11]<<"            "<<setw(2)<<tablero[12]<<"-----"<<setw(2)<<tablero[13]<<"-----"<<setw(2)<<tablero[14]<<endl;
    cout<<" |      |      |             |      |      |"<<endl;
    cout<<" |      |     "<<setw(2)<<tablero[15]<<"-----"<<setw(2)<<tablero[16]<<"-----"<<setw(2)<<tablero[17]<<"      |      |"<<endl;
    cout<<" |      |             |             |      |"<<endl;
    cout<<" |     "<<setw(2)<<tablero[18]<<"------------"<<setw(2)<<tablero[19]<<"------------"<<setw(2)<<tablero[20]<<"      |"<<endl;
    cout<<" |                    |                    |"<<endl;
    cout<<setw(2)<<tablero[21]<<"-------------------"<<setw(2)<<tablero[22]<<"-------------------"<<setw(2)<<tablero[23]<<endl<<endl;
}

bool verificartriada(vector<string>&tablero, string &jugador, int &posicion){ //recibe el tablero, la ficha del jugador y la posicion que escogió
    //posibles triadas en el juego
    vector<vector<int>> posiblesTriadas = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},{9, 10, 11},
    {12, 13, 14}, {15, 16, 17},{18, 19, 20}, {21, 22, 23}, 
    {0, 9, 21},{3, 10, 8}, {6, 11, 15}, {1, 4, 7},
    {16, 19, 22}, {8, 12, 17}, {5, 13, 20}, {2, 14, 23}
    };

    for (size_t i = 0; i < posiblesTriadas.size(); i++) {
        // Verificamos si la posición actual está dentro de la tríada
        if (posiblesTriadas[i][0] == posicion ||
            posiblesTriadas[i][1] == posicion ||
            posiblesTriadas[i][2] == posicion) {

            // Verificamos si las tres posiciones tienen la ficha del mismo jugador
            if (tablero[posiblesTriadas[i][0]] == jugador &&
                tablero[posiblesTriadas[i][1]] == jugador &&
                tablero[posiblesTriadas[i][2]] == jugador) {
                return true;
            }
        }
    }
    return false;
}

void eliminarficha(vector<string>&tablero, string &jugador, int &posicion, int &fichastotalesj1, int &fichastotalesj2){
    //se recibe el tablero, el jugador actual del turno, la posicion que escogio, la cantidad de fichas por jugador
    
    //cambiar ficha por numero de la posicion en el tablero
    string cambio = to_string(posicion); //cambiar la variable int posicion al tipo string porque el vector es de tipo string
    tablero[posicion] = cambio;

    //eliminar la cantidad de fichas del oponente
    if (jugador == "X") { //reducir cantidad de fichas 
        fichastotalesj2 -= 1;
    } else {
        fichastotalesj1 -= 1;
    }
}

bool es_adyacente(int origen, int destino) {
    //posiciones adyacentes de acuerdo a la posición
    vector<vector<int>> adyacentes = {
        {1,9}, {0,2,4}, {1,14}, {4,10}, {1,3,5,7}, {4,13},
        {7,11}, {4,6,8}, {7,12}, {0,10,21}, {3,9,11,18}, {6,10,15},
        {8,13,17}, {5,12,14,20}, {2,13,23}, {11,16}, {15,17,19},
        {12,16}, {10,19}, {16,18,20,22}, {13,19}, {9,22},
        {19,21,23}, {14,22}
    };
    for (int adj : adyacentes[origen]) {
        if (adj == destino) return true; //ver si la posición que escogió el jugador es adyacente 
    }
    return false;
}

bool todasenTriada(vector<string>& tablero, string& oponente){
    //posibles triadas
    vector<vector<int>> posiblesTriadas = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},{9, 10, 11},
        {12, 13, 14}, {15, 16, 17},{18, 19, 20}, {21, 22, 23}, 
        {0, 9, 21},{3, 10, 8}, {6, 11, 15}, {1, 4, 7},
        {16, 19, 22}, {8, 12, 17}, {5, 13, 20}, {2, 14, 23}
        };
    
    //verificar si todas las fichas del oponente están en triadas
    for (int i = 0; i < tablero.size(); ++i) {
        if (tablero[i] == oponente && !verificartriada(tablero, oponente, i)) {
            return false;
        }
    }
    return true;
}

int victoria(int &fichastotalesj1, int &fichastotalesj2){
    //si un jugador llega a dos fichas
    if (fichastotalesj1 == 2) {
        return 1;
    }
    if (fichastotalesj2 == 2) {
        return 2;
    }
    return 0;
}

bool victoriaporadyacente(vector<string>&tablero, string &jugador){
    //adyacentes de acuerdo a las posiciones
    vector<vector<int>> adyacentes = {
        {1,9}, {0,2,4}, {1,14}, {4,10}, {1,3,5,7}, {4,13},
        {7,11}, {4,6,8}, {7,12}, {0,10,21}, {3,9,11,18}, {6,10,15},
        {8,13,17}, {5,12,14,20}, {2,13,23}, {11,16}, {15,17,19},
        {12,16}, {10,19}, {16,18,20,22}, {13,19}, {9,22},
        {19,21,23}, {14,22}
    };

    //si al menos una ficha de un jugador tiene adyacentes libres, devuelve false
    for (size_t i = 0; i < tablero.size(); i++) {
        if (tablero[i] == jugador) {
            bool tiene_adyacente_libre = false;
            for (size_t j = 0; j < 24; j++) {
                if (es_adyacente(i, j) && tablero[j] != "X" && tablero[j] != "O") {
                    tiene_adyacente_libre = true;
                    break;
                }
            }
            if (tiene_adyacente_libre) {
                return false;  
            }
        }
    }
    return true; //si todas las fichas del jugador tiene posiciones adyacentes ocupadas, devuelve true
}