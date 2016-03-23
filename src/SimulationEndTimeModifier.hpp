
#ifndef SIMULATIONENDTIMEMODIFIER_HPP
#define SIMULATIONENDTIMEMODIFIER_HPP

#include "AbstractCellBasedSimulationModifier.hpp"

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
class SimulationEndTimeModifier : public AbstractCellBasedSimulationModifier<ELEMENT_DIM,SPACE_DIM> {
                                   
  private:

  public:

    /**
     * Specify what to do in the simulation at the end of each output timestep.
     *
     * @param rCellPopulation reference to the cell population
     */
    void UpdateAtEndOfOutputTimeStep(AbstractCellPopulation<ELEMENT_DIM,SPACE_DIM>& rCellPopulation){
    }


    /**
     * Specify what to do in the simulation at the end of each timestep.
     *
     * @param rCellPopulation reference to the cell population
     */
    void UpdateAtEndOfTimeStep(AbstractCellPopulation<ELEMENT_DIM,SPACE_DIM>& rCellPopulation)
    {
      // need to get number of different clones
      
      /*
      std::vector<unsigned> location_indices = generator.GetCellLocationIndices();
      for(int i = 0; i < (int) location_indices.size(); i++){
        std::cout << location_indices[i] << std::endl;
      }
      */

      
      // if number of different clones is = 1, terminate (i.e. set simulation end time to now)
      
      
    }




};


#endif //SIMULATIONENDTIMEMODIFIER_HPP
