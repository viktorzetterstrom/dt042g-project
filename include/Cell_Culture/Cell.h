/**
 * @file Cell.h
 * @author Erik Ström
 * @brief 
 * @version 0.1
 * @date 2018-10-30
 */

#ifndef cellH
#define cellH

#include "../../terminal/terminal.h"

/**
 * @brief Data structure holding colors to visualize the state of cells.
 */
struct StateColors {
    COLOR LIVING, // Representing living cell
            DEAD, // Representing dead cell
            OLD,  // Representing old cell
            ELDER;// Representing very old cell
}

/**
 * @brief Default color values.
 */
const STATE_COLORS = { COLOR::WHITE, COLOR::BLACK, COLOR::CYAN, COLOR::MAGENTA };

/**
 * @brief Enumeration of possible cell actions. Determined by rule.
 */
enum ACTION { KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING };

/**
 * @brief Cells represents a certain combination of row and column of the 
 * simulated world.
 * 
 * @details Cells may be of two types; rim cells, those representing the outer 
 * limits of the world, or non-rim cells. The first cell type are immutable, 
 * exempt from the game's rules, and thus their values may not be changed. The 
 * latter type, however, may be changed and editedin ways specified by the 
 * rules.
 */
class Cell {
private:
    /**
     * @brief Struct that encapsulates the details about the Cell.
     */
    struct CellDetails {
        int age;
        COLOR color;
        bool rimCell;
        char value;
    } details;

    /**
     * @brief Struct that encapsulates the changes to be made next generation
     *  of the simulation.
     */
    struct NextUpdate {
        ACTION nextGenerationAction;
        COLOR nextColor;
        char nextValue;
        bool willBeAlive;	// some rules may need to know beforehand whether the cell will be alive
    } nextUpdate;

    /**
     * @brief Increments the age property in CellDetails by one.
     */
    void incrementAge() { details.age++; }

    /**
     * @brief Sets the age property in CellDetails to zero.
     */
    void killCell() { details.age = 0; }

    /**
     * @brief Sets the value property of CellDetails to value. Which will be 
     *  printed on the screen for that cell.
     * 
     * @param value Char which will be printed to screen.
     */
    void setCellValue(char value) { details.value = value; }

    /**
     * @brief Set the color property of CellDetails to color.
     * @todo remove this->, to use consequent syntax for all set-functions.
     * 
     * @param color Color to be used.
     */
    void setColor(COLOR color) { this->details.color = color; }

public:

    /**
     * @brief Construct a new Cell object
     * 
     * @param isRimCell True if the cell is a rim cell, default is false.
     * @param action Specify an ACTION for the cell, default is DO_NOTHING.
     */
    Cell(bool isRimCell = false, ACTION action = DO_NOTHING);

    /**
     * @brief Returns true if cell is alive.
     * @details Cell is said to be alive if it is not a rim cell and has an age
     *  that is larger than zero.
     * 
     * @return true If cell is not a rim cell and age is larger than zero.
     * @return false Otherwise.
     */
    bool isAlive();

    /**
     * @brief Set the NextGenerationAction in NextUpdate to action.
     * @details Does not work on rim cells.
     * 
     * @param action ACTION for next generation in the simulation.
     */
    void setNextGenerationAction(ACTION action);

    /**
     * @brief Uses NextUpdate to update the cell state for the next generation.
     * @details If the action is KILL_CELL the cell is killed. If the next 
     *  action is IGNORE_CELL it is kept alive and age is incremented. If the
     *  action is GIVE_CELL_LIFE the age is incremented given it is not a rim
     *  cell.
     */
    void updateState();

    /**
     * @brief Returns the age of the cell.
     * @details Age is stored in CellDetails.
     * 
     * @return int Current cell age.
     */
    int getAge() { return details.age; }

    /**
     * @brief Returns color of the cell.
     * @details Color is stored in CellDetails
     * 
     * @return COLOR Current cell color.
     */
    COLOR getColor() { return details.color; }

    /**
     * @brief Returns true if the cell is a rim cell.
     * @details Determines whether the cell is a rim cell, and thus should be 
     *  immutable.
     * 
     * @return true If cell is a rim cell.
     * @return false Otherwise.
     */
    bool isRimCell() { return details.rimCell; }

    /**
     * @brief Sets the color the cell will have after its next update.
     * 
     * @param nextColor Next color for cell.
     */
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }

    /**
     * @brief Returns the value of the cell.
     * 
     * @return char Current cell value.
     */
    char getCellValue() { return details.value; }

    /**
     * @brief Sets the next character value of the cell, which will be printed 
     *  to screen.
     * 
     * @param value Next cell value.
     */
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    /**
     * @brief Sets whether the cell is alive/dead next generation.
     * 
     * @param isAliveNext true if alive, false if dead.
     */
    void setIsAliveNext(bool isAliveNext) { nextUpdate.willBeAlive = isAliveNext; }

    // Will the cell be alive next generation?
    /**
     * @brief Returns true if the cell will be alive next generation.
     * 
     * @return true If willBeAlive in NextUpdate is true.
     * @return false Otherwise.
     */
    bool isAliveNext() { return nextUpdate.willBeAlive; }

    /**
     * @brief Returns the cells next action.
     * 
     * @return ACTION& Next cell action.
     */
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }
};

#endif
