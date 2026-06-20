#include "TaskManager.h"
#include <iostream>


TaskManager::TaskManager(std::string n, std::string p) : User(n, p) {}

void TaskManager::showTasks() const
{
	TaskBoard::getInstance().showBoard();
}

void TaskManager::addTask(std::string product, int q, int rewardB, int rewardS)
{
	TaskBoard::getInstance().addTask(product, q, rewardB, rewardS);
	std::cout << "Task added successfully!\n";
}

void TaskManager::removeTask(int taskId)
{
    if (TaskBoard::getInstance().removeTask(taskId)) {
        std::cout << "Task removed successfully!\n";
    }
    else {
        std::cout << "Task not found!\n";
    }
}

std::string TaskManager::getType() const
{
    return "TaskManager";
}

void TaskManager::profileInfo() const
{
    User::profileInfo();
    std::cout << "Type: TaskManager\n";
}

void TaskManager::logout()
{
    std::cout << "TaskManager " << getUsername() << " logged out successfully.\n";
}



