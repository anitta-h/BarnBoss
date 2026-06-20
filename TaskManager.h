#pragma once
#include "User.h"
#include "Task.h"
#include <vector>
#include "TaskBoard.h"

class TaskManager : public User {
public:
    TaskManager(std::string n, std::string p);
    void showTasks() const;
    void addTask(std::string product, int q, int rewardB, int rewardS);
    void removeTask(int taskId);
    std::string getType() const override;
    void profileInfo() const override;
    void logout() override;
};
