#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Employee {
protected:
    std::string name;

public:
    Employee(const std::string& employeeName) : name(employeeName) {}

    virtual void receiveInstruction(int instruction) = 0;
};

class Worker : public Employee {
public:
    Worker(const std::string& workerName) : Employee(workerName) {}

    void receiveInstruction(int instruction) override {
        std::srand(instruction);
        std::string tasks[] = { "Task A", "Task B", "Task C" };
        std::string taskName = tasks[rand() % 3];
        std::cout << "Worker " << name << " received instruction: " << taskName << std::endl;
    }
};

class Manager : public Employee {
private:
    std::vector<Worker*> workers;

public:
    Manager(const std::string& managerName, const std::vector<Worker*>& employeeWorkers) : Employee(managerName), workers(employeeWorkers) {}

    void receiveInstruction(int instruction) override {
        std::srand(instruction);
        int tasksCount = rand() % (workers.size() + 1);
        for (int i = 0; i < tasksCount; ++i) {
            int workerIndex = rand() % workers.size();
            workers[workerIndex]->receiveInstruction(instruction + i);
        }
        std::cout << "Manager " << name << " distributed tasks to workers." << std::endl;
    }
};

class Company {
private:
    Manager* head;
    std::vector<Manager*> middleManagers;
    std::vector<Worker*> workers;

public:
    Company(int numTeams, int numWorkersPerTeam) {
        std::cout << "Creating company with " << numTeams << " teams and " << numWorkersPerTeam << " workers per team." << std::endl;

        for (int i = 0; i < numTeams; ++i) {
            for (int j = 0; j < numWorkersPerTeam; ++j) {
                std::string workerName = "Worker " + std::to_string(i + 1) + "-" + std::to_string(j + 1);
                workers.push_back(new Worker(workerName));
            }
        }

        for (int i = 0; i < numTeams; ++i) {
            std::vector<Worker*> teamWorkers(workers.begin() + (i * numWorkersPerTeam), workers.begin() + ((i + 1) * numWorkersPerTeam));
            std::string managerName = "Manager " + std::to_string(i + 1);
            middleManagers.push_back(new Manager(managerName, teamWorkers));
        }

        std::vector<Worker*> allWorkers(workers.begin(), workers.end());
        std::string headName = "Head";
        head = new Manager(headName, allWorkers);
    }

    ~Company() {
        for (Worker* worker : workers) {
            delete worker;
        }
        for (Manager* manager : middleManagers) {
            delete manager;
        }
        delete head;
    }

    void simulateCompanyOperation() {
        std::cout << "Simulation of company operation started." << std::endl;

        int instruction;
        while (!workers.empty()) {
            std::cout << "Enter an instruction for the head of the company (integer): ";
            std::cin >> instruction;
            head->receiveInstruction(instruction);
        }

        std::cout << "All workers are busy with tasks. Simulation ended." << std::endl;
    }
};

int main() {
    int numTeams, numWorkersPerTeam;
    std::cout << "Enter the number of teams in the company: ";
    std::cin >> numTeams;
    std::cout << "Enter the number of workers per team: ";
    std::cin >> numWorkersPerTeam;

    Company company(numTeams, numWorkersPerTeam);
    company.simulateCompanyOperation();

    return 0;
}
