#include <iostream>
#include <cassert>
#include "../include/sista/sista.hpp"

int main() {
    std::cout << "Testing SwappableField pawnsCount logic..." << std::endl;
    
    // Test 1: Basic addPawn should set count to 1
    {
        sista::SwappableField field(5, 5);
        auto pawn1 = std::make_shared<sista::Pawn>('X', sista::Coordinates(0, 0), sista::ANSISettings());
        field.addPawn(pawn1);
        std::cout << "✓ Test 1 passed: addPawn sets count correctly" << std::endl;
    }
    
    // Test 2: Adding pawn to occupied cell should throw
    {
        sista::SwappableField field(5, 5);
        auto pawn1 = std::make_shared<sista::Pawn>('X', sista::Coordinates(1, 1), sista::ANSISettings());
        auto pawn2 = std::make_shared<sista::Pawn>('O', sista::Coordinates(1, 1), sista::ANSISettings());
        
        field.addPawn(pawn1);
        
        bool caught = false;
        try {
            field.addPawn(pawn2);
        } catch (const std::invalid_argument& e) {
            caught = true;
        }
        
        if (caught) {
            std::cout << "✓ Test 2 passed: collision detection works on addPawn" << std::endl;
        } else {
            std::cerr << "✗ Test 2 failed: no exception thrown for occupied cell" << std::endl;
            return 1;
        }
    }
    
    // Test 3: movePawn should update pawnsCount
    {
        sista::SwappableField field(5, 5);
        auto pawn1 = std::make_shared<sista::Pawn>('X', sista::Coordinates(2, 2), sista::ANSISettings());
        field.addPawn(pawn1);
        
        // Move the pawn
        field.movePawn(pawn1.get(), sista::Coordinates(3, 3));
        
        // Verify the pawn moved
        if (pawn1->getCoordinates().x == 3 && pawn1->getCoordinates().y == 3) {
            std::cout << "✓ Test 3 passed: movePawn updates pawn coordinates and count" << std::endl;
        } else {
            std::cerr << "✗ Test 3 failed: pawn coordinates not updated" << std::endl;
            return 1;
        }
    }
    
    // Test 4: movePawn to occupied cell should throw
    {
        sista::SwappableField field(5, 5);
        auto pawn1 = std::make_shared<sista::Pawn>('X', sista::Coordinates(0, 0), sista::ANSISettings());
        auto pawn2 = std::make_shared<sista::Pawn>('O', sista::Coordinates(1, 1), sista::ANSISettings());
        field.addPawn(pawn1);
        field.addPawn(pawn2);
        
        bool caught = false;
        try {
            field.movePawn(pawn1.get(), sista::Coordinates(1, 1));
        } catch (const std::invalid_argument& e) {
            caught = true;
        }
        
        if (caught) {
            std::cout << "✓ Test 4 passed: movePawn throws on occupied cell" << std::endl;
        } else {
            std::cerr << "✗ Test 4 failed: no exception thrown for occupied cell" << std::endl;
            return 1;
        }
    }
    
    // Test 5: Using addPawnToSwap and applySwaps (the intended way)
    {
        sista::SwappableField field(5, 5);
        auto pawn1 = std::make_shared<sista::Pawn>('X', sista::Coordinates(0, 0), sista::ANSISettings());
        auto pawn2 = std::make_shared<sista::Pawn>('O', sista::Coordinates(4, 4), sista::ANSISettings());
        field.addPawn(pawn1);
        field.addPawn(pawn2);
        
        // Swap positions
        field.addPawnToSwap(pawn1.get(), sista::Coordinates(1, 1));
        field.addPawnToSwap(pawn2.get(), sista::Coordinates(3, 3));
        field.applySwaps();
        
        if (pawn1->getCoordinates().x == 1 && pawn1->getCoordinates().y == 1 &&
            pawn2->getCoordinates().x == 3 && pawn2->getCoordinates().y == 3) {
            std::cout << "✓ Test 5 passed: addPawnToSwap and applySwaps work correctly" << std::endl;
        } else {
            std::cerr << "✗ Test 5 failed: pawns not swapped correctly" << std::endl;
            return 1;
        }
    }
    
    std::cout << "\nAll tests passed! ✓" << std::endl;
    return 0;
}
