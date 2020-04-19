#include <iostream>
#include <queue>
#include <ctime>

using namespace std;
#define MAX_BENEFIT 400

/*
Tenemos que completar un conjunto de N tareas con plazos límite. Cada una de las tareas consume la misma cantidad de tiempo (una unidad) y, en un instante determinado, podemos realizar únicamente una tarea. La tarea i tiene como plazo límite Di y produce un beneficio Gi, con Gi > 0 únicamente si la tarea se realiza en un instante de tiempo T <= Di.
Diseñe un algoritmo voraz que nos permita seleccionar el conjunto de tareas que nos asegure el mayor beneficio posible.


Vamos a analizar el enunciado de una forma mas extensa.
Se nos proveee de un conjunto de tareas, en este caso llamado N.
Cada tarea i tiene como plazo limite de realización Di, esto significa que la tarea solo puede tardar el mismo tiempo o menos que el indicado para ser realizada.
Además, cada tarea tiene un beneficio asociado Gi, este será positivo siempre y cuando la tarea se realize dentro del plazo antes acordado.

El objetivo propuesto es realizar el conjunto de tareas en un orden en el cual podamos tener el mejor beneficio, es decir, que todas las tareas se realizen de forma que su respectivo beneficio pueda ser añadido a un conjunto total de Beneficio, que llamaremos B.


Cada Tarea analizada tendrá por tanto 3 parámetros de entrada:
  -ID_ : Este será el identificador que tendrá cada tarea.
  -T_ : Este será el plazo límite de realización de cada caso.
  -B_ : Este será el beneficio que genere la tarea en cuestión.

Para facilitar el almacenamiento de estos datos, crearemos una clase llamada Task, que guardará toda la información necesaria de cada tarea nueva.
Una vez implementada dicha clase, sobrecargaremos el operador < para poder realizar la comparación directa entre el beneficio de cada objeto de la clase tarea.

Hacemos esto para, en el main, tener la posibilidad de hacer uso del Tipo de dato de la STL priority_queue, es decir, una cola de prioridades.

Realizaremos la implementación de dicha cola de forma que al insertar en la misma cada objeto, quede en el tope aquel objeto que de mas beneficios.

No obstante, se presenta también un nuevo obstáculo, pues debemos añadir el beneficio de aquellas tareas que únicamente podemos ejecutar dentro de su límite de tiempo permitido. Para comprobar esto, realizaremos una comprobación despues de sacar el elemento de la cola para ver si este puede ser ejecutado dentro de su plazo de tiempo.


Por último, para evitar complicaciones en cuanto a entrada de datos o bancos de datos para analizar, vamos a crear un generador de datos automático, de forma que el único parámetro de entrada necesario para este programa al ejecutarse sea el número de tareas que queremos generar para su posterior análisis.


*/

class Task{
private:
  string ID_; //Identificador de la tarea
  int T_;     //Tiempo Límite para la ejecución de la tarea
  long B_;    //Beneficio Generado por la realización de la tarea
public:

  Task();

  Task(string new_ID, double new_T, long new_B): ID_(new_ID), T_(new_T), B_(new_B){}

  string get_ID()const{return ID_;}

  int get_T()const{return T_;}

  long get_B()const{return B_;}

  void set_ID(string new_ID){ID_ = new_ID;}

  void set_T(int new_T){T_ = new_T;}

  void set_B(long new_B){B_ = new_B;}

  void printTask(){
    cout << "Identificador: " << get_ID() 
         << "  Plazo limite: " << get_T()
         << "  Beneficio: " << get_B() << endl;
  }
};



/*Sobrecarga de operador < para poder realizar la comparación entre objetos de la misma clase. Este será usado por el Tipo de dato priority_queue para poder elegir los objetos segun la prioridad que deseemos.
*/
bool operator<(const Task &t1, const Task &t2){
  return (t1.get_B()< t2.get_B());
}


/*
Generador de Objetos de la clase Task.
El numero de tareas será también el numero de unidades de tiempo máximo que pueda tener cada tarea como limite de ejecución.
El rango de beneficio va entre 1-400
*/
void taskGenerator(priority_queue<Task> &cola, int nTasks){

   srand(time(NULL));


    for(int i=0; i<nTasks; i++){
      string aux_ID = "ID_"+ to_string(rand()%(666)+1);
      int aux_T = rand()%(nTasks)+1;
      long aux_B = rand()%(MAX_BENEFIT)+1;

      Task aux(aux_ID, aux_T, aux_B);
      cola.push(aux);
    }

}


//Metodo auxiliar para imprimir el contenido de la cola
void printQueue(priority_queue <Task> q) 
{ 
    priority_queue <Task> g = q; 
    while (!g.empty()) { 
      Task tAux = g.top();
      g.pop(); 
      tAux.printTask();  
    } 
  cout << endl; 
} 



int main(int argc, char * argv[]){

  priority_queue<Task> Schedule;
  priority_queue<Task> FinalSchedule;
  int TIME_UNITY = 0;
  int TOTAL_BENEFIT = 0;

  if (argc != 2){
      cerr << "Formato de entrada incorrecto" << endl;
      return -1;
  }
  
  int n = atoi(argv[1]);
  
  taskGenerator(Schedule, n);

  cout << "El numero de tareas generadas es: " << n << endl;
  printQueue(Schedule);

  
  while(!Schedule.empty()){
    Task  singleTask = Schedule.top();
    Schedule.pop();

    if(singleTask.get_T() >= TIME_UNITY){
      TOTAL_BENEFIT += singleTask.get_B();
      TIME_UNITY++;

      cout << "ID de tarea extraida: " << singleTask.get_ID() << endl;
      cout << "Beneficio actual: " << TOTAL_BENEFIT << endl;
      cout << "Unidades de tiempo utilizadas: " << TIME_UNITY << endl << endl;
      FinalSchedule.push(singleTask);
    }
    else cout << "Se omite esta tarea por haber superado el limite de tiempo."<< endl << endl;

  } 

cout << "El conjunto final de tareas obtenidas es: " << endl;
printQueue(FinalSchedule);
cout << "Con un total de Beneficio: " << TOTAL_BENEFIT << endl;
cout << "Unidades de tiempo consumidas: " << TIME_UNITY << endl;
}