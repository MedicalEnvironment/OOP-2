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
    std::vector<Branch> trees(5);

    // Tree 1
    Branch* tree1Branch1 = new Branch();
    Branch* tree1Branch2 = new Branch();
    Branch* tree1Branch3 = new Branch();
    trees[0].addChildBranch(tree1Branch1);
    trees[0].addChildBranch(tree1Branch2);
    trees[0].addChildBranch(tree1Branch3);

    // Tree 2
    Branch* tree2Branch1 = new Branch();
    Branch* tree2Branch2 = new Branch();
    Branch* tree2Branch3 = new Branch();
    Branch* tree2Branch4 = new Branch();
    trees[1].addChildBranch(tree2Branch1);
    trees[1].addChildBranch(tree2Branch2);
    trees[1].addChildBranch(tree2Branch3);
    trees[1].addChildBranch(tree2Branch4);

    // Tree 3
    Branch* tree3Branch1 = new Branch();
    Branch* tree3Branch2 = new Branch();
    Branch* tree3Branch3 = new Branch();
    trees[2].addChildBranch(tree3Branch1);
    trees[2].addChildBranch(tree3Branch2);
    trees[2].addChildBranch(tree3Branch3);

    // Tree 4
    Branch* tree4Branch1 = new Branch();
    Branch* tree4Branch2 = new Branch();
    trees[3].addChildBranch(tree4Branch1);
    trees[3].addChildBranch(tree4Branch2);

    // Tree 5
    Branch* tree5Branch1 = new Branch();
    Branch* tree5Branch2 = new Branch();
    trees[4].addChildBranch(tree5Branch1);
    trees[4].addChildBranch(tree5Branch2);

    // Set parent branches
    tree1Branch1->setParentBranch(&trees[0]);
    tree1Branch2->setParentBranch(&trees[0]);
    tree1Branch3->setParentBranch(&trees[0]);

    tree2Branch1->setParentBranch(&trees[1]);
    tree2Branch2->setParentBranch(&trees[1]);
    tree2Branch3->setParentBranch(&trees[1]);
    tree2Branch4->setParentBranch(&trees[1]);

    tree3Branch1->setParentBranch(&trees[2]);
    tree3Branch2->setParentBranch(&trees[2]);
    tree3Branch3->setParentBranch(&trees[2]);

    tree4Branch1->setParentBranch(&trees[3]);
    tree4Branch2->setParentBranch(&trees[3]);

    tree5Branch1->setParentBranch(&trees[4]);
    tree5Branch2->setParentBranch(&trees[4]);

    // Place the elves in the houses
    for (auto& tree : trees) {
        placeElves(&tree);
    }

    // Search for a specific elf
    std::string searchName;
    std::cout << "Enter the name of the elf you are looking for: ";
    std::cin >> searchName;

    Branch* foundElf = nullptr;
    for (auto& tree : trees) {
        foundElf = tree.searchElf(searchName);
        if (foundElf != nullptr)
            break;
    }

    if (foundElf != nullptr) {
        int totalNeighbors = foundElf->getTotalNeighbors();
        std::cout << "The total number of neighbors for " << searchName << " is: " << totalNeighbors << std::endl;
    } else {
        std::cout << "Elf not found!" << std::endl;
    }

    // Clean up memory
    for (auto& tree : trees) {
        delete tree.getChildBranches()[0];
        delete tree.getChildBranches()[1];
    }

    return 0;
}
