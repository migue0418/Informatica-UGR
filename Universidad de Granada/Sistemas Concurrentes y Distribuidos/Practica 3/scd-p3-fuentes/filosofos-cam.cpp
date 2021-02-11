#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos     = 5,
   num_procesos_mesa = 2*num_filosofos,
   num_procesos      = num_procesos_mesa + 1,
   id_camarero       = num_procesos-1,
   tag_tenedores     = 0,
   tag_sentarse      = 1,
   tag_levantarse    = 2;


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// ---------------------------------------------------------------------

void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1)              % num_procesos_mesa, //id. tenedor izq.
      id_ten_der = (id+num_procesos_mesa-1) % num_procesos_mesa, //id. tenedor der.
      valor      = 0;

  while ( true )
  {
    cout << "Filósofo " << id << " solicita sentarse." << endl;
    // ... solicitar sentarse
    MPI_Ssend( &valor, 1, MPI_INT, id_camarero, tag_sentarse, MPI_COMM_WORLD );
    
    cout << "Filósofo " << id << " solicita ten. izq." << id_ten_izq << endl;
    // ... solicitar tenedor izquierdo
    MPI_Ssend( &valor, 1, MPI_INT, id_ten_izq, tag_tenedores, MPI_COMM_WORLD );

    cout << "Filósofo " << id << " solicita ten. der." << id_ten_der << endl;
    // ... solicitar tenedor derecho
    MPI_Ssend( &valor, 1, MPI_INT, id_ten_der, tag_tenedores, MPI_COMM_WORLD );

    cout << "Filósofo " << id << " comienza a comer" << endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    cout << "Filósofo " << id << " suelta ten. izq. " << id_ten_izq << endl;
    // ... soltar el tenedor izquierdo
    MPI_Ssend( &valor, 1, MPI_INT, id_ten_izq, tag_tenedores, MPI_COMM_WORLD );

    cout << "Filósofo " << id << " suelta ten. der. " << id_ten_der << endl;
    // ... soltar el tenedor derecho
    MPI_Ssend( &valor, 1, MPI_INT, id_ten_der, tag_tenedores, MPI_COMM_WORLD );

    cout << "Filósofo " << id << " solicita levantarse." << endl;
    // ... solicitar levantarse
    MPI_Ssend( &valor, 1, MPI_INT, id_camarero, tag_levantarse, MPI_COMM_WORLD );

    cout << "Filosofo " << id << " comienza a pensar" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}

// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
     // ...... recibir petición de cualquier filósofo
     MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_tenedores, MPI_COMM_WORLD, &estado );
     
     // ...... guardar en 'id_filosofo' el id. del emisor
     id_filosofo = estado.MPI_SOURCE;
     
     cout << "Ten. " << id << " ha sido cogido por filo. " << id_filosofo << endl;

     // ...... recibir liberación de filósofo 'id_filosofo'
     MPI_Recv ( &valor, 1, MPI_INT, id_filosofo, tag_tenedores, MPI_COMM_WORLD, &estado );
     
     cout << "Ten. " << id << " ha sido liberado por filo. " << id_filosofo << endl ;
  }
}

// ---------------------------------------------------------------------

void funcion_camarero()
{
  int valor                        = 0,  // valor recibido
      tag_recibida                    ,  // etiqueta del mensaje
      num_filosofos_sentados       = 0,  // numero de filosofos sentados
      tag_filosofo_aceptable          ;  // etiqueta que se puede aceptar en el siguiente mensaje
  MPI_Status estado ;           // metadatos de las recepciones

  while ( true )
  {
     // 1. determinar si los filosofos pueden levantarse solo o si pueden tb sentarse
     
     if ( num_filosofos_sentados == 4 )                // si hay 4 filosofos
         tag_filosofo_aceptable = tag_levantarse ;     // $~~~$ solo levantarse.
     else                                              // si hay menos de 4 filosofos
         tag_filosofo_aceptable = MPI_ANY_TAG ;        // $~~~$ levantarse o sentarse.

     // 2. recibir un mensaje de la solicitud aceptable (levatarse solo, o levantarse o sentarse)
     
     MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_filosofo_aceptable, MPI_COMM_WORLD, &estado );

     // 3. procesar el mensaje recibido
     
     // ...... guardar en 'tag_recibida' la etiqueta del mensaje
     tag_recibida = estado.MPI_TAG;
     
     if( tag_recibida == tag_levantarse )
         num_filosofos_sentados--;
     else
         num_filosofos_sentados++;
  }
}

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if( id_propio == id_camarero )         // si es el camarero
         funcion_camarero();
      else if ( id_propio % 2 == 0 )         // si es par
         funcion_filosofos( id_propio );     //   es un filósofo
      else                                   // si es impar
         funcion_tenedores( id_propio );     //   es un tenedor
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}
