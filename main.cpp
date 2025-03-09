#include <iostream>
#include "tree.h"

enum class Instruction {
    ReadFromFile,
    ManualInput
};

enum class Operation {
    SearchKey,
    AddNode,
    RemoveNode,
    PrintInOrder,
    PrintTree,
    Quit
};

Instruction getInstruction() {
    std::string input;
    std::cin >> input;
    if (input == "file") {
        return Instruction::ReadFromFile;
    } else if (input == "manual") {
        return Instruction::ManualInput;
    } else {
        throw std::invalid_argument("Invalid input");
    }
}

Operation getOperation() {
    std::string input;
    std::cin >> input;
    if (input == "search") {
        return Operation::SearchKey;
    } else if (input == "add") {
        return Operation::AddNode;
    } else if (input == "remove") {
        return Operation::RemoveNode;
    } else if (input == "print_inorder") {
        return Operation::PrintInOrder;
    } else if (input == "print_tree") {
        return Operation::PrintTree;
    } else if (input == "quit") {
        return Operation::Quit;
    } else {
        throw std::invalid_argument("Invalid operation");
    }
}

int main() {
    std::cout << "Red-Black Tree implementation\n by Lorenzo Esposito\n";
    std::cout << "Choose the node input method:\n - Read from file (file)\n - Manual input (manual)\n";

    tree rbTree;
    int numNodes;
    Instruction instr;
    try {
        instr = getInstruction();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (instr == Instruction::ReadFromFile) {
        std::string filename;
        std::cout << "Enter the filename:\n";
        std::cin >> filename;

        tree fileTree(filename);
        rbTree = fileTree;

    } else if (instr == Instruction::ManualInput) {
        std::cout << "How many nodes do you want to insert?\n";
        std::cin >> numNodes;

        for (int i = 1; i <= numNodes; ++i) {
            int key;
            std::cout << "Enter the key for node " << i << "\n";
            std::cin >> key;
            rbTree.insertNode(key);
        }
    }

    while (true) {
        std::cout << "Choose an operation:\n - Search for a key (search)\n - Add a node (add)\n - Remove a node (remove)\n - Print in-order (print_inorder)\n - Print tree structure, not stable (print_tree)\n - Quit (quit)\n";
        Operation op;
        try {
            op = getOperation();
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            continue;
        }

        if (op == Operation::SearchKey) {
            int key;
            std::cout << "Enter the key to search:\n";
            std::cin >> key;
            if (rbTree.isKeyInside(key)) {
                std::cout << key << " is inside the three\n";
            } else {
                std::cout << key << " is not inside the three\n";
            }
        } else if (op == Operation::AddNode) {
            int key;
            std::cout << "Enter the key to add:\n";
            std::cin >> key;
            rbTree.insertNode(key);
            std::cout << "key " << key << " added\n";
        } else if (op == Operation::RemoveNode) {
            int key;
            std::cout << "Enter the key to remove:\n";
            std::cin >> key;
            rbTree.deleteNode(key);
            std::cout << "key " << key << " removed\n";
        } else if (op == Operation::PrintInOrder) {
            std::cout << "RBTree value in order:\n";
            rbTree.inOrderTraversal(rbTree.getRoot());
            std::cout << std::endl;
        } else if (op == Operation::PrintTree) {
            std::cout << "Tree structure:\n";
            rbTree.printTree(rbTree.getRoot(), 0);
            std::cout << std::endl;
        } else if (op == Operation::Quit) {
            break;
        }
    }

    return 0;
}


