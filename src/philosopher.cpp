#include "../headers/philosopher.h"

Philosopher::Philosopher (
        const std::string &name,
        int appetite,
        Fork& leftFork,
        Fork& rightFork,
        std::mutex& gLock)
    : m_name(name),
      m_appetite(appetite),
      m_leftFork(leftFork),
      m_rightFork(rightFork),
      m_gLock(gLock),
      m_foodEaten(0),
      m_stopped(false)
{
    m_thread = std::thread(&Philosopher::run, this);
    printAction("присоединился");
}

Philosopher::~Philosopher() {
    printAction("закончил");
}

void Philosopher::eat() {
    // Захват вилок
    std::lock_guard<std::mutex> lc(m_leftFork.mtx);
    std::lock_guard<std::mutex> rc(m_rightFork.mtx);

    // Инкрементируем сколько порций уже съел филосов
    ++m_foodEaten;
    printAction("ест (" + std::to_string(m_foodEaten) + "/" + std::to_string(m_appetite) + ")");
    ponder(3, 5);
}

void Philosopher::think() {
    printAction("думает");
    ponder(2, 4);
}

void Philosopher::ponder(int min_sec, int max_sec) {
    if (m_stopped) return;
    // Рандомное число на отрезке
    thread_local std::uniform_int_distribution<> dist(min_sec, max_sec);
    int t = dist(m_range);
    // Спим рандомное время
    std::this_thread::sleep_for(std::chrono::milliseconds(t * 500));

    // Если аппетит философа удовлетворён то останавливаемся
    if (m_foodEaten >= m_appetite) m_stopped = true;
}

void Philosopher::printAction(const std::string &msg) {
    // захват мьютекса для печати действий философа
    std::lock_guard<std::mutex> coutLock(m_gLock);
    std::cout << m_name << " " << msg << std::endl;
}

void Philosopher::stop() {
    // остановка философов
    m_stopped = true;
}

void Philosopher::run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // пока не остановимся думаем и едим
    while (!m_stopped) {
        think();
        if (m_stopped) break;
        eat();
    }
    printAction("закончил");
}

void Philosopher::join()
{
    m_thread.join();
}
