#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

class Plotter {
private:
    std::ofstream file;                     // Arquivo CSV mantido aberto
    bool headersWritten = false;            // Verifica se os cabeçalhos já foram escritos

public:
    // Construtor
    Plotter(const std::string& filename) {
        file.open(filename, std::ios::out | std::ios::app);  // Abre em modo de anexar
        if (!file.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo para escrita: " + filename);
        }
    }

    // Destrutor para fechar o arquivo ao final
    ~Plotter() {
        if (file.is_open()) {
            file.close();
        }
    }

    // Escrever cabeçalhos no arquivo
    void writeHeaders(const std::vector<std::string>& headers) {
        if (!headersWritten) {
            for (size_t i = 0; i < headers.size(); ++i) {
                file << headers[i];
                if (i < headers.size() - 1) file << ",";
            }
            file << "\n";
            headersWritten = true;
        }
    }

    void clearFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc); // Abre o arquivo no modo truncar
        if (!file.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo para limpeza: " + filename);
        }
        file.close();
    }

    // Adicionar uma nova linha de dados
    void addDataRow(const std::vector<double>& rowData) {
        if (!file.is_open()) {
            throw std::runtime_error("Arquivo não está aberto para escrita.");
        }

        for (size_t i = 0; i < rowData.size(); ++i) {
            file << rowData[i];
            if (i < rowData.size() - 1) file << ";";
        }
        file << "\n";
        file.flush();  // Garante que os dados sejam escritos imediatamente
    }
};

#endif // PLOTTER_H
