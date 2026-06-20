#include "TaskBoard.h"
#include <iostream>

TaskBoard::TaskBoard() : nextId(1) {
    addTask("Wheat", 5, 50, 10);
    addTask("Milk", 3, 120, 20);
}

Task* TaskBoard::getTaskById(int taskId)
{
    for (auto& task : tasks) {
        if (task.id == taskId) {
            return &task;
        }
    }
    return nullptr;
}

TaskBoard& TaskBoard::getInstance()
{
    static TaskBoard instance;
    return instance;
}

void TaskBoard::showBoard() const
{
    std::cout << "=== TASK BOARD ===\n";
    for (const auto& t : tasks) {
        std::cout << t.id << ". Deliver " << t.requiredQuantity << " " << t.requiredProduct
            << " -> Reward: " << t.rewardBalance << " Balance, " << t.rewardScore << " Score\n";
    }
}

void TaskBoard::addTask(std::string product, int qty, int rb, int rs)
{
    tasks.emplace_back(nextId++, product, qty, rb, rs);
}

bool TaskBoard::removeTask(int taskId)
{
    auto it = std::remove_if(tasks.begin(), tasks.end(),
        [taskId](const Task& t) { return t.id == taskId; });

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return true;
    }
    return false;
}

const std::vector<Task>& TaskBoard::getTasks() const
{
    return tasks;
}

