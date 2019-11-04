/** 
 * @details Archivo Dfa.h: En esta clase  se encuentra el método addState 
 *                         que sirve para rellenar los vectores de estados 
 *                         states_ y final_states así como el estado inicial.
 *                         Por otro lado, con la función drawDfa se imprimen
 *                         los datos en un archivo de salida con formato dot.
 * 
 *  @brief Clase en la que se almacena el dfa equivalente al nfa dado
 *  @author Alejandro Peraza González
 *  @date   05/11/2019
 *  @par Universidad
 *    Universidad de La Laguna
 *  @par Curso
 *    2º de Ingeniería Informática
 *  @par Título
 *    La construccion de subconjuntos
 *  @par Correo 
 *    alu0101211770@ull.edu.es
 *  @par Referencias
 *    https://campusvirtual.ull.es/1920/pluginfile.php/181073/mod_assign/introattachment/0/CYA_1920_Practica_7.pdf?forcedownload=1
 *  @par Historial de revisiones
 *    30/10/2019 - Creación (primera versión) del código
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
  /** @brief Setter del atributo alphabet_
   *  @param alphabet - un vector de caracteres que conforma el alfabeto
   */
  void setAlphabet (std::vector<char> alphabet);
  /** @brief Método para incluir los estados, tanto los genéricos(mode = 0)
   *  como el inicial (mode = 1) y los de aceptación (mode = 2)
   *  @param q - el estado a almacenar
   *  @param mode - selecciona dónde se almacenará q
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