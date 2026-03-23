#include <iostream>
#include <string>

using namespace std;

class AtivoCampo {
private:
    // Acesso restrito: apenas AtivoCampo pode alterar diretamente.
    string tag;
    bool bloqueado;

protected:
    // Acesso permitido para a própria classe e suas derivadas.
    string area;

    void redefinirArea(string novaArea) {
        area = novaArea;
    }

public:
    AtivoCampo(string novaTag, string novaArea)
        : tag(novaTag), bloqueado(false), area(novaArea) {}

    string getTag() const { return tag; }
    bool estaBloqueado() const { return bloqueado; }
    void bloquear() { bloqueado = true; }
    void liberar() { bloqueado = false; }
};

// Declaração antecipada para a friend function
class SensorNivel;
void inspecaoTecnicaSensor(const SensorNivel& sensor);

class SensorNivel : public AtivoCampo {
private:
    double nivelAtual;
    double limiteAlto;

public:
    // Construtor reaproveitando a base AtivoCampo
    SensorNivel(string novaTag, string novaArea, double nivel, double limite)
        : AtivoCampo(novaTag, novaArea), nivelAtual(nivel), limiteAlto(limite) {}

    // Regras de negócio encapsuladas no setter
    void atualizarNivel(double novoNivel) {
        if (estaBloqueado()) {
            cout << "Bloqueio: Nao e possivel alterar o nivel do sensor " << getTag() << ".\n";
            return;
        }
        if (novoNivel < 0) {
            cout << "Erro: O nivel nao pode ser negativo.\n";
            return;
        }
        nivelAtual = novoNivel;
    }

    void exibirResumo() const {
        // Usa getTag() pois 'tag' é private na base. 'area' é acessível pois é protected.
        cout << "[Sensor] Tag: " << getTag() << " | Area: " << area 
             << " | Nivel Atual: " << nivelAtual << " | Limite Alto: " << limiteAlto << "\n";
    }

    // Declaração da friend function
    friend void inspecaoTecnicaSensor(const SensorNivel& sensor);
};

// Definição da friend function: acessa os membros private de SensorNivel diretamente.
void inspecaoTecnicaSensor(const SensorNivel& sensor) {
    cout << "--- Inspecao Tecnica ---\n";
    cout << "Leitura direta de memoria -> Sensor: " << sensor.getTag() 
         << " | Nivel: " << sensor.nivelAtual 
         << " | Limite: " << sensor.limiteAlto << "\n";
}

class BombaDosadora : public AtivoCampo {
private:
    double vazaoPercentual;

public:
    // Construtor reaproveitando a base AtivoCampo
    BombaDosadora(string novaTag, string novaArea, double vazao)
        : AtivoCampo(novaTag, novaArea), vazaoPercentual(vazao) {}

    // Regras de negócio encapsuladas no setter
    void ajustarVazao(double novaVazao) {
        if (estaBloqueado()) {
            cout << "Bloqueio: Nao e possivel ajustar a vazao da bomba " << getTag() << ".\n";
            return;
        }
        if (novaVazao < 0.0 || novaVazao > 100.0) {
            cout << "Erro: A vazao deve estar entre 0% e 100%.\n";
            return;
        }
        vazaoPercentual = novaVazao;
    }

    // Reaproveita o método protegido da classe base
    void moverParaArea(string novaArea) {
        redefinirArea(novaArea);
    }

    void exibirResumo() const {
        cout << "[Bomba] Tag: " << getTag() << " | Area: " << area 
             << " | Vazao: " << vazaoPercentual << "%\n";
    }
};

int main() {
    // 1. Criação dos objetos
    SensorNivel sensor("SN-001", "Tanque A", 10.5, 80.0);
    BombaDosadora bomba("BD-101", "Tratamento", 50.0);

    // 2. Atualização de estados (Testando lógicas e bloqueios)
    sensor.atualizarNivel(15.0); // Sucesso
    sensor.atualizarNivel(-5.0); // Falha (nível negativo)
    
    bomba.bloquear();
    bomba.ajustarVazao(75.0);    // Falha (bomba bloqueada)
    bomba.liberar();
    bomba.ajustarVazao(75.0);    // Sucesso
    bomba.moverParaArea("Tratamento Secundario"); // Testa o método protected

    // 3. Resumo e inspeção
    cout << "\n=== RESUMO OPERACIONAL ===\n";
    sensor.exibirResumo();
    bomba.exibirResumo();

    cout << "\n";
    inspecaoTecnicaSensor(sensor); // Chama a friend function

    return 0;
}