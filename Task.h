#pragma once
#include <string>

struct Task {
    int id;
    std::string requiredProduct;
    int requiredQuantity;
    int rewardBalance;
    int rewardScore;

    Task(int taskId, std::string product, int qty, int rb, int rs)
        : id(taskId), requiredProduct(product), requiredQuantity(qty),
        rewardBalance(rb), rewardScore(rs) {
    }
};
