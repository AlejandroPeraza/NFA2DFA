/** Universidad de La Laguna
 *  Escuela Superior de Ingeniería y Tecnología
 *  Grado en Ingeniería Informática
 *  Asignatura: Computabilidad y Algoritmia (CyA)
 *  Curso: 2º 
 *  Práctica 7 CyA - La construccion de subconjuntos
 *  Autor: Alejandro Peraza González
 *  Correo: alu0101211770@ull.edu.es
 *  Fecha: 05/11/2019
 *  Archivo Nfa.cc: En esta clase, partiendo del fichero de entrada se
 *                  conforma un NFA en el constructor y luego, por medio
 *                  del método SubSets (que aplica el algoritmo de creación
 *                  de subconjuntos) se crea un DFA equivalente gracias a 
 *                  los métodos E-Closure y Move 
 *  Referencias: 
 *                  Enunciado de la práctica:
 *                  https://campusvirtual.ull.es/1920/pluginfile.php/181073/mod_assign/introattachment/0/CYA_1920_Practica_7.pdf?forcedownload=1
 *  Historial de revisiones
 *                       30/10/2019 - Creación (primera versión) del código
 */ 

#include "Nfa.h"
#include "Dfa.h"
#include "State.h"
#include <stack>

typedef std::vector<std::pair<State, char>> vector_pair;

Nfa::Nfa (std::istream& is) : states_(), initial_state_(), final_states_(), alphabet_() {
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
    int aux1 = FindPos(str2, states_);
    int aux2 = FindPos(str3, states_);
    states_[aux1].Insert(token, states_[aux2]);
    str2.clear();
    str3.clear();
  } 
}
  
Nfa::~Nfa() {
  states_.erase(states_.begin(), states_.end());
  final_states_.erase(final_states_.begin(), final_states_.end());
  alphabet_.erase(alphabet_.begin(), alphabet_.end());
}

int Nfa::FindPos (std::string str, std::vector<State> v) {
    for (std::size_t i = 0; i < v.size(); i++) {
      if (v[i].getStr() == str) return i;
    }
  return -1;
}

std::set<State> Nfa::EClosure (std::set<State> T) {
  std::stack<State> cl_stack;
  std::set<State> epsilon_closure = T;
  for (std::set<State>::iterator it = begin(T); it != end(T); it++) {
    cl_stack.push(*it);
  }
  while(!cl_stack.empty()) {
    State q = cl_stack.top();
    cl_stack.pop();
    vector_pair tr = q.getTransitions();
    for (vector_pair::iterator it = tr.begin(); it < tr.end(); it++) {
      if (it->second == alphabet_[0] ) {
        if (!epsilon_closure.count(it->first)) {
          State aux = states_[FindPos(it->first.getStr(), states_)];
          epsilon_closure.insert(aux);;
          cl_stack.push(aux);
        }
      }
    }
  } 
  return epsilon_closure;
}

std::set<State> Nfa::Move (std::set<State> S, char token) {
  std::stack<State> cl_stack;
  std::set<State> moved;
  for (std::set<State>::iterator it = begin(S); it != end(S); it++) {
    cl_stack.push(*it);
  }
  // En la pila están actualmente los estados de la E Clausura de S
  while(!cl_stack.empty()) {
    State q = cl_stack.top();
    cl_stack.pop();
    vector_pair tr = q.getTransitions();
    for (vector_pair::iterator it = tr.begin(); it < tr.end(); it++) {
      if (it->second == token) {
        if (!moved.count(it->first)) {
          State aux_state = states_[FindPos(it->first.getStr(), states_)];
          moved.insert(aux_state);
        }
      }
    }
  } 
  return moved;
}



std::ostream& Nfa::SubSets (Dfa &DFA, std::ostream& os) {
  Dfa dfa;
  std::vector<std::pair<std::set<State>, State>> states;
  std::vector<std::pair<std::set<State>, State>>::iterator check;
  int id = 0;
  State q_d (std::to_string(0));
  std::set<State> q_n;
  q_n.insert(states_[FindPos(initial_state_.getStr(), states_)]);
  q_n = EClosure(q_n);
  states.push_back(std::make_pair(q_n, q_d));
  std::set<State> H = EClosure(Move(states[0].first, 'a'));
  std::set<State> z = EClosure(Move(H, 'a'));
  
  int a = 0;
  while(marked(states, a) != -1) {
    for (std::vector<char>::iterator alph = alphabet_.begin() + 1 ; alph < alphabet_.end(); alph++) {
      std::set<State> H = EClosure(Move(states[a].first, *alph));
     int pos = 0;
     isinVector(states, H, pos);
     int aux = 0;
     if (pos == 0) aux = id + 1;
     else aux = pos;
     State q_aux (std::to_string(aux));
      if (pos == 0) {
        id++;
        q_aux.setMark(false);
        states.push_back(std::make_pair(H, q_aux));
      }
      states[a].second.Insert(*alph, q_aux);
    }
  }
  std::vector<std::pair<std::set<State>, State>>::iterator it;
  for (it = states.begin(); it < states.end(); it++) {
    for (std::set<State>::iterator it2 = it->first.begin(); it2 != it->first.end(); it2++) {
      if (FindPos(it2->getStr(), final_states_) != -1) {
        dfa.AddState(it->second, 2);
      }
    }
    dfa.AddState(it->second, 0);
  }
  dfa.AddState(states[0].second, 1);
  std::vector<char> alphabet = alphabet_;
  alphabet.erase(alphabet.begin());
  dfa.setAlphabet(alphabet);
  dfa.drawDFA(os);
  return os;
}

bool Nfa::isinVector (std::vector<std::pair<std::set<State>, State>>& s, std::set<State>& q, int &pos) {
  for(std::vector<std::pair<std::set<State> , State>>::size_type i = 0; i != s.size(); i++) {
    if (s[i].first == q) {
      pos = i;
      return true;
    }
  }
  return false;
}

int Nfa::marked (std::vector<std::pair<std::set<State> , State>> &s, int &a) {
  for(std::vector<std::pair<std::set<State> , State>>::size_type i = 0; i != s.size(); i++) {
    if (!s[i].second.getMark()) {
      s[i].second.setMark(true);
      a = i;
      return i;
    }
  }
  return -1;
}
