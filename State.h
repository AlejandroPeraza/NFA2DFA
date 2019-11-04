/** 
 * @details Archivo State.h: Clase conformada por un string y un booleano 
 *                  que sirve para saber si un estado está o no marcado, 
 *                  también tiene un vector de pares, dichos pares son un 
 *                  Estado (un objeto de la misma clase) y un char. 
 *                  Dicho vector indica las diversas transiciones de 
 *                  cada estado.
 * 
 *  @brief Clase empleada para representar cada estado del DFA
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

#include <string>
#include <vector>

#ifndef STATE
#define STATE


class State {
 public:
  typedef std::vector<std::pair<State, char>> vector_pair;
  /// Constructor de la clase State por defecto 
  State ();
  /** @brief Constructor al recibir una string, esta es asignada a
   *  la variable state_
   *  @param state - identificador de cada estado
   */
  State (std::string state);
  /** @brief Destructor que libera la memoria reservada por el vector
   *  transitions_
   */
  ~State ();
  /** @brief Getter del atributo state_
   *  @return string que identifica a cada estado
   */
  std::string getStr () const;
  /** @brief Setter del atributo state_
   *  @param str - una string que modifica el valor de state_  
   */
  void setStr (std::string &str);
  /** @brief Método que devuelve el atributo marked_
   *  @return booleano que indica si el estado está o no marcado
   */
  bool getMark() const;
  /** @brief Método que mopdiifca el atributo marked_
   *  @param mark - 1 ó 0 para marcar o desmarcar el estado
   */
  void setMark(bool mark);
  vector_pair getTransitions () const;
  /** @brief Método que devuelve el estado siguiente dado un estado
   *  actual y un char
   * @param token - un char
   * @return un estado siguiente
   */ 
  State Delta (char token);
  /** @brief Método para comparar si dos estados son iguales 
   *  @param state - estado a comparar
   *  @return un booleano que indica si son o no iguales
   */
  void Insert (char token, State q);
  /** @brief Sobrecarga del operador < para el correcto 
   *  funcionamiento de un set
   *  @param other - un estado, objeto de la clase
   *  @return un booleano que indica si es menor o no
   */
  bool operator< (const State &other) const;
  /** @brief Compara si dos estados son iguales 
   *  @param state - estado a 
   *  @return un booleano que indica si son o no iguales
   */
  bool operator== (const State &other) const;

 private:
  std::string state_;
  vector_pair transitions_;
  bool marked_;
};

#endif
