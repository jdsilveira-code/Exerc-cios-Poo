#include <iostream>
#include <string>

using namespace std;

class SensorNivel {
private:
    string tag;
    double minimo;
    double maximo;
    double valorAtual;

public:
    // Cria com valores padrao
    SensorNivel(string tag) : tag(tag), minimo(0.0), maximo(100.0), valorAtual(0.0) {}
    // Cria ja configurado
    SensorNivel(string tag, double minimo, double maximo, double valorAtual)
        : tag(tag), minimo(minimo), maximo(maximo), valorAtual(valorAtual) {}

    void exibirResumo() const {
        cout << "[SensorNivel] " << tag
             << " | faixa: " << minimo << " a " << maximo
             << " | valor atual: " << valorAtual << "\n";
    }
};

class Bomba {
private:
    string tag;
    double velocidade;

public:
    // Cria com valor padrao
    Bomba(string tag) : tag(tag), velocidade(0.0) {}
    // Cria ja configurada
    Bomba(string tag, double velocidade) : tag(tag), velocidade(velocidade) {}

    void exibirResumo() const {
        cout << "[Bomba] " << tag
             << " | velocidade: " << velocidade << "%\n";
    }
};

class ControladorTanque {
private:
    string tag;
    double setpoint;
    double kp;

public:
    // Cria com valores padrao
    ControladorTanque(string tag) : tag(tag), setpoint(0.0), kp(1.0) {}
    // Cria ja configurado
    ControladorTanque(string tag, double setpoint, double kp)
        : tag(tag), setpoint(setpoint), kp(kp) {}

    void exibirResumo() const {
        cout << "[ControladorTanque] " << tag
             << " | SP=" << setpoint
             << " | Kp=" << kp << "\n";
    }
};

int main() {
    // Sensores
    SensorNivel sn1("LT-401");
    SensorNivel sn2("LT-402", 0.0, 5000.0, 2780.0);

    // Bombas
    Bomba b1("P-201");
    Bomba b2("P-202", 75.0);

    // Controladores
    ControladorTanque ct1("LIC-101");
    ControladorTanque ct2("LIC-102", 3500.0, 2.5);

    sn1.exibirResumo();
    sn2.exibirResumo();
    b1.exibirResumo();
    b2.exibirResumo();
    ct1.exibirResumo();
    ct2.exibirResumo();

    return 0;
}
