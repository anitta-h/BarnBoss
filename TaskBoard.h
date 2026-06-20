#pragma once
#include <vector>
#include "Task.h"


class TaskBoard {
private:
    std::vector<Task> tasks;
    int nextId;
    

public:
    TaskBoard();
    TaskBoard(const TaskBoard&) = delete;
    TaskBoard& operator=(const TaskBoard&) = delete;
    static TaskBoard& getInstance();
    void showBoard() const;
    void addTask(std::string product, int qty, int rb, int rs);
    bool removeTask(int taskId);
    const std::vector<Task>& getTasks() const;
    Task* getTaskById(int taskId);
    void setTasks(const std::vector<Task>& newTasks, int nId) { tasks = newTasks; nextId = nId; }
};

