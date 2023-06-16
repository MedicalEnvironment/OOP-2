#include <iostream>
#include <vector>
#include <string>

class Branch {
private:
    std::vector<Branch*> childBranches;
    Branch* parentBranch;
    std::string elfName;

public:
    Branch() {
        parentBranch = nullptr;
        elfName = "";
    }

    void setParentBranch(Branch* parent) {
        parentBranch = parent;
    }

    void addChildBranch(Branch* child) {
        childBranches.push_back(child);
    }

    void setElfName(const std::string& name) {
        elfName = name;
    }

    std::string getElfName() const {
        return elfName;
    }

    int getTotalNeighbors() const {
        int neighbors = 0;

        for (Branch* child : childBranches) {
            if (child->getElfName() != "")
                neighbors++;
        }

        return neighbors;
    }

    std::vector<Branch*> getChildBranches() const {
        return childBranches;
    }

    Branch* getTopBranch() {
        if (parentBranch == nullptr)
            return nullptr;
        if (parentBranch->parentBranch == nullptr)
            return parentBranch;
        return parentBranch->getTopBranch();
    }

    Branch* searchElf(const std::string& name) {
        if (elfName == name)
            return this;

        for (Branch* child : childBranches) {
            Branch* result = child->searchElf(name);
            if (result != nullptr)
                return result;
        }

        return nullptr;
    }
};

void placeElves(Branch* branch) {
    std::string elfName;
    std::cout << "Enter the name of the elf for branch: ";
    std::cin >> elfName;

    if (elfName != "None") {
        branch->setElfName(elfName);

        for (Branch* child : branch->getChildBranches()) {
            placeElves(child);
        }
    }
}

int main() {
    // Generate the forest structure
    std::vector<Branch> tree(5);
    tree[0].addChildBranch(&tree[1]);
    tree[0].addChildBranch(&tree[2]);
    tree[0].addChildBranch(&tree[3]);
    tree[1].addChildBranch(&tree[4]);
    tree[2].addChildBranch(&tree[4]);
    tree[3].addChildBranch(&tree[4]);

    // Place the elves in the houses
    placeElves(&tree[0]);

    // Search for a specific elf
    std::string searchName;
    std::cout << "Enter the name of the elf you are looking for: ";
    std::cin >> searchName;

    Branch* foundElf = tree[0].searchElf(searchName);

    if (foundElf != nullptr) {
        int totalNeighbors = foundElf->getTotalNeighbors();
        std::cout << "The total number of neighbors for " << searchName << " is: " << totalNeighbors << std::endl;
    } else {
        std::cout << "Elf not found!" << std::endl;
    }

    return 0;
}
