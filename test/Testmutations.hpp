/*
 * mutations.hpp
 *
 *  Created on: 15 Mar 2016
 *      Author: fieldj
 */

#ifndef MUTATIONS_HPP_
#define MUTATIONS_HPP_


#include <cxxtest/TestSuite.h>

// Must be included before any other cell_based or crypt headers
#include "CellBasedSimulationArchiver.hpp"

#include "CheckpointArchiveTypes.hpp"
#include "SmartPointers.hpp"
#include "AbstractCellBasedTestSuite.hpp"
#include "AbstractCellPopulation.hpp"
#include "CellAncestorWriter.hpp"
#include "CryptCellsGenerator.hpp"
#include "SimpleWntCellCycleModel.hpp"
#include "CylindricalHoneycombMeshGenerator.hpp"
#include "MeshBasedCellPopulationWithGhostNodes.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "CryptSimulation2d.hpp"
#include "WntConcentration.hpp"
#include "SloughingCellKiller.hpp"
#include "CellMutationStatesCountWriter.hpp"
#include "FakePetscSetup.hpp"

#include "CellBasedEventHandler.hpp"

class TestRunningCryptSimulationsWithMutationsTutorial : public AbstractCellBasedTestSuite
{
public:
    void TestMeshBasedCryptWithMutations() throw(Exception)
    {
    	double time_of_each_run = 10.0;
    	double end_simulations = 600.0;

        CylindricalHoneycombMeshGenerator generator(10, 10, 2);
        Cylindrical2dMesh* p_mesh = generator.GetCylindricalMesh();

        std::vector<unsigned> location_indices = generator.GetCellLocationIndices();

        std::vector<CellPtr> cells;
        CryptCellsGenerator<StochasticWntCellCycleModel> cells_generator;
        cells_generator.Generate(cells, p_mesh, location_indices, true);

        boost::shared_ptr<AbstractCellProperty> p_state(CellPropertyRegistry::Instance()->Get<ApcTwoHitCellMutationState>());

        MeshBasedCellPopulationWithGhostNodes<2> cell_population(*p_mesh, cells, location_indices);

        cell_population.AddCellPopulationCountWriter<CellMutationStatesCountWriter>();
        cell_population.SetCellAncestorsToLocationIndices();

        double crypt_height = 8.0;

        WntConcentration<2>::Instance()->SetType(LINEAR);
        WntConcentration<2>::Instance()->SetCellPopulation(cell_population);
        WntConcentration<2>::Instance()->SetCryptLength(crypt_height);

        CryptSimulation2d simulator(cell_population);
        simulator.SetOutputDirectory("MeshBasedCryptWithMutations");
        simulator.SetSamplingTimestepMultiple(100);
        simulator.SetEndTime(10);

        cell_population.AddCellWriter<CellAncestorWriter>();

        MAKE_PTR(GeneralisedLinearSpringForce<2>, p_linear_force);
        simulator.AddForce(p_linear_force);
        MAKE_PTR_ARGS(SloughingCellKiller<2>, p_killer, (&cell_population, crypt_height));
        simulator.AddCellKiller(p_killer);

        simulator.Solve();

        for (AbstractCellPopulation<2>::Iterator cell_iter = cell_population.Begin();
             cell_iter != cell_population.End();
             ++cell_iter)
        {
            unsigned node_index = cell_population.GetLocationIndexUsingCell(*cell_iter);

            if (node_index == 132) // Chosen from looking at the results from steady state
            {
                cell_iter->SetMutationState(p_state);
            }
        }

       double normal_damping_constant = cell_population.GetDampingConstantNormal();
       cell_population.SetDampingConstantMutant(10*normal_damping_constant);

       CellBasedSimulationArchiver<2, CryptSimulation2d>::Save(&simulator);

       for (double t = time_of_each_run; t<end_simulations+0.5; t += time_of_each_run)
            {
         	   CryptSimulation2d* p_simulator = CellBasedSimulationArchiver<2, CryptSimulation2d>::Load("MeshBasedCryptWithMutations",t);
         	   p_simulator->SetEndTime(t+time_of_each_run);
         	   p_simulator->Solve();
         	   CellBasedSimulationArchiver<2, CryptSimulation2d>::Save(p_simulator);
         	   delete p_simulator;
            }

       CellBasedEventHandler::Headings();
       CellBasedEventHandler::Report();

       WntConcentration<2>::Destroy();


    }
};


#endif /* MUTATIONS_HPP_ */
