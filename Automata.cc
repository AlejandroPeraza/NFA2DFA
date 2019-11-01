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

#include "Automata.h"
#include "State.h"
#include <stack>

typedef std::vector<std::pair<State, char>> vector_pair;

Automata::Automata (std::istream& is) : states_(), initial_state_(), final_states_(), alphabet_() {
  std::vector<std::string> read;
  std::string str, str2, str3;
  int option = 0;
  char token;
  while (getline(is, str)) {
    if ((str[0] == '/' && str[1] == '/') || str[0] == '\n') continue;
    else 
      read.push_back(str);
  }

  int count = 1;
  int aux = std::stoi(read[0]);
  // N+ 1 iterations
  for (int i = 0; i <= aux; i++) {
      alphabet_.push_back(read[i+1][0]);
  }
  
  count += aux + 1;
  aux = std::stoi(read[count]);
  for (int i = 0; i < aux; i++) {
    State q (read[count + i + 1]);
    states_.push_back(q);
  }

  count+=aux + 1;
  initial_state_.setStr(read[count]);
  count++;
  aux = std::stoi(read[count]);
  
  for (int i = 0; i < aux; i++) {
    State q (read[count + i + 1]);
    final_states_.push_back(q);
  }

  count+=aux + 1;
  aux = std::stoi(read[count]);
  for (int i = 0; i < aux; i++) {
    str = read[count + i + 1];
    option = 0;
    for (std::string::size_type j = 0; j < str.length(); j++) {
      switch (option) {
        case 0 : {
          if (str[j] == ' ') {
            option++;
          } 
          else {
            str2 += str[j];
          }
          break;
        }
        case 1 : {
          token = str[j];
          option++;
          break;
        }
        case 2 : {
          if (str[j] != ' ')
            str3 += str[j];
          break;
        }
      }
    }
    states_[FindPos(str2)].Insert(token, states_[FindPos(str3)]);
    str2.clear();
    str3.clear();
  }
  /*
  vector_pair v = states_[6].getTransitions();
  for (vector_pair::iterator it = v.begin(); it < v.end(); it++) {
    std::cout << it->first.getStr() << ' ' << it->second << '\n';
  }

  for (std::vector<char>::iterator it = alphabet_.begin(); it < alphabet_.end(); it++) {
    std::cout << *it << '\n';
  }
  std::cout << '\n';
  std::cout << initial_state_.getStr()  << '\n';
  std::cout << '\n';
    for (std::vector<State>::iterator it = final_states_.begin(); it < final_states_.end(); it++) {
    std::cout << it->getStr() << '\n';
  }
  std::cout << '\n';
  for (std::vector<State>::iterator it = states_.begin(); it < states_.end(); it++) {
    std::cout << it->getStr() << '\n';
  }
  std::cout << '\n';
  */
  std::set<State> T;
  T.insert(states_[5]);
  T.insert(states_[10]);
  T = EClosure(T);
  //for (std::set<State>::iterator it = begin(T); it != end(T); it++) {
    //std::cout << it->getStr() << '\n';
  //}
  T.clear();
  T.insert(states_[0]);
  T.insert(states_[1]);
  T.insert(states_[2]);
  T.insert(states_[4]);
  T.insert(states_[7]);
  T = Move(T, 'b');
  for (std::set<State>::iterator it = begin(T); it != end(T); it++) {
    std::cout << it->getStr() << '\n';
  }
}
  
Automata::~Automata() {
  states_.erase(states_.begin(), states_.end());
  final_states_.erase(final_states_.begin(), final_states_.end());
  alphabet_.erase(alphabet_.begin(), alphabet_.end());
}

int Automata::FindPos (std::string str) {
    for (std::size_t i = 0; i < states_.size(); i++){
      if (states_[i].getStr() == str) return i;
    }
  return -1;
}

std::ostream& Automata::Dot (std::ostream& os) {
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
  return os;
}

std::set<State> Automata::EClosure (std::set<State> T) {
  std::stack<State> cl_stack;
  std::set<State> epsilon_closure = T;
  for (std::set<State>::iterator it = begin(T); it != end(T); it++) {
    cl_stack.push(*it);
  }
  while(!cl_stack.empty()) {
    // TODO make this shit prettier pls
    State q = cl_stack.top();
    cl_stack.pop();
    vector_pair tr = q.getTransitions();
    for (vector_pair::iterator it = tr.begin(); it < tr.end(); it++) {
      if (it->second == alphabet_[0] ) {
        if (!epsilon_closure.count(it->first)) {
          State aux = states_[FindPos(it->first.getStr())];
          epsilon_closure.insert(aux);;
          cl_stack.push(aux);
        }
      }
    }
  } 
  return epsilon_closure;
}

std::set<State> Automata::Move (std::set<State> S, char token) {
  std::stack<State> cl_stack;
  std::set<State> aux;
  aux = EClosure(S);
  std::set<State> moved;
  for (std::set<State>::iterator it = begin(aux); it != end(aux); it++) {
    cl_stack.push(*it);
  }


  // En la pila están actualmente los estados de la E Clausura de S
  while(!cl_stack.empty()) {
    // TODO make this shit prettier pls
    State q = cl_stack.top();
    cl_stack.pop();
    vector_pair tr = q.getTransitions();
    for (vector_pair::iterator it = tr.begin(); it < tr.end(); it++) {
      if (it->second == token ) {
        if (!moved.count(it->first)) {
          State aux_state = states_[FindPos(it->first.getStr())];
          moved.insert(aux_state);
        }
      }
    }
  } 
  return moved;
}