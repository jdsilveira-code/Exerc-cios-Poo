#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AtuadorLinha {
private:
    string tag;
    string area;

protected:
    double limitarPercentual(double percentual) const {
        if (percentual < 0.0) return 0.0;
        if (percentual > 100.0) return 100.0;
        return percentual;
    }

public:
    AtuadorLinha(string novaTag, string novaArea)
        : tag(novaTag), area(novaArea) {}

    virtual ~AtuadorLinha() = default;

    string getTag() const { return tag; }
    string getArea() const { return area; }

    // Métodos virtuais puros tornam a classe abstrata
    virtual void aplicarReferenciaPercentual(double percentual) = 0;
    virtual void exibirResumo() const = 0;
};

class MotorEsteira : public AtuadorLinha {
private:
    double frequenciaHz;

public:
    // Construtor repassando parâmetros para a base
    MotorEsteira(string novaTag, string novaArea) 
        : AtuadorLinha(novaTag, novaArea), frequenciaHz(0.0) {}

    // Converte 0-100% para 0-60Hz (Ex: 50% vira 30Hz)
    void aplicarReferenciaPercentual(double percentual) override {
        double limpo = limitarPercentual(percentual);
        frequenciaHz = (limpo / 100.0) * 60.0;
    }

    void exibirResumo() const override {
        cout << "[MOTOR] Tag: " << getTag() << " | Area: " << getArea() 
             << " | Frequencia: " << frequenciaHz << " Hz" << endl;
    }
};

class ValvulaDosagem : public AtuadorLinha {
private:
    double aberturaPercentual;

public:
    ValvulaDosagem(string novaTag, string novaArea) 
        : AtuadorLinha(novaTag, novaArea), aberturaPercentual(0.0) {}

    // Aplica o percentual diretamente (0-100%)
    void aplicarReferenciaPercentual(double percentual) override {
        aberturaPercentual = limitarPercentual(percentual);
    }

    void exibirResumo() const override {
        cout << "[VALVULA] Tag: " << getTag() << " | Area: " << getArea() 
             << " | Abertura: " << aberturaPercentual << "%" << endl;
    }
};

int main() {
    // 1. Criando instâncias das classes derivadas
    MotorEsteira* esteiraPrincipal = new MotorEsteira("MOT-01", "Envase");
    ValvulaDosagem* valvulaEntrada = new ValvulaDosagem("VAL-02", "Tanque A");

    // 2. Armazenando no vetor polimórfico de ponteiros da base
    vector<AtuadorLinha*> atuadores;
    atuadores.push_back(esteiraPrincipal);
    atuadores.push_back(valvulaEntrada);

    // 3. Aplicando a mesma referência (80%) para ambos
    double comandoSetPoint = 80.0;
    cout << "--- Enviando comando de " << comandoSetPoint << "% para a linha ---" << endl;

    for (AtuadorLinha* atuador : atuadores) {
        atuador->aplicarReferenciaPercentual(comandoSetPoint);
    }

    // 4. Exibindo resumos
    for (const AtuadorLinha* atuador : atuadores) {
        atuador->exibirResumo();
    }
    // Limpeza de memória
    delete esteiraPrincipal;
    delete valvulaEntrada;

    return 0;
}