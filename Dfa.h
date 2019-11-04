/** 
 * @details Archivo Automata.h:  Esta es la clase principal y la que inicializa el
 *                      funcionamiento del autómata y requiere de la creación  de 
 *                      los estados, un alfabeto de entrada y las transiciones
 *                      entre estados
 * 
 *  @brief Clase principal que crea un autómata a partir de los datos 
 *  leídos en el fichero de entrada.
 *  @author Alejandro Peraza González
 *  @date   28/10/2019
 *  @par Universidad
 *    Universidad de La Laguna
 *  @par Curso
 *    2º de Ingeniería Informática
 *  @par Título
 *    Autómatas finitos deterministas
 *  @par Correo 
 *    alu0101211770@ull.edu.es
 *  @par Referencias
 *    https://campusvirtual.ull.es/1920/pluginfile.php/176735/mod_assign/introattachment/0/CYA_1920_Practica_6.pdf?forcedownload=1
 *  @par Historial de revisiones
 *    10/10/2019 - Creación (primera versión) del código
 */

#include <iostream>
#include <vector>
#include "State.h"

#ifndef DFA
#define DFA

class Dfa {
 public:
  /** @brief Constructor por defecto
   */
  Dfa ();

  /** @brief Destructor de la clase Autómata que libera la memoria reservada por
   *  los vectores states_, final_states_ y alphabet_ 
   */
  ~Dfa();
  
  /** @brief Método que recorre el vecor states_ que contiene los estados
   *  y devuelve la posición en la que encuentra la string buscada
   *  @param str - string para poder encontrar la posición en el vector 
   *  @return entero que indica la posición del vector
   */
//int FindPos (std::string str);
  /**
   */
  void AddState (State q, int mode);
  /** @brief Método que realiza la conversión de los datos del DFA a un archivo
   *  con formato Dot
   *  @param os - fichero en el que se imprime la conversión por referencia
   *  @return se devuelve por referncia el stream
   */
  std::ostream& drawDFA (std::ostream& os);

 private:
  std::vector<State> states_;
  State initial_state_;
  std::vector<State> final_states_;
  std::vector<char> alphabet_;
};

#endif