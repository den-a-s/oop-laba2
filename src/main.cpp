#include <array>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <stdlib.h>
#include <locale>

#include "../headers/philosopher.h"
#include "../headers/fork.h"

std::array<Philosopher *, 5> philosophers;

// Инициализируем философов
void initPhilosophers(int appetite, std::mutex & mtx, std::array<Fork, 5> & forks) {
    std::array<std::string, 5> names = {
        "Платон",
        "Сократ",
        "Кант",
        "Декарт",
        "Конфуций",
    };
    std::array<std::string, 6> colors = {
        "\033[31m", // red
        "\033[33m", // yellow
        "\033[32m", // green
        "\033[34m", // blue
        "\033[35m", // purple
        "\033[00m", // white
    };
    for (int i = 0; i < names.size(); i++) {
        // индекс соседней вилки
        int rc = (i + 1) % names.size();
        philosophers[i] = new Philosopher(colors[i] + names[i] + colors.back(), appetite, forks[i], forks[rc], mtx);
    }
}

// Останавливает всех философов при выходе
void quit(int s) {
    for (Philosopher *p : philosophers)
        p->stop();
    std::cout << std::endl << "Обед окончен. Позволяю философам закончить..." << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Мьютек для синхронизации вывода
    std::mutex outLock;
    // Вилки философов
    std::array<Fork, 5> forks;
    std::cout << "Обед подан! (нажмите Ctl+C, чтобы закончить)" << std::endl;
    std::cout << std::endl << "Философы: " << std::endl;
    initPhilosophers(100, outLock, forks);
    std::cout << std::endl << std::endl;
    // Функция которая вызовется при Ctr+C
    signal(SIGINT, quit);
    // Запуск потоков
    for (Philosopher *p : philosophers)
        p->join();
    return 0;
}
