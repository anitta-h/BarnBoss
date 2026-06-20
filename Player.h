#pragma once
#include "User.h"
#include "Barn.h"
#include "Farm.h"
#include "TaskBoard.h"

class Player : public User {
Barn barn;
Farm farm;
int balance;
int score;

public:
    Player(std::string name, std::string pass);

    void profileInfo() const override;
    void checkBarn() const;
    void checkFarm() const;
    void checkBalance() const;
    void checkScore() const;

    bool buyItem(int productId, int quantity); 
    bool sellItem(int productId, int quantity); 
    void addReward(int b, int s);

    void sowPlant(int seedId); 
    void addAnimal(int animalId); 
    void harvest();
    void completeTask(int taskId);

    void expandCropland(); 
    void expandFarmland();

    int getScore() const;
    int getBalance() const;
    void setStats(int bal, int scr, int cc, int fc);
    Barn& getBarn();
    Farm& getFarm();
    std::string getType() const override;
    
};
