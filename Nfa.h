/** 
 * @details Archivo Nfa.h: Esta es la clase principal y la que inicializa la
 *                         lectura y creación del Nfa, requiere de la creación de 
 *                         los estados, un alfabeto de entrada y las transiciones
 *                         entre estados. A partir de este Nfa se creará un DFA
 *                         equivalente.
 * 
 *  @brief Se crea un NFA a partir de los datos leídos en el fichero 
 *  de entrada y se imprime un DFA equivalente en el de salida.
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
#include <set>
#include "State.h"
#include "Dfa.h"

#ifndef NFA
#define NFA

class Nfa {
 public:
  /** @brief Constructor de la clase Autómata que lee el contenido de un fichero
   *  y crea un DFA 
   *  @param is - fichero del que se lee los datos del DFA por referencia
   */
  Nfa (std::istream& is);
  /** @brief Destructor de la clase Autómata que libera la memoria reservada por
   *  los vectores states_, final_states_ y alphabet_ 
   */
  ~Nfa();
  /** @brief Método que recorre el vecor states_ que contiene los estados
   *  y devuelve la posición en la que encuentra la string buscada
   *  @param str - string para poder encontrar la posición en el vector 
   *  @return entero que indica la posición del vector
   */
  int FindPos (std::string str, std::vector<State> v);
  /** @brief Método  que obtiene los E-clausra estados de un estado
   *  @param T - conjunto de estados sobre el que calcular
   *  @return el conjunto de estados resultante
   */
  std::set<State> EClosure (std::set<State> T);
  /** @brief Método que devuelve el conjunto de estados que pueden alcanzarse
   *  desde el estado S con el símbolo de entrada token
   *  @param S - estado desde el que se analizan las tranisiciones
   *  @param token - símbolo de entrada
   *  @return conjunto de estados correspondiente
   */
  std::set<State> Move (std::set<State> S, char token);
  /** @brief Método que aplica el algoritmo de construcción de suconjuntos
   *  @param DFA_states - el conjunto de estados del DFA correspondiente
   */
  std::ostream& SubSets (Dfa &DFA, std::ostream& os);
  /** 
   */
  bool isinVector (std::vector<std::pair<std::set<State>, State>> &s, std::set<State> &q, int &pos);
  /**
   */
  int marked (std::vector<std::pair<std::set<State>, State>> &s, int &a);


 private:
  std::vector<State> states_;
  State initial_state_;
  std::vector<State> final_states_;
  std::vector<char> alphabet_;
};

#endif
