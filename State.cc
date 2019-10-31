/* Universidad de La Laguna
 *  Escuela Superior de Ingeniería y Tecnología
 *  Grado en Ingeniería Informática
 *  Asignatura: Computabilidad y Algoritmia (CyA)
 *  Curso: 2º 
 *  Práctica 4 CyA - Eliminador de comentarios
 *  Autor: Alejandro Peraza González
 *  Correo: alu0101211770@ull.edu.es
 *  Fecha: 16/10/2019
 *  Archivo State.cc:   Esta clase es empleada con el fin de simbolizar
 *                      más fácilmente cada estado de un diagrama de
 *                      transiciones
 *  Referencias: 
 *                       Enunciado de la práctica:
 *                       https://campusvirtual.ull.es/1920/pluginfile.php/166891/mod_assign/introattachment/0/CYA_1920_Practica_4.pdf?forcedownload=1
 *  Historial de revisiones
 *                       10/10/2019 - Creación (primera versión) del código
 */

#include <iostream>
#include "State.h"

typedef std::vector<std::pair<State, char>> vector_pair;

State::State () : state_(), transitions_() {

}

State::State (std::string state) : state_(), transitions_() {
  state_ = state;
}

State::~State () {
  transitions_.erase(transitions_.begin(), transitions_.end());
}

std::string State::getStr () const {
  return state_;
}

void State::setStr (std::string &str) {
  state_ = str;
}

vector_pair State::getTransitions () const {
  return transitions_;
}

State State::Delta (char token) {
  State dead ("NULL");
  for(std::size_t i = 0; i < transitions_.size(); i++) {
    if (transitions_[i].second == token) {
      return transitions_[i].first;
    }
  }
  return dead;
}
// TODO delete Equal
bool State::Equal (State &state) const{
  if (state_ == state.getStr()) return 1;
  else return 0;
}

void State::Insert (char token, State q) {
  transitions_.push_back(std::make_pair(q, token));
}

// TODO add friend
bool State::operator< (const State &other) const { 
  return state_ < other.getStr(); 
}  
