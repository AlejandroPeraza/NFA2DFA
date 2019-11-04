/* Universidad de La Laguna
 *  Escuela Superior de Ingeniería y Tecnología
 *  Grado en Ingeniería Informática
 *  Asignatura: Computabilidad y Algoritmia (CyA)
 *  Curso: 2º 
 *  Práctica 4 CyA - Eliminador de comentarios
 *  Autor: Alejandro Peraza González
 *  Correo: alu0101211770@ull.edu.es
 *  Fecha: 16/10/2019
 *  Archivo Automata.cc: Esta es la clase principal y la que inicializa el
 *                       funcionamiento del autómata y requiere de la 
 *                       creación de States, un alfabeto y una matriz
 *                       de transiciones
 *  Referencias: 
 *                       Enunciado de la práctica:
 *                       https://campusvirtual.ull.es/1920/pluginfile.php/166891/mod_assign/introattachment/0/CYA_1920_Practica_4.pdf?forcedownload=1
 *  Historial de revisiones
 *                       10/10/2019 - Creación (primera versión) del código
 */

#include "Dfa.h"
#include "State.h"
typedef std::vector<std::pair<State, char>> vector_pair;

Dfa::Dfa() : states_(), initial_state_(), final_states_(), alphabet_() {

}

Dfa::~Dfa() {
  states_.erase(states_.begin(), states_.end());
  final_states_.erase(final_states_.begin(), final_states_.end());
  alphabet_.erase(alphabet_.begin(), alphabet_.end());
}

void Dfa::AddState (State q, int mode) {
  switch (mode)
  {
  case 0:
    states_.push_back(q);
    break;
  case 1:
    initial_state_ = q;
    break;
  case 2:
    final_states_.push_back(q);
    break;
  default:
    break;
  } 
}

void Dfa::setAlphabet (std::vector<char> alphabet) {
  alphabet_ = alphabet;
}

// TODO el drawDfa

std::ostream& Dfa::drawDFA (std::ostream& os) {
  
  os << "digraph DFA {\n  rankdir=LR;\n  size =  \"10 , 4\";\n";
  os << "  d2tstyleonly = true;\n  node [shape = none]; \" \";\n";
  os << "  node [shape = doublecircle];";
  std::vector<State>::iterator it;
  for (it = final_states_.begin() ; it != final_states_.end(); ++it)
    os << " \"" << it->getStr() << '\"';
  if (!final_states_.empty()) os << ';';
  os << "\n  node [shape = circle];\n  \" \" -> \"" << initial_state_.getStr();
  os << "\"\n";
  for (std::size_t i = 0; i < states_.size(); i++) {
    for (std::size_t j = 0; j < alphabet_.size(); j++) {
      char token = alphabet_[j];
      State q = states_[i].Delta(token);
      if (q.getStr() != "NULL") {
        os << "  \"" << states_[i].getStr() << "\" -> \"" << q.getStr() << "\"";
        os << " [label=\"" << token <<"\"];\n";
      }
    }
  }
  os << '}';

/*

  for (std::vector<State>::iterator it = states_.begin(); it < states_.end(); it++) {
    os << it->getStr() << '\n';
    vector_pair tr = it->getTransitions();
    for (vector_pair::iterator at = tr.begin(); at < tr.end(); at++) {
      os << at->first.getStr() << ' ' << at->second << '\n';
    }
  }
  os << initial_state_.getStr() << '\n';
  

  for (std::vector<State>::iterator it = final_states_.begin(); it < final_states_.end(); it++) {
    os << it->getStr() << '\n';
  }
   for (std::vector<char>::iterator it = alphabet_.begin(); it < alphabet_.end(); it++) {
    os << *it << '\n';
  }
  */
  return os;
}