#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <tuple>
using namespace std;

template <typename T, int sz>   // 2 parametros
                                // - parametro tipo
                                // - parametro no tipo
class Array {
};

void ejemplo_uso_de_parametro_no_tipo() {
    array<int, 4> arr = {1, 2, 3, 4};
    for (auto item: arr)
        cout << item << " ";
}

template <typename T, template<typename...> typename Container>
// 2 parametros
// - parametro tipo
// - parametro template de template
Container<T> create() {
    return Container<T>{};
}


void ejemplo_uso_de_parametro_template_template () {
    auto v = create<string, vector>();
    v.push_back("jose");
    v.push_back("maria");
    for (auto item: v)
        cout << item << " ";
    auto d = create<string, deque>();
    d.push_back("jose");
    d.push_back("maria");
    for (auto item: d)
        cout << item << " ";
}

template <typename T, size_t sz, template<typename, size_t> typename Array>
// 3 parametros
// - parametro tipo, parametro no tipo, parametro template de template
Array<T, sz> create_array() {
    return Array<T, sz>{};
}

void ejemplo_uso_de_parametro_template_template_cantidad_fija () {
    auto a1 = create_array<int, 4, std::array>();
    for (auto item: a1)
        cout << item << " ";
//    auto a2 = create_array<float, 3, Array>();
//    for (auto item: a2)
//        cout << item << " ";
}

template <typename T>       // un template con parametro tipo
auto sumar(T a, T b) { return a + b; }

template <typename ...Ts>   // Variadic template de tipos
auto funcion1() {
    cout << __PRETTY_FUNCTION__ << endl;
}
template <int ...Ts>   // Variadic template de no tipos
auto funcion2() {
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T, typename ...Ts>             // ...Ts empaqueta los tipos
auto print(T t, Ts... ts) {         // Ts... desempaqueta los tipos
    // Condicion base (utilizar sizeof...)
    if constexpr (sizeof...(ts) == 0) {
        cout << t << " " << __PRETTY_FUNCTION__ << " - condicion base" << endl;
    }
    // Condicion recursiva
    else {
        cout << t << " " << __PRETTY_FUNCTION__ << endl;
        print(ts ...);
    }
}
auto print() {}

template <typename T, typename ...Ts>
auto print2(T t, Ts ...ts) {
    cout << t << " ";
    (..., print2(ts));      // Fold expression
}
auto print2() {}

template <typename ...Ts>
auto print3(Ts... ts) {
//    (cout << ... << ts);      // Fold expression
    ((cout << ts << " "), ...);      // Fold expression
}

int main() {
//    ejemplo_uso_de_parametro_template_template();
//    ejemplo_uso_de_parametro_template_template_cantidad_fija();
//    cout << sumar(1, 2) << endl;               // llamada implicita (deduce por valores)
//    cout << sumar<double>(1, 2.5) << endl;     // llamada explicita
//    funcion1<int, float, bool, bool>();             // Tipos
//    funcion1<int, bool>();                          // Tipos
//    funcion1<>();                                   // Tipos
//    funcion2<1, 2, 4, 5>();                         // No tipos
    print(1, 2.0f, 3.0, 'c');                         // print(int x, float y, double z, char w)
                                                      // ts = {1, 2.0f, 3.0, 'c'} // std::tuple
    print(10000);
    print();
    print2(1, 2.0f, 3.0, 'c');
    print2(10000);
    print2();
    print3();
    print3(1, 2.0f, 3.0, 'c');
    print3(1000);

    return 0;
}
