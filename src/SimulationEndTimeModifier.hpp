
#ifndef SIMULATIONENDTIMEMODIFIER_HPP
#define SIMULATIONENDTIMEMODIFIER_HPP

#include "AbstractCellBasedSimulationModifier.hpp"

template<unsigned SPACE_DIM>
class SimulationEndTimeModifier : public AbstractCellBasedSimulationModifier<SPACE_DIM,SPACE_DIM> {
                                   
  private:

  public:

    /**
     * Specify what to do in the simulation at the end of each output timestep.
     *
     * @param rCellPopulation reference to the cell population
     */
    void UpdateAtEndOfOutputTimeStep(AbstractCellPopulation<SPACE_DIM,SPACE_DIM>& rCellPopulation){
    }


    /**
     * Specify what to do in the simulation at the end of each timestep.
     *
     * @param rCellPopulation reference to the cell population
     */
    void UpdateAtEndOfTimeStep(AbstractCellPopulation<SPACE_DIM,SPACE_DIM>& rCellPopulation)
    {
      // need to get number of different clones
      
      //std::cout << rCellPopulation.GetNumNodes() << std::endl;
      
      // if number of different clones is = 1, terminate (i.e. set simulation end time to now)
      
      
    }


    /**
     * Output any simulation modifier parameters to file.
     *
     * As this method is pure virtual, it must be overridden
     * in subclasses.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    void OutputSimulationModifierParameters(out_stream& rParamsFile){
    }

};


#endif //SIMULATIONENDTIMEMODIFIER_HPP
