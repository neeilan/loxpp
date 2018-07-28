//#include <map>
//#include <string>
//#include <interpreter.h>
//
//#include "environment.hpp"
//#include "token.hpp"
//
//template <class T>
//void Environment<T>::define(std::string name, const T &value) {
//    values[name] = value;
//}
//
//template <class T>
//T Environment<T>::get(const Token name) {
//    if (values.count(name.lexeme) > 0) {
//        return values[name.lexeme];
//    }
//
//    if (enclosing) {
//        return enclosing->get(name);
//    }
//
//    throw RuntimeErr(name, "Undefined variable '" + name.lexeme + "'.");
//}
//
//template <class T>
//T Environment<T>::get_at(int distance, const Token name) {
//    return (ancestor(distance)->values)[name.lexeme];
//}
//
//template <class T>
//void Environment<T>::assign_at(int distance, const Token name, const T &value) {
//    ancestor(distance)->values.at(name.lexeme) = value;
//}
//
//template <class T>
//Environment<T>* Environment<T>::ancestor(int distance) {
//
//    Environment<T>* curr_environment = this;
//
//    for (int i = 0; i < distance; i++)
//        curr_environment = curr_environment->enclosing;
//
//    return curr_environment;
//}
//
//template <class T>
//void Environment<T>::assign(const Token name, const T &value) {
//    if (values.count(name.lexeme) > 0) {
//        values[name.lexeme] = value;
//        return;
//    }
//
//    if (enclosing) {
//        enclosing->assign(name, value);
//        return;
//    }
//
//    throw RuntimeErr(name, "Undefined assignment target '" + name.lexeme + "'.");
//}
