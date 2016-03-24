
#ifndef SIMULATIONENDTIMEMODIFIER_HPP
#define SIMULATIONENDTIMEMODIFIER_HPP

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>

#include "SimulationTime.hpp"

#include "AbstractCellBasedSimulationModifier.hpp"



template<unsigned SPACE_DIM>
class SimulationEndTimeModifier : public AbstractCellBasedSimulationModifier<SPACE_DIM,SPACE_DIM>
{
                                   
  private:
	   /** Needed for serialization. */
	    friend class boost::serialization::access;
	    /**
	     * Boost Serialization method for archiving/checkpointing.
	     * Archives the object and its member variables.
	     *
	     * @param archive  The boost archive.
	     * @param version  The current version of this class.
	     */
	    template<class Archive>
	    void serialize(Archive & archive, const unsigned int version)
	    {
	        archive & boost::serialization::base_object<AbstractCellBasedSimulationModifier<SPACE_DIM,SPACE_DIM> >(*this);
	    }
  public:

	    /**
	     * Default constructor.
	     */
	    SimulationEndTimeModifier();

	    /**
	     * Destructor.
	     */
	    virtual ~SimulationEndTimeModifier();

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

		  std::cout << "Time = " << SimulationTime::Instance()->GetTime() << "\t num_cells = " << rCellPopulation.GetNumNodes() << std::endl;

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
		void OutputSimulationModifierParameters(out_stream& rParamsFile);

};


#include "SerializationExportWrapper.hpp"
EXPORT_TEMPLATE_CLASS_SAME_DIMS(SimulationEndTimeModifier)

#endif //SIMULATIONENDTIMEMODIFIER_HPP
