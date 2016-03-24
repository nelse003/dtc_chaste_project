#include "SimulationEndTimeModifier.hpp"

template<unsigned SPACE_DIM>
SimulationEndTimeModifier<SPACE_DIM>::SimulationEndTimeModifier()
    : AbstractCellBasedSimulationModifier<SPACE_DIM>()
{
}

template<unsigned SPACE_DIM>
SimulationEndTimeModifier<SPACE_DIM>::~SimulationEndTimeModifier()
{
}


template<unsigned SPACE_DIM>
void SimulationEndTimeModifier<SPACE_DIM>::OutputSimulationModifierParameters(out_stream& rParamsFile)
{
    // No parameters to output, so just call method on direct parent class
    AbstractCellBasedSimulationModifier<SPACE_DIM>::OutputSimulationModifierParameters(rParamsFile);
}

// Explicit instantiation
//template class SimulationEndTimeModifier<1>;
template class SimulationEndTimeModifier<2>;
//template class SimulationEndTimeModifier<3>;

#include "SerializationExportWrapperForCpp.hpp"
EXPORT_TEMPLATE_CLASS_SAME_DIMS(SimulationEndTimeModifier)
