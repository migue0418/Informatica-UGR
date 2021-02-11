#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <mpi.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

const int
   num_procesos_productores = 4,
   id_buffer = 4,
   num_procesos_consumidores = 5,
   num_procesos_esperado = num_procesos_productores + num_procesos_consumidores + 1,
   
   //num_item debe ser multiplo de num_procesos_productores*num_procesos_consumidores
   num_items             = 20,
   tam_vector            = 10,
   tag_productor	 = 0,
   tag_consumidor        = 1;

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


int producir(int num_orden_productor)
{
   static int contador = num_orden_productor*num_items/num_procesos_productores;
   
   sleep_for( milliseconds( aleatorio<10,100>()) );
   contador++ ;
   
   cout << "Productor (" << num_orden_productor << ") ha producido valor " << contador << endl << flush;
   return contador ;
}

// ---------------------------------------------------------------------

void funcion_productor(int num_orden_productor)
{
   for ( unsigned int i= 0 ; i < num_items/num_procesos_productores ; i++ )
   {
      // producir valor
      int valor_prod = producir(num_orden_productor);

      // enviar valor
      cout << "Productor (" << num_orden_productor << ") va a enviar valor " << valor_prod << endl << flush;
      MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, tag_productor, MPI_COMM_WORLD );
   }
}

// ---------------------------------------------------------------------

void consumir( int valor_cons, int num_orden_consumidor )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   
   cout << "Consumidor (" << num_orden_consumidor << ") ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int num_orden_consumidor)
{
   int         peticion,
               valor_rec = 1;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < num_items/num_procesos_consumidores ; i++ )
   {
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, tag_consumidor, MPI_COMM_WORLD);
      
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, tag_consumidor, MPI_COMM_WORLD,&estado );
      
      cout << "Consumidor (" << num_orden_consumidor << ") ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec, num_orden_consumidor );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              tag_emisor_aceptable ;    // identificador de emisor aceptable
   MPI_Status estado ;                 // metadatos del mensaje recibido

   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
      // 1. determinar si puede enviar solo prod., solo cons, o todos

      if ( primera_libre == 0 )               // si buffer vacío
         tag_emisor_aceptable = tag_productor ;     // $~~~$ solo prod.
      else if ( primera_libre == tam_vector ) // si buffer lleno
         tag_emisor_aceptable = tag_consumidor ;    // $~~~$ solo cons.
      else                                          // si no vacío ni lleno
         tag_emisor_aceptable = MPI_ANY_TAG ;       // $~~~$ cualquiera

      // 2. recibir un mensaje del emisor o emisores aceptables

      MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_emisor_aceptable, MPI_COMM_WORLD, &estado );

      // 3. procesar el mensaje recibido
      int tag_emisor = estado.MPI_TAG,    // leer etiqueta del mensaje en metadatos
          id_emisor  = estado.MPI_SOURCE; // leer emisor del mensaje en metadatos

      if(tag_emisor == tag_productor){ // si ha sido un productor: insertar en buffer
            buffer[primera_libre] = valor ;
            primera_libre++;
            
            cout << "Buffer ha recibido valor " << valor << " (del productor " << id_emisor << ")" << endl ;
      }else {                                  // si ha sido un consumidor: extraer y enviarle
            valor = buffer[primera_libre-1] ;
            primera_libre-- ;
            
            cout << "Buffer va a enviar valor " << valor << " (al consumidor " << id_emisor-num_procesos_productores-1 << ")" << endl ;
            
            MPI_Ssend( &valor, 1, MPI_INT, id_emisor, tag_consumidor, MPI_COMM_WORLD);
      }
   }
}

// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual;

   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_esperado == num_procesos_actual )
   {
      // ejecutar la operación apropiada a 'id_propio'
      if ( id_propio < num_procesos_productores )
         funcion_productor(id_propio);
      else if ( id_propio == num_procesos_productores )
         funcion_buffer();
      else
         funcion_consumidor(id_propio-num_procesos_productores-1);
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}
