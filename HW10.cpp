//Задание
//Создать :
//Класс Connector - который осуществляет работу с абстрактным Device.Устройство можно менять по необходимости, для этого реализовать соответствующий функционал.
//Класс Device имеющим возможность что - то выводить на устройство и что - то получать с устройства.
//Класс Data который может быть использован для разных видов данных.
//Разработать классы устройств — Монитор, файл, принтер, сеть, сканер.
//Разработать классы для хранения разных видов данных.
//Устройства Монитор и файл реализовать полноценно, а остальные  устройства  выполнить условно реализованными.
//Разработать приложение в котором есть обьект Data.Данный обьект может быть отправлен на любое выбранное устройство с помощью  Connector.

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Device {
public:
    virtual void output(const string& data) = 0; 
    virtual string input() = 0; 
    virtual ~Device() = default; 
};

class Monitor : public Device {
public:
    void output(const string& data) override {
        std::cout << "Output to Monitor: " << data << std::endl;
    }

    string input() override {
        return "Input from Monitor";
    }
};

class File : public Device {
private:
    string filename;

public:
    File(const string& fname) : filename(fname) {}

    void output(const string& data) override {
        ofstream ofs(filename, ios::app);
        if (ofs.is_open()) {
            ofs << data << std::endl;
            ofs.close();
        }
    }

    string input() override {
        ifstream ifs(filename);
        string line;
        if (ifs.is_open()) {
            getline(ifs, line);
            ifs.close();
        }
        return line; 
    }
};

class Printer : public Device {
public:
    void output(const string& data) override {
        cout << "Output to Printer: " << data << endl;
    }

    string input() override {
        return "Input from Printer"; 
    }
};

class Network : public Device {
public:
    void output(const string& data) override {
        cout << "Output to Network: " << data << endl;
    }

    string input() override {
        return "Input from Network";
    }
};

class Scanner : public Device {
public:
    void output(const string& data) override {
       cout << "Output to Scanner: " << data << endl; 
    }

    string input() override {
        return "Input from Scanner"; 
    }
};

class Data {
private:
    string content;

public:
    Data(const string& data) : content(data) {}

    const string& getContent() const {
        return content;
    }
};

class Connector {
private:
    Device* device;

public:
    Connector(Device* dev) : device(dev) {}

    void setDevice(Device* dev) {
        device = dev;
    }

    void sendData(const Data& data) {
        device->output(data.getContent());
    }

    Data receiveData() {
        return Data(device->input());
    }
};

int main() {
    Monitor monitor;

    File file("output.txt");
    Data data("Hello, World!");

    Connector connector(&monitor);

    connector.sendData(data); // Отправка данных на монитор

    connector.setDevice(&file);
    connector.sendData(data); // Отправка данных в файл

    return 0;
}
