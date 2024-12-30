#pragma once

#include <iostream>
#include <vector>

typedef void (*task_t)();
std::vector<task_t> tasks;

void task1()
{
    std::cout << "LOL: Refresh the log." << std::endl;
}

void task2()
{
    std::cout << "LOL: Update the jungle." << std::endl;
}

void task3()
{
    std::cout << "LOL: Detect software updates." << std::endl;
}

void task4()
{
    std::cout << "LOL: The user releases a skill and this task updates the user's blood and mana levels." << std::endl;
}

void LoadTask(std::vector<task_t>* tasks)
{
    tasks->push_back(task1);
    tasks->push_back(task2);
    tasks->push_back(task3);
    tasks->push_back(task4);
}
